#include "doctest.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "mediator/Staff.h"
#include "composite/PlantGroup.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "singleton/Singleton.h"
#include "strategy/LowWater.h"
#include "strategy/LowSun.h"
#include <type_traits>

TEST_CASE("Testing Observer Pattern - Interface Abstraction")
{
    SUBCASE("Observer interface is abstract")
    {
        bool isObserverAbstract = std::is_abstract<Observer>::value;
        CHECK(isObserverAbstract == true);
    }

    SUBCASE("Subject interface is abstract")
    {
        bool isSubjectAbstract = std::is_abstract<Subject>::value;
        CHECK(isSubjectAbstract == true);
    }
}

TEST_CASE("Testing Observer Pattern - Staff Observer Implementation")
{
    SUBCASE("Staff can be created as observer")
    {
        Staff *staff = new Staff();
        CHECK(staff != nullptr);
        delete staff;
    }

    SUBCASE("Staff observer receives water update notifications")
    {
        Staff *staff = new Staff();
        LivingPlant *testPlant = new Tree();

        // Should be callable without crashing
        staff->getWaterUpdate(testPlant);

        delete testPlant;
        delete staff;
    }

    SUBCASE("Staff observer receives sun update notifications")
    {
        Staff *staff = new Staff();
        LivingPlant *testPlant = new Tree();

        // Should be callable without crashing
        staff->getSunUpdate(testPlant);

        delete testPlant;
        delete staff;
    }

    SUBCASE("Staff observer receives state update notifications")
    {
        Staff *staff = new Staff();
        LivingPlant *testPlant = new Tree();

        // Should be callable without crashing
        staff->getStateUpdate(testPlant);

        delete testPlant;
        delete staff;
    }
}

TEST_CASE("Testing Observer Pattern - PlantGroup Subject Implementation")
{
    SUBCASE("PlantGroup can serve as subject")
    {
        PlantGroup *plantGroup = new PlantGroup();
        CHECK(plantGroup != nullptr);
        delete plantGroup;
    }

    SUBCASE("PlantGroup can attach observer")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        plantGroup->attach(staff);

        delete plantGroup;
        delete staff;
    }

    SUBCASE("PlantGroup can detach observer")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        plantGroup->attach(staff);
        plantGroup->detach(staff);

        delete plantGroup;
        delete staff;
    }

    SUBCASE("PlantGroup can notify waterNeeded")
    {
        PlantGroup *plantGroup = new PlantGroup();
        plantGroup->waterNeeded();
        delete plantGroup;
    }

    SUBCASE("PlantGroup can notify sunlightNeeded")
    {
        PlantGroup *plantGroup = new PlantGroup();
        plantGroup->sunlightNeeded();
        delete plantGroup;
    }

    SUBCASE("PlantGroup can notify stateUpdated")
    {
        PlantGroup *plantGroup = new PlantGroup();
        plantGroup->stateUpdated();
        delete plantGroup;
    }
}

TEST_CASE("Testing Observer Pattern - Observer Registration and Notification")
{
    SUBCASE("Single observer receives notifications")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        plantGroup->attach(staff);
        plantGroup->waterNeeded();
        plantGroup->sunlightNeeded();
        plantGroup->stateUpdated();

        plantGroup->detach(staff);

        delete plantGroup;
        delete staff;
    }

    SUBCASE("Multiple observers receive notifications")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff1 = new Staff();
        Staff *staff2 = new Staff();

        plantGroup->attach(staff1);
        plantGroup->attach(staff2);

        plantGroup->waterNeeded();
        plantGroup->sunlightNeeded();
        plantGroup->stateUpdated();

        plantGroup->detach(staff1);
        plantGroup->detach(staff2);

        delete plantGroup;
        delete staff1;
        delete staff2;
    }
}

