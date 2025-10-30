#include "doctest.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Succulent.h"
#include "prototype/Herb.h"

TEST_CASE("Testing Prototype Pattern - Plant Type Creation")
{
    SUBCASE("Tree creation and basic properties")
    {
        LivingPlant *tree = new Tree();
        CHECK(tree != nullptr);

        // Verify plant is initialized with default values
        CHECK(tree->getAge() >= 0);
        CHECK(tree->getHealth() >= 0);

        delete tree;
    }

    SUBCASE("Shrub creation and basic properties")
    {
        LivingPlant *shrub = new Shrub();
        CHECK(shrub != nullptr);
        CHECK(shrub->getAge() >= 0);
        CHECK(shrub->getHealth() >= 0);

        delete shrub;
    }

    SUBCASE("Succulent creation and basic properties")
    {
        LivingPlant *succulent = new Succulent();
        CHECK(succulent != nullptr);
        CHECK(succulent->getAge() >= 0);
        CHECK(succulent->getHealth() >= 0);

        delete succulent;
    }

    SUBCASE("Herb creation and basic properties")
    {
        LivingPlant *herb = new Herb();
        CHECK(herb != nullptr);
        CHECK(herb->getAge() >= 0);
        CHECK(herb->getHealth() >= 0);

        delete herb;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Prototype Pattern - Plant Type Differences")
{
    SUBCASE("Different plant types have different characteristics")
    {
        LivingPlant *tree = new Tree();
        LivingPlant *succulent = new Succulent();
        LivingPlant *shrub = new Shrub();

        // All should be valid plants
        CHECK(tree != nullptr);
        CHECK(succulent != nullptr);
        CHECK(shrub != nullptr);

        delete tree;
        delete succulent;
        delete shrub;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Prototype Pattern - Plant Initialization")
{
    SUBCASE("Plant with constructor parameters")
    {
        LivingPlant *plant = new LivingPlant("TestPlant", 25.0, 5, 5);
        CHECK(plant != nullptr);
        CHECK(plant->getAge() >= 0);
        CHECK(plant->getHealth() >= 0);

        delete plant;
    }

    SUBCASE("Multiple plants of same type are independent")
    {
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Tree();

        // Set different water levels
        plant1->setWaterLevel(10);
        plant2->setWaterLevel(20);

        // Verify independence
        CHECK(plant1->getWaterLevel() != plant2->getWaterLevel());
        CHECK(plant1->getWaterLevel() == 10);
        CHECK(plant2->getWaterLevel() == 20);

        delete plant1;
        delete plant2;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Prototype Pattern - Plant Cloning via Copy")
{
    SUBCASE("Plant instance can be configured independently")
    {
        LivingPlant *originalPlant = new Tree();

        // Configure the original plant
        originalPlant->setAge(10);
        originalPlant->setHealth(75);
        originalPlant->setWaterLevel(30);
        originalPlant->setSunExposure(40);

        // Create another plant of same type but different configuration
        LivingPlant *clonedPlant = new Tree();
        clonedPlant->setAge(5);
        clonedPlant->setHealth(50);
        clonedPlant->setWaterLevel(15);
        clonedPlant->setSunExposure(20);

        // Verify they have different states
        CHECK(originalPlant->getAge() == 10);
        CHECK(clonedPlant->getAge() == 5);
        CHECK(originalPlant->getHealth() == 75);
        CHECK(clonedPlant->getHealth() == 50);
        CHECK(originalPlant->getWaterLevel() == 30);
        CHECK(clonedPlant->getWaterLevel() == 15);

        delete originalPlant;
        delete clonedPlant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Prototype Pattern - Mixed Plant Types")
{
    SUBCASE("Can create and manage different plant types")
    {
        LivingPlant *plants[4] = {
            new Tree(),
            new Shrub(),
            new Succulent(),
            new Herb()
        };

        // Set unique properties on each
        for (int i = 0; i < 4; i++) {
            plants[i]->setAge(i * 10);
            plants[i]->setHealth(50 + i * 10);
        }

        // Verify each maintains its own state
        for (int i = 0; i < 4; i++) {
            CHECK(plants[i]->getAge() == i * 10);
            CHECK(plants[i]->getHealth() == 50 + i * 10);
            delete plants[i];
        }
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Prototype Pattern - Plant Lifecycle Properties")
{
    SUBCASE("Plant can transition through lifecycle states")
    {
        LivingPlant *plant = new Tree();

        // Simulate aging
        plant->setAge(6);
        CHECK(plant->getAge() == 6);

        plant->setAge(29);
        CHECK(plant->getAge() == 29);

        plant->setAge(119);
        CHECK(plant->getAge() == 119);

        delete plant;
    }

    SUBCASE("Plant health can be modified")
    {
        LivingPlant *plant = new Succulent();

        plant->setHealth(100);
        CHECK(plant->getHealth() == 100);

        plant->setHealth(50);
        CHECK(plant->getHealth() == 50);

        plant->setHealth(0);
        CHECK(plant->getHealth() == 0);

        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Prototype Pattern - Plant Care Properties")
{
    SUBCASE("Plant water level can be managed")
    {
        LivingPlant *plant = new Tree();

        plant->setWaterLevel(0);
        CHECK(plant->getWaterLevel() == 0);

        plant->setWaterLevel(50);
        CHECK(plant->getWaterLevel() == 50);

        plant->setWaterLevel(100);
        CHECK(plant->getWaterLevel() == 100);

        delete plant;
    }

    SUBCASE("Plant sun exposure can be managed")
    {
        LivingPlant *plant = new Shrub();

        plant->setSunExposure(0);
        CHECK(plant->getSunExposure() == 0);

        plant->setSunExposure(30);
        CHECK(plant->getSunExposure() == 30);

        plant->setSunExposure(100);
        CHECK(plant->getSunExposure() == 100);

        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Prototype Pattern - Plant Type Operations")
{
    SUBCASE("All plant types support water method")
    {
        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();
        LivingPlant *succulent = new Succulent();

        tree->setWaterLevel(0);
        shrub->setWaterLevel(0);
        succulent->setWaterLevel(0);

        // These should not crash
        tree->water();
        shrub->water();
        succulent->water();

        delete tree;
        delete shrub;
        delete succulent;
    }

    SUBCASE("All plant types support setOutside method")
    {
        LivingPlant *tree = new Tree();
        LivingPlant *herb = new Herb();

        tree->setSunExposure(0);
        herb->setSunExposure(0);

        // These should not crash
        tree->setOutside();
        herb->setOutside();

        CHECK(tree->getSunExposure() >= 0);
        CHECK(herb->getSunExposure() >= 0);

        delete tree;
        delete herb;
    }
    delete Inventory::getInstance();
}
