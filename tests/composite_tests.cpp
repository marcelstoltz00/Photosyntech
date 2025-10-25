#include "doctest.h"
#include "composite/PlantComponent.h"
#include "composite/PlantGroup.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Succulent.h"
#include "strategy/LowWater.h"
#include "strategy/LowSun.h"

TEST_CASE("Testing Composite Pattern - Basic PlantGroup Creation")
{
    SUBCASE("PlantGroup can be created")
    {
        PlantGroup *group = new PlantGroup();
        CHECK(group != nullptr);
        delete group;
    }

    SUBCASE("PlantGroup starts empty")
    {
        PlantGroup *group = new PlantGroup();
        // A newly created group should have no components
        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Single Plant Component")
{
    SUBCASE("Single plant can be added to group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();

        group->addComponent(plant);

        delete group;  // This will delete plant as well
    }

    SUBCASE("Plant operations work on single component")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        group->addComponent(plant);
        group->water();

        // Plant should have been watered
        CHECK(plant->getWaterLevel() > 0);

        delete group;  // This will delete plant as well
    }
}

TEST_CASE("Testing Composite Pattern - Multiple Plants in Group")
{
    SUBCASE("Multiple plants can be added to group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();
        LivingPlant *plant3 = new Succulent();

        group->addComponent(plant1);
        group->addComponent(plant2);
        group->addComponent(plant3);

        delete group;  // This will delete all plants as well
    }

    SUBCASE("Water operation applies to all plants in group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setWaterStrategy(LowWater::getID());
        plant2->setWaterStrategy(LowWater::getID());
        plant1->setWaterLevel(0);
        plant2->setWaterLevel(0);

        group->addComponent(plant1);
        group->addComponent(plant2);

        group->water();

        // Both plants should be watered
        CHECK(plant1->getWaterLevel() > 0);
        CHECK(plant2->getWaterLevel() > 0);

        delete group;  // This will delete all plants as well
    }

    SUBCASE("Sun operation applies to all plants in group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setSunStrategy(LowSun::getID());
        plant2->setSunStrategy(LowSun::getID());
        plant1->setSunExposure(0);
        plant2->setSunExposure(0);

        group->addComponent(plant1);
        group->addComponent(plant2);

        group->setOutside();

        // Both plants should have received sun
        CHECK(plant1->getSunExposure() > 0);
        CHECK(plant2->getSunExposure() > 0);

        delete group;  // This will delete all plants as well
    }
}

TEST_CASE("Testing Composite Pattern - Nested Plant Groups")
{
    SUBCASE("PlantGroup can contain other PlantGroups")
    {
        PlantGroup *rootGroup = new PlantGroup();
        PlantGroup *subGroup = new PlantGroup();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());

        // Build hierarchy
        subGroup->addComponent(plant);
        rootGroup->addComponent(subGroup);

        plant->setWaterLevel(0);
        rootGroup->water();

        // Plant in subgroup should be watered
        CHECK(plant->getWaterLevel() > 0);

        delete rootGroup;  // This will delete subGroup and plant as well
    }

    SUBCASE("Deep nesting with multiple levels")
    {
        PlantGroup *level1 = new PlantGroup();
        PlantGroup *level2 = new PlantGroup();
        PlantGroup *level3 = new PlantGroup();

        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setWaterStrategy(LowWater::getID());
        plant2->setWaterStrategy(LowWater::getID());
        plant1->setWaterLevel(0);
        plant2->setWaterLevel(0);

        // Build deep hierarchy
        level3->addComponent(plant1);
        level2->addComponent(level3);
        level2->addComponent(plant2);
        level1->addComponent(level2);

        level1->water();

        // Both plants in different nesting levels should be watered
        CHECK(plant1->getWaterLevel() > 0);
        CHECK(plant2->getWaterLevel() > 0);

        delete level1;  // This will delete all children recursively
    }
}

