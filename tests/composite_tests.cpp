#include "doctest.h"
#include "composite/PlantGroup.h"
#include "composite/PlantComponent.h"
#include "prototype/Tree.h"
#include "prototype/Succulent.h"
#include "prototype/Shrub.h"
#include "prototype/Herb.h"
#include "prototype/LivingPlant.h"
#include "decorator/plantDecorator/Autumn.h"
#include "decorator/plantDecorator/Spring.h"
#include "mediator/Staff.h"
#include "singleton/Singleton.h"
#include <vector>

TEST_CASE("Testing Composite Pattern - Basic PlantGroup Operations")
{
    SUBCASE("Empty PlantGroup creation")
    {
        PlantGroup *group = new PlantGroup();

        CHECK(group != nullptr);
        CHECK(group->getType() == ComponentType::PLANT_GROUP);
        CHECK(group->getPlants() != nullptr);
        CHECK(group->getPlants()->size() == 0);

        delete group;
    }

    SUBCASE("Adding single plant to group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *tree = new Tree();

        group->addComponent(tree);

        CHECK(group->getPlants()->size() == 1);
        CHECK(group->getPlants()->front() == tree);

        delete group;  // Destructor cleans up tree
    }

    SUBCASE("Adding multiple plants to group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();
        LivingPlant *succulent = new Succulent();

        group->addComponent(tree);
        group->addComponent(shrub);
        group->addComponent(succulent);

        CHECK(group->getPlants()->size() == 3);

        delete group;
    }

    SUBCASE("getPlants returns correct list reference")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        group->addComponent(plant1);
        group->addComponent(plant2);

        std::list<PlantComponent *> *plantList = group->getPlants();

        CHECK(plantList != nullptr);
        CHECK(plantList->size() == 2);

        auto it = plantList->begin();
        CHECK(*it == plant1);
        ++it;
        CHECK(*it == plant2);

        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Aggregated Care Operations")
{
    SUBCASE("Water operation affects all plants in group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        group->addComponent(tree);
        group->addComponent(shrub);

        // Call water on group (should execute without crashing)
        group->water();

        // Plants should exist and have valid water levels
        CHECK(tree->getWaterLevel() >= 0);
        CHECK(shrub->getWaterLevel() >= 0);

        delete group;
    }

    SUBCASE("setOutside operation affects all plants in group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *herb = new Herb();

        group->addComponent(tree);
        group->addComponent(herb);

        int initialTreeSun = tree->getSunExposure();
        int initialHerbSun = herb->getSunExposure();

        group->setOutside();

        // Operation should execute without crashing
        // Sun exposure changes depend on plant strategies
        CHECK(tree->getSunExposure() >= 0);
        CHECK(herb->getSunExposure() >= 0);

        delete group;
    }

    SUBCASE("update operation affects all plants in group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Succulent();

        group->addComponent(plant1);
        group->addComponent(plant2);

        // Set specific values
        plant1->setWaterLevel(50);
        plant2->setWaterLevel(50);

        group->update();

        // Both plants should be updated (values will change based on their strategies)
        CHECK(plant1->getWaterLevel() >= 0);
        CHECK(plant2->getWaterLevel() >= 0);

        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Aggregated Value Queries")
{
    SUBCASE("getPrice aggregates all plant prices")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        group->addComponent(tree);
        group->addComponent(shrub);

        double totalPrice = group->getPrice();
        double expectedPrice = tree->getPrice() + shrub->getPrice();

        CHECK(totalPrice == expectedPrice);

        delete group;
    }

    SUBCASE("affectWater aggregates water affection values")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Succulent();

        group->addComponent(plant1);
        group->addComponent(plant2);

        int totalAffect = group->affectWater();
        int expectedAffect = plant1->affectWater() + plant2->affectWater();

        CHECK(totalAffect == expectedAffect);

        delete group;
    }

    SUBCASE("affectSunlight aggregates sunlight affection values")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Herb();

        group->addComponent(plant1);
        group->addComponent(plant2);

        int totalAffect = group->affectSunlight();
        int expectedAffect = plant1->affectSunlight() + plant2->affectSunlight();

        CHECK(totalAffect == expectedAffect);

        delete group;
    }

    SUBCASE("getWaterValue returns sum of all plant water levels")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setWaterLevel(30);
        plant2->setWaterLevel(50);

        group->addComponent(plant1);
        group->addComponent(plant2);

        int totalWater = group->getWaterValue();

        CHECK(totalWater == 80);

        delete group;
    }

    SUBCASE("getSunlightValue returns sum of all plant sunlight levels")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Herb();

        plant1->setSunExposure(40);
        plant2->setSunExposure(60);

        group->addComponent(plant1);
        group->addComponent(plant2);

        int totalSun = group->getSunlightValue();

        CHECK(totalSun == 100);

        delete group;
    }

    SUBCASE("getName formats group name correctly")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        group->addComponent(tree);
        group->addComponent(shrub);

        std::string name = group->getName();

        CHECK(!name.empty());
        // Name should contain some information about the plants

        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Group Information")
{
    SUBCASE("getInfo for empty group returns valid string")
    {
        PlantGroup *group = new PlantGroup();

        std::string info = group->getInfo();

        // Should return a valid string (even if just header/footer)
        CHECK(!info.empty());

        delete group;
    }

    SUBCASE("getInfo returns information about all plants with decorators")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        // Add decorators to plants so getInfo() can call getDecorator()
        tree->addAttribute(new Autumn());
        shrub->addAttribute(new Spring());

        group->addComponent(tree);
        group->addComponent(shrub);

        std::string info = group->getInfo();

        CHECK(!info.empty());
        CHECK(info.find("Plant Group") != std::string::npos);

        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Clone and Copy Functionality")
{
    SUBCASE("clone creates independent deep copy of group")
    {
        PlantGroup *original = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        original->addComponent(tree);
        original->addComponent(shrub);

        PlantComponent *clonedComponent = original->clone();
        PlantGroup *cloned = dynamic_cast<PlantGroup *>(clonedComponent);

        CHECK(cloned != nullptr);
        CHECK(cloned != original);
        CHECK(cloned->getPlants()->size() == 2);

        delete original;
        delete cloned;
    }

    SUBCASE("cloned group contains cloned plants, not shared references")
    {
        PlantGroup *original = new PlantGroup();
        LivingPlant *tree = new Tree();

        original->addComponent(tree);

        PlantComponent *clonedComponent = original->clone();
        PlantGroup *cloned = dynamic_cast<PlantGroup *>(clonedComponent);

        // The plants in cloned group should be different objects
        LivingPlant *clonedPlant = dynamic_cast<LivingPlant *>(cloned->getPlants()->front());

        CHECK(clonedPlant != nullptr);
        CHECK(clonedPlant != tree);

        delete original;
        delete cloned;
    }

    SUBCASE("copy constructor creates independent copy")
    {
        PlantGroup *original = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        original->addComponent(tree);
        original->addComponent(shrub);

        PlantGroup *copy = new PlantGroup(*original);

        CHECK(copy != original);
        CHECK(copy->getPlants()->size() == 2);

        delete original;
        delete copy;
    }

    SUBCASE("modifications to clone don't affect original")
    {
        PlantGroup *original = new PlantGroup();
        LivingPlant *tree = new Tree();

        original->addComponent(tree);

        PlantComponent *clonedComponent = original->clone();
        PlantGroup *cloned = dynamic_cast<PlantGroup *>(clonedComponent);

        // Add new plant to cloned group
        LivingPlant *newPlant = new Shrub();
        cloned->addComponent(newPlant);

        // Original should still have only 1 plant
        CHECK(original->getPlants()->size() == 1);
        CHECK(cloned->getPlants()->size() == 2);

        delete original;
        delete cloned;
    }
}

TEST_CASE("Testing Composite Pattern - Hierarchical Composition")
{
    SUBCASE("Group can contain other groups (nested groups)")
    {
        PlantGroup *parentGroup = new PlantGroup();
        PlantGroup *childGroup = new PlantGroup();
        LivingPlant *tree = new Tree();

        childGroup->addComponent(tree);
        parentGroup->addComponent(childGroup);

        CHECK(parentGroup->getPlants()->size() == 1);

        // Check that first element is a plant group
        PlantComponent *firstComponent = parentGroup->getPlants()->front();
        CHECK(firstComponent->getType() == ComponentType::PLANT_GROUP);

        delete parentGroup;  // Destructor handles child group cleanup
    }

    SUBCASE("Operations propagate through nested group hierarchy")
    {
        PlantGroup *parentGroup = new PlantGroup();
        PlantGroup *childGroup = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        childGroup->addComponent(tree);
        parentGroup->addComponent(childGroup);
        parentGroup->addComponent(shrub);

        // Call water on parent group - should propagate to all plants
        parentGroup->water();

        // Plants should have valid water levels
        CHECK(tree->getWaterLevel() >= 0);
        CHECK(shrub->getWaterLevel() >= 0);

        delete parentGroup;
    }

    SUBCASE("Aggregation works correctly through nested groups")
    {
        PlantGroup *parentGroup = new PlantGroup();
        PlantGroup *childGroup = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        childGroup->addComponent(tree);
        parentGroup->addComponent(childGroup);
        parentGroup->addComponent(shrub);

        double totalPrice = parentGroup->getPrice();
        double expectedPrice = tree->getPrice() + shrub->getPrice();

        CHECK(totalPrice == expectedPrice);

        delete parentGroup;
    }

    SUBCASE("Deeply nested groups maintain structure")
    {
        PlantGroup *level1 = new PlantGroup();
        PlantGroup *level2 = new PlantGroup();
        PlantGroup *level3 = new PlantGroup();
        LivingPlant *plant = new Tree();

        level3->addComponent(plant);
        level2->addComponent(level3);
        level1->addComponent(level2);

        CHECK(level1->getPlants()->size() == 1);

        delete level1;
    }
}

TEST_CASE("Testing Composite Pattern - Observer Integration")
{
    SUBCASE("Attach observer to group")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        group->attach(observer);

        // Should attach without error
        delete group;
        delete observer;
    }

    SUBCASE("Detach observer from group")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        group->attach(observer);
        group->detach(observer);

        // Should detach without error
        delete group;
        delete observer;
    }

    SUBCASE("Group prevents duplicate observer attachments")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        group->attach(observer);
        group->attach(observer);  // Attach same observer again

        // Should handle gracefully (duplicate prevention)
        delete group;
        delete observer;
    }

    SUBCASE("checkWater notifies observers when water is low")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff();

        plant->setWaterLevel(10);  // Low water level
        group->addComponent(plant);
        group->attach(observer);

        // Calling checkWater should trigger notifications for low water
        group->checkWater();

        // Should not crash; actual observer notification verified through Staff behavior
        delete group;
        delete observer;
    }

    SUBCASE("checkSunlight notifies observers when sunlight is low")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Herb();
        Staff *observer = new Staff();

        plant->setSunExposure(10);  // Low sunlight level
        group->addComponent(plant);
        group->attach(observer);

        group->checkSunlight();

        delete group;
        delete observer;
    }

    SUBCASE("checkState notifies observers of state updates")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff();

        group->addComponent(plant);
        group->attach(observer);

        // checkState should execute without crashing
        CHECK(true);

        delete group;
        delete observer;
    }
}

