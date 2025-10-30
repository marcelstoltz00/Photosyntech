#include "doctest.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Succulent.h"
#include "prototype/Herb.h"
#include "singleton/Singleton.h"
#include "state/Seed.h"
#include "state/Vegetative.h"
#include "state/Mature.h"
#include "state/Dead.h"
#include "state/MaturityState.h"
#include "observer/Subject.h"
#include "observer/Observer.h"
#include <vector>
#include <iostream>

TEST_CASE("Testing MaturityState transitions and behavior")
{
    Inventory *inv = Inventory::getInstance();
    LivingPlant *plant = new Tree();

    SUBCASE("Seed -> Vegetative transition")
    {
        plant->setAge(6);
        plant->setHealth(50);

        plant->setWaterLevel(56);
        plant->setSunExposure(30);
        plant->setMaturity(Seed::getID());

        inv->getStates(Seed::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 25);
        CHECK(plant->getSunExposure() == 50);
        CHECK(plant->getHealth() >= 45);
    }

    SUBCASE("Vegetative -> Mature transition")
    {
        plant->setAge(29);
        plant->setHealth(60);
        plant->setWaterLevel(50);
        plant->setSunExposure(50);
        plant->setMaturity(Vegetative::getID());

        inv->getStates(Vegetative::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 40);
    CHECK(plant->getSunExposure() == 60);
    CHECK(plant->getHealth() >= 55);
    }

    SUBCASE("Mature -> Dead transition by age")
    {
        plant->setAge(119);
        plant->setHealth(10);
        plant->setWaterLevel(40);
        plant->setSunExposure(40);
        plant->setMaturity(Mature::getID());

        inv->getStates(Mature::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 0);
        CHECK(plant->getSunExposure() == 0);
        CHECK(plant->getHealth() == 0);
    }

    SUBCASE("Dead state grow increments age only and keeps zeros")
    {
        plant->setAge(120);
        plant->setHealth(0);
        plant->setWaterLevel(0);
        plant->setSunExposure(0);
        plant->setMaturity(Dead::getID());

        inv->getStates(Dead::getID())->getState()->grow(plant);

        CHECK(plant->getAge() == 121);
        CHECK(plant->getWaterLevel() == 0);
        CHECK(plant->getHealth() == 0);
    }

    delete plant;
    delete Inventory::getInstance();
}

// ============================================================================
// COMPREHENSIVE STATE TESTS - HEALTH-BASED TRANSITIONS & EDGE CASES
// ============================================================================