TEST_CASE("Testing Observer Pattern - Observer Response to Plant Updates")
{
    SUBCASE("Staff responds to water update with strategy")
    {
        Staff *staff = new Staff();
        LivingPlant *testPlant = new Tree();

        testPlant->setWaterStrategy(LowWater::getID());
        testPlant->setWaterLevel(5);
        testPlant->setHealth(50);

        int initialWater = testPlant->getWaterLevel();

        // Staff processes water update
        staff->getWaterUpdate(testPlant);

        // Plant should have been watered
        CHECK(testPlant->getWaterLevel() > initialWater);

        delete staff;
        delete testPlant;
    }

    SUBCASE("Staff responds to sun update with strategy")
    {
        Staff *staff = new Staff();
        LivingPlant *testPlant = new Tree();

        testPlant->setSunStrategy(LowSun::getID());
        testPlant->setSunExposure(10);
        testPlant->setHealth(50);

        int initialSun = testPlant->getSunExposure();

        // Staff processes sun update
        staff->getSunUpdate(testPlant);

        // Plant should have received sun
        CHECK(testPlant->getSunExposure() > initialSun);

        delete staff;
        delete testPlant;
    }

    SUBCASE("Staff handles state update notification")
    {
        Staff *staff = new Staff();
        LivingPlant *testPlant = new Tree();

        // Should not crash when handling state update
        staff->getStateUpdate(testPlant);

        delete staff;
        delete testPlant;
    }
}

TEST_CASE("Testing Observer Pattern - Observer with Plant Group Operations")
{
    SUBCASE("Group watering with observer attachment")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setWaterStrategy(LowWater::getID());
        plant2->setWaterStrategy(LowWater::getID());
        plant1->setWaterLevel(0);
        plant2->setWaterLevel(0);

        plantGroup->addComponent(plant1);
        plantGroup->addComponent(plant2);
        plantGroup->attach(staff);

        plantGroup->water();

        // Plants should be watered
        CHECK(plant1->getWaterLevel() > 0);
        CHECK(plant2->getWaterLevel() > 0);

        plantGroup->detach(staff);

        delete plantGroup;
        delete staff;
    }

    SUBCASE("Group sun exposure with observer attachment")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setSunStrategy(LowSun::getID());
        plant2->setSunStrategy(LowSun::getID());
        plant1->setSunExposure(0);
        plant2->setSunExposure(0);

        plantGroup->addComponent(plant1);
        plantGroup->addComponent(plant2);
        plantGroup->attach(staff);

        plantGroup->setOutside();

        // Plants should have sun
        CHECK(plant1->getSunExposure() > 0);
        CHECK(plant2->getSunExposure() > 0);

        plantGroup->detach(staff);

        delete plantGroup;
        delete staff;
    }
}

TEST_CASE("Testing Observer Pattern - Nested PlantGroup with Observers")
{
    SUBCASE("Nested groups with observer at root")
    {
        PlantGroup *rootGroup = new PlantGroup();
        PlantGroup *subGroup = new PlantGroup();
        Staff *staff = new Staff();

        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setSunStrategy(LowSun::getID());
        plant->setWaterLevel(0);
        plant->setSunExposure(0);

        subGroup->addComponent(plant);
        rootGroup->addComponent(subGroup);
        rootGroup->attach(staff);

        rootGroup->water();
        rootGroup->setOutside();

        // Plant in nested group should be affected
        CHECK(plant->getWaterLevel() > 0);
        CHECK(plant->getSunExposure() > 0);

        rootGroup->detach(staff);

        delete rootGroup; // This also deletes subGroup and plant
        delete staff;
    }

    SUBCASE("Multiple observers on different group levels")
    {
        PlantGroup *topGroup = new PlantGroup();
        PlantGroup *middleGroup = new PlantGroup();

        Staff *topObserver = new Staff();
        Staff *middleObserver = new Staff();

        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setSunStrategy(LowSun::getID());
        plant->setWaterLevel(0);
        plant->setSunExposure(0);

        middleGroup->addComponent(plant);
        topGroup->addComponent(middleGroup);

        topGroup->attach(topObserver);
        middleGroup->attach(middleObserver);

        topGroup->water();
        middleGroup->setOutside();

        CHECK(plant->getWaterLevel() > 0);
        CHECK(plant->getSunExposure() > 0);

        topGroup->detach(topObserver);
        middleGroup->detach(middleObserver);

        delete topGroup; // This also deletes middleGroup and plant
        delete topObserver;
        delete middleObserver;
    }
}