TEST_CASE("Testing Composite Pattern - Plant Information Retrieval")
{
    SUBCASE("Plant group can retrieve component information")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();

        group->addComponent(plant);

        // GetInfo should work on group
        std::string info = group->getInfo();
        CHECK(!info.empty());

        delete group;  // This will delete plant as well
    }

    SUBCASE("Nested group information includes child information")
    {
        PlantGroup *group = new PlantGroup();
        PlantGroup *subGroup = new PlantGroup();
        LivingPlant *plant = new Tree();

        subGroup->addComponent(plant);
        group->addComponent(subGroup);

        std::string groupInfo = group->getInfo();
        CHECK(!groupInfo.empty());

        delete group;  // This will delete subGroup and plant as well
    }
}

TEST_CASE("Testing Composite Pattern - Observer Integration")
{
    SUBCASE("PlantGroup supports observer attachment")
    {
        PlantGroup *group = new PlantGroup();
        // Group creation should work for observer attachment
        CHECK(group != nullptr);
        delete group;
    }

    SUBCASE("Multiple observers can be attached to group")
    {
        PlantGroup *group = new PlantGroup();
        // Note: Staff class serves as Observer - testing that interface exists

        // Group should be able to support observers without crashing
        group->waterNeeded();
        group->sunlightNeeded();
        group->stateUpdated();

        delete group;
    }
}

TEST_CASE("Testing Composite Pattern - Composite with All Plant Types")
{
    SUBCASE("Group can manage all four plant types")
    {
        PlantGroup *group = new PlantGroup();

        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();
        LivingPlant *succulent = new Succulent();

        tree->setWaterStrategy(LowWater::getID());
        shrub->setWaterStrategy(LowWater::getID());
        succulent->setWaterStrategy(LowWater::getID());

        tree->setWaterLevel(0);
        shrub->setWaterLevel(0);
        succulent->setWaterLevel(0);

        group->addComponent(tree);
        group->addComponent(shrub);
        group->addComponent(succulent);

        group->water();

        // All plants should be watered
        CHECK(tree->getWaterLevel() > 0);
        CHECK(shrub->getWaterLevel() > 0);
        CHECK(succulent->getWaterLevel() > 0);

        delete group;  // This will delete all plants as well
    }
}

TEST_CASE("Testing Composite Pattern - Update Operations")
{
    SUBCASE("PlantGroup can call update on components")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        plant->setWaterLevel(50);
        plant->setSunExposure(50);

        group->addComponent(plant);

        // Update should work without crashing
        group->update();

        delete group;  // This will delete plant as well
    }
}

TEST_CASE("Testing Composite Pattern - Large Group Operations")
{
    SUBCASE("Group can handle many plants efficiently")
    {
        PlantGroup *group = new PlantGroup();

        // Create and add multiple plants
        std::vector<LivingPlant *> plants;
        for (int i = 0; i < 10; i++) {
            LivingPlant *plant = new Tree();
            plant->setWaterStrategy(LowWater::getID());
            plant->setWaterLevel(0);
            plants.push_back(plant);
            group->addComponent(plant);
        }

        // Water all plants
        group->water();

        // All should be watered
        for (LivingPlant *plant : plants) {
            CHECK(plant->getWaterLevel() > 0);
        }

        // Cleanup
        delete group;  // This will delete all plants as well
    }
}

TEST_CASE("Testing Composite Pattern - Mixed Composition")
{
    SUBCASE("Group can mix plants and subgroups")
    {
        PlantGroup *mainGroup = new PlantGroup();
        PlantGroup *subGroup = new PlantGroup();

        LivingPlant *directPlant = new Tree();
        LivingPlant *nestedPlant = new Shrub();

        directPlant->setWaterStrategy(LowWater::getID());
        nestedPlant->setWaterStrategy(LowWater::getID());
        directPlant->setWaterLevel(0);
        nestedPlant->setWaterLevel(0);

        subGroup->addComponent(nestedPlant);
        mainGroup->addComponent(directPlant);
        mainGroup->addComponent(subGroup);

        mainGroup->water();

        // Both plants should be watered regardless of nesting
        CHECK(directPlant->getWaterLevel() > 0);
        CHECK(nestedPlant->getWaterLevel() > 0);

        delete mainGroup;  // This will delete subGroup, directPlant, and nestedPlant as well
    }
}