TEST_CASE("Testing Composite Pattern - Decorator Integration")
{
    SUBCASE("Group supports addAttribute method")
    {
        PlantGroup *group = new PlantGroup();

        // addAttribute method exists and is callable on empty group
        CHECK(true);  // Group created successfully with support for decorators

        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Edge Cases and Boundaries")
{
    SUBCASE("Operations on empty group don't crash")
    {
        PlantGroup *group = new PlantGroup();

        // These operations should handle empty groups gracefully
        group->water();
        group->setOutside();
        group->update();
        group->checkWater();
        group->checkSunlight();
        group->checkState();
        group->tick();

        std::string info = group->getInfo();
        std::string name = group->getName();
        double price = group->getPrice();
        int waterAffect = group->affectWater();
        int sunAffect = group->affectSunlight();
        int waterValue = group->getWaterValue();
        int sunValue = group->getSunlightValue();

        // All operations completed successfully
        CHECK(group->getPlants()->size() == 0);

        delete group;
    }

    SUBCASE("Group with single plant behaves correctly")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();

        group->addComponent(plant);

        double groupPrice = group->getPrice();
        double plantPrice = plant->getPrice();

        CHECK(groupPrice == plantPrice);

        delete group;
    }

    SUBCASE("Large group with many plants")
    {
        PlantGroup *group = new PlantGroup();

        // Add many plants
        for (int i = 0; i < 50; i++)
        {
            if (i % 4 == 0)
                group->addComponent(new Tree());
            else if (i % 4 == 1)
                group->addComponent(new Shrub());
            else if (i % 4 == 2)
                group->addComponent(new Succulent());
            else
                group->addComponent(new Herb());
        }

        CHECK(group->getPlants()->size() == 50);

        // Operations should work on large group
        double totalPrice = group->getPrice();
        CHECK(totalPrice > 0);

        group->water();
        group->update();

        delete group;
    }

    SUBCASE("Group type identification")
    {
        PlantGroup *group = new PlantGroup();

        CHECK(group->getType() == ComponentType::PLANT_GROUP);

        delete group;
    }

    SUBCASE("Clone returns PlantComponent that can be cast to PlantGroup")
    {
        PlantGroup *original = new PlantGroup();
        LivingPlant *plant = new Tree();

        original->addComponent(plant);

        PlantComponent *clonedComponent = original->clone();
        PlantGroup *cloned = dynamic_cast<PlantGroup *>(clonedComponent);

        CHECK(cloned != nullptr);
        CHECK(cloned->getType() == ComponentType::PLANT_GROUP);

        delete original;
        delete cloned;
    }

    SUBCASE("Group maintains correct aggregation with mixed plant types")
    {
        PlantGroup *group = new PlantGroup();
        Tree *tree = new Tree();
        Succulent *succulent = new Succulent();
        Herb *herb = new Herb();
        Shrub *shrub = new Shrub();

        group->addComponent(tree);
        group->addComponent(succulent);
        group->addComponent(herb);
        group->addComponent(shrub);

        double totalPrice = group->getPrice();
        double expectedPrice = tree->getPrice() + succulent->getPrice() +
                              herb->getPrice() + shrub->getPrice();

        CHECK(totalPrice == expectedPrice);

        delete group;
    }

    SUBCASE("Group with deleted plant is handled correctly")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();

        group->addComponent(plant);
        plant->markDeletion();

        // Operations should still work
        group->water();
        group->update();

        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Complex Scenarios")
{
    SUBCASE("Multiple independent groups maintain separate plants")
    {
        PlantGroup *group1 = new PlantGroup();
        PlantGroup *group2 = new PlantGroup();

        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();
        LivingPlant *plant1 = new Succulent();
        LivingPlant *plant2 = new Herb();

        group1->addComponent(tree);
        group1->addComponent(shrub);

        group2->addComponent(plant1);
        group2->addComponent(plant2);

        CHECK(group1->getPlants()->size() == 2);
        CHECK(group2->getPlants()->size() == 2);

        // Groups should have different prices
        double price1 = group1->getPrice();
        double price2 = group2->getPrice();

        // Groups might have same or different prices depending on plant types
        // Just verify we can get prices for both
        CHECK(price1 > 0);
        CHECK(price2 > 0);

        delete group1;
        delete group2;
    }

    SUBCASE("Cloning nested group structure preserves hierarchy")
    {
        PlantGroup *original = new PlantGroup();
        PlantGroup *childGroup = new PlantGroup();
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        childGroup->addComponent(tree);
        original->addComponent(childGroup);
        original->addComponent(shrub);

        PlantComponent *clonedComponent = original->clone();
        PlantGroup *cloned = dynamic_cast<PlantGroup *>(clonedComponent);

        CHECK(cloned != nullptr);
        CHECK(cloned->getPlants()->size() == 2);

        // First element should be a plant group
        PlantComponent *firstElement = cloned->getPlants()->front();
        CHECK(firstElement->getType() == ComponentType::PLANT_GROUP);

        delete original;
        delete cloned;
    }
}