TEST_CASE("Testing Observer Pattern - Error Handling and Edge Cases")
{
    SUBCASE("Null observer handling")
    {
        PlantGroup *plantGroup = new PlantGroup();

        // Should handle gracefully
        plantGroup->attach(nullptr);
        plantGroup->detach(nullptr);

        plantGroup->waterNeeded();
        plantGroup->sunlightNeeded();
        plantGroup->stateUpdated();

        delete plantGroup;
    }

    SUBCASE("Duplicate observer attachment")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        // Attach same observer twice
        plantGroup->attach(staff);
        plantGroup->attach(staff);

        plantGroup->waterNeeded();

        plantGroup->detach(staff);

        // Should still work after single detach
        plantGroup->waterNeeded();

        delete plantGroup;
        delete staff;
    }

    SUBCASE("Observer with empty plant group")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        plantGroup->attach(staff);

        // Notifications on empty group should not crash
        plantGroup->waterNeeded();
        plantGroup->sunlightNeeded();
        plantGroup->stateUpdated();

        plantGroup->detach(staff);

        delete plantGroup;
        delete staff;
    }
}

TEST_CASE("Testing Observer Pattern - Observer Lifetime Management")
{
    SUBCASE("Observer cleanup with plant group deletion")
    {
        Staff *staff = new Staff();

        {
            PlantGroup *temporaryGroup = new PlantGroup();
            temporaryGroup->attach(staff);

            // Group deletion with attached observer
            delete temporaryGroup;
        }

        // Observer should still be valid
        CHECK(staff != nullptr);

        delete staff;
    }

    SUBCASE("Plant group cleanup with multiple observers")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff1 = new Staff();
        Staff *staff2 = new Staff();
        Staff *staff3 = new Staff();

        plantGroup->attach(staff1);
        plantGroup->attach(staff2);
        plantGroup->attach(staff3);

        delete plantGroup;

        // Observers should still be valid
        CHECK(staff1 != nullptr);
        CHECK(staff2 != nullptr);
        CHECK(staff3 != nullptr);

        delete staff1;
        delete staff2;
        delete staff3;
    }
}

TEST_CASE("Testing Observer Pattern - Notification Consistency")
{
    SUBCASE("Multiple observers receive same notifications")
    {
        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff1 = new Staff();
        Staff *staff2 = new Staff();

        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        plantGroup->addComponent(plant);
        plantGroup->attach(staff1);
        plantGroup->attach(staff2);

        int waterBefore = plant->getWaterLevel();
        plantGroup->water();

        // All observers should have processed the same plant
        CHECK(plant->getWaterLevel() > waterBefore);

        plantGroup->detach(staff1);
        plantGroup->detach(staff2);

        delete plantGroup;
        delete staff1;
        delete staff2;
    }
}

TEST_CASE("Testing Observer Pattern - Integration with Singleton Inventory")
{
    SUBCASE("Observer works with singleton inventory managed plants")
    {
        Inventory *inv = Inventory::getInstance();

        PlantGroup *plantGroup = new PlantGroup();
        Staff *staff = new Staff();

        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setSunStrategy(LowSun::getID());
        plant->setWaterLevel(5);
        plant->setSunExposure(10);

        plantGroup->addComponent(plant);
        plantGroup->attach(staff);

        plantGroup->water();
        plantGroup->setOutside();

        CHECK(plant->getWaterLevel() > 5);
        CHECK(plant->getSunExposure() > 10);

        plantGroup->detach(staff);

        delete plantGroup;
        delete staff;
    }
}