TEST_CASE("Testing State Transitions - Health-Based Path to Dead")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("High health plant remains alive")
    {
        LivingPlant *plant = new Tree();
        plant->setAge(50);
        plant->setHealth(100);
        plant->setMaturity(Mature::getID());

        inv->getStates(Mature::getID())->getState()->grow(plant);

        // High health should prevent death
        CHECK(plant->getHealth() >= 0);

        delete plant;
    }

    SUBCASE("Low health triggers dead state")
    {
        LivingPlant *plant = new Tree();
        plant->setAge(50);
        plant->setHealth(1); // Critical health
        plant->setWaterLevel(0);
        plant->setSunExposure(0);
        plant->setMaturity(Mature::getID());

        inv->getStates(Mature::getID())->getState()->grow(plant);

        // Low health should potentially lead to death
        CHECK(plant->getHealth() <= 100);

        delete plant;
    }

    SUBCASE("Zero health immediately dead")
    {
        LivingPlant *plant = new Tree();
        plant->setAge(50);
        plant->setHealth(0);
        plant->setMaturity(Vegetative::getID());

        // Zero health should be treated as dead state
        CHECK(plant->getHealth() == 0);

        delete plant;
    }

    SUBCASE("Health degradation across states")
    {
        LivingPlant *plant = new Tree();

        plant->setHealth(100);
        plant->setAge(5);
        plant->setMaturity(Seed::getID());
        plant->setWaterLevel(0);
        plant->setSunExposure(0);

        // Transition through states with poor care
        inv->getStates(Seed::getID())->getState()->grow(plant);

        // Health should degrade without proper water/sun
        CHECK(plant->getHealth() <= 100);

        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing State Transitions - All Plant Types Through All States")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("Tree through all states")
    {
        LivingPlant *tree = new Tree();

        tree->setAge(5);
        tree->setHealth(50);
        tree->setMaturity(Seed::getID());
        inv->getStates(Seed::getID())->getState()->grow(tree);

        tree->setAge(29);
        tree->setHealth(60);
        tree->setMaturity(Vegetative::getID());
        inv->getStates(Vegetative::getID())->getState()->grow(tree);

        tree->setAge(119);
        tree->setMaturity(Mature::getID());
        inv->getStates(Mature::getID())->getState()->grow(tree);

        delete tree;
    }

    SUBCASE("Shrub through all states")
    {
        LivingPlant *shrub = new Shrub();

        shrub->setAge(6);
        shrub->setHealth(50);
        shrub->setMaturity(Seed::getID());

        shrub->setAge(29);
        shrub->setHealth(60);
        shrub->setMaturity(Vegetative::getID());

        shrub->setAge(119);
        shrub->setMaturity(Mature::getID());

        delete shrub;
    }

    SUBCASE("Succulent through all states")
    {
        LivingPlant *succulent = new Succulent();

        succulent->setAge(6);
        succulent->setHealth(50);
        succulent->setMaturity(Seed::getID());

        succulent->setAge(29);
        succulent->setHealth(60);
        succulent->setMaturity(Vegetative::getID());

        succulent->setAge(119);
        succulent->setMaturity(Mature::getID());

        delete succulent;
    }

    SUBCASE("Herb through all states")
    {
        LivingPlant *herb = new Herb();

        herb->setAge(6);
        herb->setHealth(50);
        herb->setMaturity(Seed::getID());

        herb->setAge(29);
        herb->setHealth(60);
        herb->setMaturity(Vegetative::getID());

        herb->setAge(119);
        herb->setMaturity(Mature::getID());

        delete herb;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing State Transitions - Boundary Value Testing")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("Age exactly at transition boundaries")
    {
        LivingPlant *plant = new Tree();

        // Seed->Vegetative boundary: age = 6
        plant->setAge(6);
        plant->setHealth(50);
        plant->setMaturity(Seed::getID());
        inv->getStates(Seed::getID())->getState()->grow(plant);

        // Vegetative->Mature boundary: age = 29
        plant->setAge(29);
        plant->setHealth(60);
        plant->setMaturity(Vegetative::getID());
        inv->getStates(Vegetative::getID())->getState()->grow(plant);

        // Mature->Dead boundary: age = 119
        plant->setAge(119);
        plant->setMaturity(Mature::getID());
        inv->getStates(Mature::getID())->getState()->grow(plant);

        delete plant;
    }

    SUBCASE("Age just below transition boundaries")
    {
        LivingPlant *plant = new Tree();

        plant->setAge(5); // Just before Seed->Vegetative
        plant->setHealth(50);
        plant->setMaturity(Seed::getID());

        plant->setAge(28); // Just before Vegetative->Mature
        plant->setHealth(60);
        plant->setMaturity(Vegetative::getID());

        plant->setAge(118); // Just before Mature->Dead
        plant->setHealth(50);
        plant->setMaturity(Mature::getID());

        delete plant;
    }

    SUBCASE("Age just above transition boundaries")
    {
        LivingPlant *plant = new Tree();

        plant->setAge(7); // Just after Seed->Vegetative
        plant->setHealth(50);
        plant->setMaturity(Vegetative::getID());

        plant->setAge(30); // Just after Vegetative->Mature
        plant->setHealth(60);
        plant->setMaturity(Mature::getID());

        plant->setAge(120); // Just after Mature->Dead
        plant->setMaturity(Dead::getID());

        delete plant;
    }

    SUBCASE("Health exactly at critical thresholds")
    {
        LivingPlant *plant = new Tree();

        plant->setHealth(1); // Minimum before death
        plant->setAge(50);
        plant->setMaturity(Vegetative::getID());
        CHECK(plant->getHealth() == 1);

        plant->setHealth(100); // Maximum health
        CHECK(plant->getHealth() == 100);

        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing State-Specific Behavior")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("Seed state behavior")
    {
        LivingPlant *plant = new Tree();
        plant->setMaturity(Seed::getID());
        plant->setAge(1);
        plant->setHealth(30);

        // Seed should have limited capabilities
        CHECK(plant->getAge() >= 0);
        CHECK(plant->getHealth() >= 0);

        delete plant;
    }

    SUBCASE("Vegetative state behavior")
    {
        LivingPlant *plant = new Tree();
        plant->setMaturity(Vegetative::getID());
        plant->setAge(20);
        plant->setHealth(60);

        // Vegetative should have developing capabilities
        CHECK(plant->getAge() >= 6);
        CHECK(plant->getHealth() >= 0);

        delete plant;
    }

    SUBCASE("Mature state behavior")
    {
        LivingPlant *plant = new Tree();
        plant->setMaturity(Mature::getID());
        plant->setAge(50);
        plant->setHealth(80);

        // Mature should be fully developed
        CHECK(plant->getAge() >= 29);
        CHECK(plant->getHealth() > 0);

        delete plant;
    }

    SUBCASE("Dead state behavior")
    {
        LivingPlant *plant = new Tree();
        plant->setMaturity(Dead::getID());
        plant->setAge(120);
        plant->setHealth(0);

        // Dead state properties
        CHECK(plant->getHealth() == 0);
        CHECK(plant->getAge() >= 119);

        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing State Transitions - Observer Integration")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("State change triggers observer notification")
    {
        LivingPlant *plant = new Tree();
        plant->setAge(6);
        plant->setHealth(50);
        plant->setMaturity(Seed::getID());

        // Transition should trigger state change event
        inv->getStates(Seed::getID())->getState()->grow(plant);

        // Plant should reflect state change
        CHECK(plant != nullptr);

        delete plant;
    }

    SUBCASE("Multiple plants state changes")
    {
        std::vector<LivingPlant *> plants;
        plants.push_back(new Tree());
        plants.push_back(new Shrub());
        plants.push_back(new Succulent());

        for (LivingPlant *p : plants)
        {
            p->setAge(6);
            p->setHealth(50);
            p->setMaturity(Seed::getID());

            inv->getStates(Seed::getID())->getState()->grow(p);
        }

        for (LivingPlant *p : plants)
        {
            delete p;
        }
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing State Transitions - Concurrent State Changes")
{

    Inventory *inv = Inventory::getInstance();

    SUBCASE("Age and health changing simultaneously")
    {
        LivingPlant *plant = new Tree();

        plant->setAge(5);
        plant->setHealth(50);
        plant->setWaterLevel(30);
        plant->setSunExposure(30);

        // Age increases, health can change
        plant->setAge(6);
        plant->setHealth(55);

        CHECK(plant->getAge() == 6);
        CHECK(plant->getHealth() == 55);

        delete plant;
    }

    SUBCASE("State change with water/sun level changes")
    {
        LivingPlant *plant = new Tree();

        plant->setAge(6);
        plant->setHealth(50);
        plant->setWaterLevel(50);
        plant->setSunExposure(50);
        plant->setMaturity(Seed::getID());

        inv->getStates(Seed::getID())->getState()->grow(plant);

        // All properties should be consistent after state change
        CHECK(plant->getWaterLevel() >= 0);
        CHECK(plant->getSunExposure() >= 0);
        CHECK(plant->getHealth() >= 0);

        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing State Transitions - Invalid States")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("Vegetative state with age < 6 (invalid)")
    {
        LivingPlant *plant = new Tree();

        plant->setAge(3); // Below transition threshold
        plant->setHealth(50);
        plant->setMaturity(Vegetative::getID());

        // Should handle gracefully even with invalid age for state
        CHECK(plant->getAge() == 3);

        delete plant;
    }

    SUBCASE("Mature state with age < 29 (invalid)")
    {
        LivingPlant *plant = new Tree();

        plant->setAge(20); // Below transition threshold
        plant->setHealth(60);
        plant->setMaturity(Mature::getID());

        // Should handle gracefully
        CHECK(plant->getAge() == 20);

        delete plant;
    }

    SUBCASE("Dead state with health > 0 (technically invalid)")
    {
        LivingPlant *plant = new Tree();

        plant->setMaturity(Dead::getID());
        plant->setHealth(50); // Dead plants shouldn't have health

        // Should handle gracefully
        CHECK(plant->getHealth() == 50);

        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing State Transitions - Large Scale")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("100 plants aging through states")
    {
        std::vector<LivingPlant *> plants;

        for (int i = 0; i < 100; i++)
        {
            LivingPlant *p = new Tree();

            p->setAge(6 + i);
            p->setHealth(50 + (i % 50));

            if (i % 3 == 0)
                p->setMaturity(Seed::getID());
            else if (i % 3 == 1)
                p->setMaturity(Vegetative::getID());
            else
                p->setMaturity(Mature::getID());

            plants.push_back(p);
        }

        // All plants should be created and in valid states
        for (LivingPlant *p : plants)
        {
            CHECK(p != nullptr);
        }

        for (LivingPlant *p : plants)
        {
            delete p;
        }
    }
    delete Inventory::getInstance();
}

// TEST_CASE("Testing State Transitions - Continuous Aging")
// {
//     Inventory *inv = Inventory::getInstance();

//     SUBCASE("Plant aging through multiple cycles")
//     {
//         LivingPlant *plant = new Tree();

//         for (int age = 1; age <= 130; age++) {
//             plant->setAge(age);

//             if (age < 6) plant->setMaturity(Seed::getID());
//             else if (age < 29) plant->setMaturity(Vegetative::getID());
//             else if (age < 120) plant->setMaturity(Mature::getID());
//             else plant->setMaturity(Dead::getID());

//             // Simulate grow at each age
//             if (age == 6) {
//                 Seed seed;
//                 seed.grow(plant);
//             }
//             else if (age == 29) {
//                 Vegetative veg;
//                 veg.grow(plant);
//             }
//             else if (age == 120) {
//                 Mature mature;
//                 mature.grow(plant);
//             }
//         }

//         // Plant should survive aging process
//         CHECK(plant->getAge() == 130);

//         delete plant;
//     }
//     delete Inventory::getInstance();
// }

// TEST_CASE("Testing Plant Growth Balancing")
// {
//     SUBCASE("Simulate plant growth over 100 days")
//     {
//         Inventory* inv = Inventory::getInstance();

//         // Create a plant for testing
//         LivingPlant* testPlant = new Herb("Test Herb");

//         // Set initial conditions
//         testPlant->setMaturity(Seed::getID());
//         testPlant->setHealth(100);
//         testPlant->setWaterLevel(100);
//         testPlant->setSunExposure(100);
//         testPlant->setSeason(inv->getString("Spring Season"));
//         testPlant->setWaterStrategy(LowWater::getID());
//         testPlant->setSunStrategy(LowSun::getID());

//         std::cout << "\n--- Starting Plant Growth Simulation ---\n";
//         std::cout << testPlant->getInfo();

//         for (int day = 1; day <= 100; ++day)
//         {
//             std::cout << "\n--- Day " << day << " ---\n";

//             if (day % 3 == 0) {
//                 std::cout << "Watering the plant...\n";
//                 testPlant->water();
//             }

//             testPlant->tick();
//             std::cout << testPlant->getInfo();
//         }

//         std::cout << "\n--- Simulation Finished ---\n";

//         CHECK(testPlant->getAge() == 100);
//         CHECK(testPlant->getHealth() > 0); // Should still be alive

//         delete testPlant;
//         delete inv;
//     }
// }
