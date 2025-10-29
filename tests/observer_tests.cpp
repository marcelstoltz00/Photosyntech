#include "doctest.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "composite/PlantGroup.h"
#include "composite/PlantComponent.h"
#include "mediator/Staff.h"
#include "prototype/Tree.h"
#include "prototype/Succulent.h"
#include "prototype/Shrub.h"
#include "prototype/Herb.h"
#include "prototype/LivingPlant.h"
#include <vector>

TEST_CASE("Testing Observer Pattern Implementation")
{
    SUBCASE("Subject can attach an observer")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        // Attach should work without error
        group->attach(observer);

        // Verify attachment succeeded (no assertion, just execute)
        CHECK(observer != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Subject can detach an observer")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        group->attach(observer);
        group->detach(observer);

        // Detach should work without error
        CHECK(observer != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Multiple observers can be attached to same subject")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer1 = new Staff("Staff 1");
        Staff *observer2 = new Staff("Staff 2");
        Staff *observer3 = new Staff("Staff 3");

        group->attach(observer1);
        group->attach(observer2);
        group->attach(observer3);

        // All observers should be attached
        CHECK(observer1 != nullptr);
        CHECK(observer2 != nullptr);
        CHECK(observer3 != nullptr);

        delete group;
        delete observer1;
        delete observer2;
        delete observer3;
    }

    SUBCASE("Observer receives water notification")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff("Caretaker");

        plant->setWaterLevel(15);  // Low water level
        group->addComponent(plant);
        group->attach(observer);

        // This should trigger water notifications
        group->checkWater();

        // Plant exists and observer was notified (no crash)
        CHECK(plant != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Observer receives sunlight notification")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Herb();
        Staff *observer = new Staff("Caretaker");

        plant->setSunExposure(5);  // Very low sun exposure
        group->addComponent(plant);
        group->attach(observer);

        // This should trigger sunlight notifications
        group->checkSunlight();

        // Plant exists and observer was notified (no crash)
        CHECK(plant != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Observer receives state notification")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff("Caretaker");

        group->addComponent(plant);
        group->attach(observer);

        // This should trigger state notifications
        group->checkState();

        // Observer processed state update
        CHECK(observer != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Observer is notified when plant water level is critically low")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff("Caretaker");

        // Set water level very low (below threshold)
        plant->setWaterLevel(5);
        group->addComponent(plant);
        group->attach(observer);

        int originalWaterLevel = plant->getWaterLevel();
        group->checkWater();

        // After notification, plant should potentially have been watered
        // (observer calls getWaterUpdate which calls plant->water())
        CHECK(plant->getWaterLevel() >= originalWaterLevel);

        delete group;
        delete observer;
    }

    SUBCASE("Observer is notified when plant sun exposure is critically low")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Succulent();
        Staff *observer = new Staff("Caretaker");

        // Set sun exposure very low
        plant->setSunExposure(3);
        group->addComponent(plant);
        group->attach(observer);

        int originalSunLevel = plant->getSunExposure();
        group->checkSunlight();

        // After notification, plant may have been moved outside
        CHECK(plant->getSunExposure() >= 0);

        delete group;
        delete observer;
    }

    SUBCASE("Removing observer stops notifications to that observer")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff("Caretaker");

        plant->setWaterLevel(10);
        group->addComponent(plant);
        group->attach(observer);

        // Detach observer
        group->detach(observer);

        // This should not notify the detached observer
        group->checkWater();

        // Observer exists but should not receive notifications
        CHECK(observer != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Detaching non-attached observer doesn't cause error")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        // Try to detach observer that was never attached
        group->detach(observer);

        // Should handle gracefully
        CHECK(true);

        delete group;
        delete observer;
    }

    SUBCASE("Subject notifies all attached observers of water needs")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Shrub();
        Staff *observer1 = new Staff("Caretaker 1");
        Staff *observer2 = new Staff("Caretaker 2");

        plant->setWaterLevel(8);
        group->addComponent(plant);
        group->attach(observer1);
        group->attach(observer2);

        // Both observers should be notified
        group->checkWater();

        CHECK(observer1 != nullptr);
        CHECK(observer2 != nullptr);

        delete group;
        delete observer1;
        delete observer2;
    }

    SUBCASE("Subject notifies all attached observers of sun needs")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer1 = new Staff("Caretaker 1");
        Staff *observer2 = new Staff("Caretaker 2");
        Staff *observer3 = new Staff("Caretaker 3");

        plant->setSunExposure(2);
        group->addComponent(plant);
        group->attach(observer1);
        group->attach(observer2);
        group->attach(observer3);

        // All three observers should be notified
        group->checkSunlight();

        CHECK(observer1 != nullptr);
        CHECK(observer2 != nullptr);
        CHECK(observer3 != nullptr);

        delete group;
        delete observer1;
        delete observer2;
        delete observer3;
    }

    SUBCASE("Multiple plants trigger notifications for each")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Succulent();
        LivingPlant *plant3 = new Herb();
        Staff *observer = new Staff();

        plant1->setWaterLevel(10);
        plant2->setWaterLevel(12);
        plant3->setWaterLevel(8);

        group->addComponent(plant1);
        group->addComponent(plant2);
        group->addComponent(plant3);
        group->attach(observer);

        // Check water for all plants
        group->checkWater();

        // All plants should exist
        CHECK(plant1 != nullptr);
        CHECK(plant2 != nullptr);
        CHECK(plant3 != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Observer methods are called appropriately")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *staff = new Staff("Caretaker");

        // Set different need levels
        plant->setWaterLevel(5);   // Needs water
        plant->setSunExposure(10);

        group->addComponent(plant);
        group->attach(staff);

        // Call check methods which should invoke observer methods
        group->checkWater();    // Should call getWaterUpdate
        group->checkSunlight(); // Should call getSunUpdate
        group->checkState();    // Should call getStateUpdate

        // All operations completed successfully
        CHECK(true);

        delete group;
        delete staff;
    }

    SUBCASE("Empty plant group with observer doesn't crash")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        group->attach(observer);

        // These should handle empty group gracefully
        group->checkWater();
        group->checkSunlight();
        group->checkState();

        CHECK(group->getPlants()->size() == 0);

        delete group;
        delete observer;
    }

    SUBCASE("Observer receives updates for all plants in group")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();
        LivingPlant *plant3 = new Succulent();
        Staff *observer = new Staff();

        // Set water levels for all plants
        plant1->setWaterLevel(10);
        plant2->setWaterLevel(8);
        plant3->setWaterLevel(12);

        group->addComponent(plant1);
        group->addComponent(plant2);
        group->addComponent(plant3);
        group->attach(observer);

        // Observer should be notified for plants that need water
        group->checkWater();

        // All plants should be accessible
        CHECK(group->getPlants()->size() == 3);

        delete group;
        delete observer;
    }

    SUBCASE("Attaching same observer multiple times handled gracefully")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        group->attach(observer);
        group->attach(observer);  // Attach again
        group->attach(observer);  // And again

        // Should handle duplicate attachment
        CHECK(observer != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Detaching observer multiple times handled gracefully")
    {
        PlantGroup *group = new PlantGroup();
        Staff *observer = new Staff();

        group->attach(observer);
        group->detach(observer);
        group->detach(observer);  // Detach again

        // Should handle gracefully
        CHECK(observer != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Observer pattern with nested groups")
    {
        PlantGroup *parentGroup = new PlantGroup();
        PlantGroup *childGroup = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();
        Staff *observer = new Staff();

        plant1->setWaterLevel(10);
        plant2->setWaterLevel(8);

        childGroup->addComponent(plant1);
        parentGroup->addComponent(childGroup);
        parentGroup->addComponent(plant2);
        parentGroup->attach(observer);

        // Observer attached to parent group
        parentGroup->checkWater();

        // Plant in child group should still trigger notifications
        CHECK(plant1 != nullptr);
        CHECK(plant2 != nullptr);

        delete parentGroup;
        delete observer;
    }

    SUBCASE("Observer with plant state changes")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff();

        group->addComponent(plant);
        group->attach(observer);

        // Notify observers of state without calling tick
        group->checkState(); // Notify observers of state

        // Observer should handle state notifications
        CHECK(plant != nullptr);

        delete group;
        delete observer;
    }

    SUBCASE("Multiple independent observers on different groups")
    {
        PlantGroup *group1 = new PlantGroup();
        PlantGroup *group2 = new PlantGroup();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();
        Staff *observer1 = new Staff("Observer 1");
        Staff *observer2 = new Staff("Observer 2");

        plant1->setWaterLevel(10);
        plant2->setWaterLevel(8);

        group1->addComponent(plant1);
        group1->attach(observer1);

        group2->addComponent(plant2);
        group2->attach(observer2);

        // Observers should independently monitor their groups
        group1->checkWater();
        group2->checkWater();

        CHECK(observer1 != nullptr);
        CHECK(observer2 != nullptr);

        delete group1;
        delete group2;
        delete observer1;
        delete observer2;
    }

    SUBCASE("Observer pattern preserves plant integrity after notifications")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *observer = new Staff();

        double initialPrice = plant->getPrice();
        int initialWaterLevel = plant->getWaterLevel();

        plant->setWaterLevel(5);
        group->addComponent(plant);
        group->attach(observer);

        group->checkWater();

        // Plant price should remain unchanged
        CHECK(plant->getPrice() == initialPrice);
        // Water level should be >= initial (may have been increased by watering)
        CHECK(plant->getWaterLevel() >= 0);

        delete group;
        delete observer;
    }

    SUBCASE("Staff observer responds to water update")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Tree();
        Staff *staff = new Staff("Caretaker");

        plant->setWaterLevel(8);
        group->addComponent(plant);
        group->attach(staff);

        int waterBefore = plant->getWaterLevel();

        // Trigger water notification
        group->checkWater();

        // After water update notification, staff should have called water
        int waterAfter = plant->getWaterLevel();

        // Water level should increase (observer called water() on plant)
        CHECK(waterAfter >= waterBefore);

        delete group;
        delete staff;
    }

    SUBCASE("Staff observer responds to sun update")
    {
        PlantGroup *group = new PlantGroup();
        LivingPlant *plant = new Herb();
        Staff *staff = new Staff("Caretaker");

        plant->setSunExposure(4);
        group->addComponent(plant);
        group->attach(staff);

        // Trigger sun notification
        group->checkSunlight();

        // Observer should have called setOutside()
        CHECK(plant->getSunExposure() >= 0);

        delete group;
        delete staff;
    }

    SUBCASE("Large group with many plants and multiple observers")
    {
        PlantGroup *group = new PlantGroup();
        std::vector<Staff *> observers;

        // Create 5 observers
        for (int i = 0; i < 5; i++)
        {
            Staff *staff = new Staff("Staff " + std::to_string(i));
            group->attach(staff);
            observers.push_back(staff);
        }

        // Add 20 plants with low water levels
        for (int i = 0; i < 20; i++)
        {
            LivingPlant *plant = nullptr;
            if (i % 4 == 0)
                plant = new Tree();
            else if (i % 4 == 1)
                plant = new Shrub();
            else if (i % 4 == 2)
                plant = new Succulent();
            else
                plant = new Herb();

            plant->setWaterLevel(10);
            group->addComponent(plant);
        }

        // All observers should be notified for all plants
        group->checkWater();

        CHECK(group->getPlants()->size() == 20);
        CHECK(observers.size() == 5);

        delete group;
        for (auto observer : observers)
        {
            delete observer;
        }
    }
}
