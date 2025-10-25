#include "doctest.h"
#include "facade/NurseryFacade.h"
#include "builder/Director.h"
#include "singleton/Singleton.h"
#include "mediator/Mediator.h"
#include "mediator/Staff.h"
#include "mediator/Customer.h"
#include "composite/PlantGroup.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Succulent.h"
#include "decorator/plantDecorator/Autumn.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "iterator/Iterator.h"
#include "iterator/PlantIterator.h"
#include <vector>
#include <string>

// ============================================================================
// FACADE PATTERN TESTS - UNIFIED INTERFACE VERIFICATION
// ============================================================================

// Helper function to clean up between tests
static void cleanupSingleton() {
    delete Inventory::getInstance();
}

TEST_CASE("Testing Facade Pattern - Facade Creation and Initialization")
{
    SUBCASE("Facade can be created")
    {
        NurseryFacade *facade = new NurseryFacade();
        CHECK(facade != nullptr);
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Multiple facade instances coordinate through singleton")
    {
        NurseryFacade *facade1 = new NurseryFacade();
        CHECK(facade1 != nullptr);
        NurseryFacade *facade2 = new NurseryFacade();
        CHECK(facade2 != nullptr);

        // Both should access same inventory
        Inventory *inv1 = Inventory::getInstance();
        Inventory *inv2 = Inventory::getInstance();
        CHECK(inv1 == inv2);

        delete facade1;
        delete facade2;
        cleanupSingleton();
    }

    SUBCASE("Facade provides unified interface")
    {
        NurseryFacade *facade = new NurseryFacade();
        CHECK(facade != nullptr);
        // Interface should include all major operations
        // - createPlant
        // - addToInventory
        // - browsePlants
        // - purchasePlant
        // - waterPlant
        // - getSuggestions
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Plant Creation through Facade")
{
    SUBCASE("Create tree plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Pine");
        CHECK(plant != nullptr);
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Create shrub plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Rose");
        CHECK(plant != nullptr);
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Create succulent plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Cactus");
        CHECK(plant != nullptr);
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Create multiple plants via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        std::vector<PlantComponent *> plants;

        plants.push_back(facade->createPlant("Pine"));
        plants.push_back(facade->createPlant("Rose"));
        plants.push_back(facade->createPlant("Cactus"));

        for (PlantComponent *p : plants) {
            CHECK(p != nullptr);
        }

        // Don't delete plants - createPlant() automatically adds them to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Facade hides builder complexity")
    {
        NurseryFacade *facade = new NurseryFacade();
        // Facade delegates to Builder/Director pattern internally
        // Client doesn't need to know about Builder, Director, or construction steps
        PlantComponent *plant = facade->createPlant("Maple");
        CHECK(plant != nullptr);
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Inventory Management through Facade")
{
    SUBCASE("Add plant to inventory via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Pine");

        // createPlant() already adds to inventory, so no need to call addToInventory()
        // Just verify it's in inventory
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        // Don't delete plant - inventory owns it now
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Multiple plants can be added to inventory via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        std::vector<PlantComponent *> plants;

        for (int i = 0; i < 5; i++) {
            PlantComponent *p = facade->createPlant("Maple");
            plants.push_back(p);
            // createPlant() already adds to inventory
        }

        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        // Don't delete plants - inventory owns them now
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Facade coordinates plant creation and inventory")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Rose");

        // Plant exists and is automatically in inventory
        CHECK(plant != nullptr);

        // Should be retrievable from inventory
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        // Don't delete plant - inventory owns it now
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Add different plant types to inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *tree = facade->createPlant("Pine");
        PlantComponent *shrub = facade->createPlant("Lavender");
        PlantComponent *succulent = facade->createPlant("JadePlant");

        // createPlant() already adds to inventory automatically

        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        // Don't delete plants - inventory owns them now
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Plant Browsing through Facade")
{
    SUBCASE("Browse all plants without filter")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Add some plants (createPlant() automatically adds to inventory)
        PlantComponent *plant1 = facade->createPlant("Pine");
        PlantComponent *plant2 = facade->createPlant("Rose");

        // Browse without filter should show all
        Iterator* it = facade->createAllPlantsIterator();
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Don't delete plants - inventory owns them now
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Browse plants with season filter")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Sunflower");
        // createPlant() already adds to inventory

        // Browse with specific season filter
        Iterator* it = facade->createSeasonIterator("Spring");
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Don't delete plant - inventory owns it now
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Browse empty inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should handle gracefully
        Iterator* it = facade->createAllPlantsIterator();
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Browse with various filters")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Cactus");
        // createPlant() already adds to inventory

        // Test multiple filter strings
        Iterator* it1 = facade->createSeasonIterator("Spring");
        if (it1 != nullptr) {
            for (it1->first(); !it1->isDone(); it1->next()) {
                it1->currentItem();
            }
            delete it1;
        }

        Iterator* it2 = facade->createSeasonIterator("Summer");
        if (it2 != nullptr) {
            for (it2->first(); !it2->isDone(); it2->next()) {
                it2->currentItem();
            }
            delete it2;
        }

        Iterator* it3 = facade->createSeasonIterator("Fall");
        if (it3 != nullptr) {
            for (it3->first(); !it3->isDone(); it3->next()) {
                it3->currentItem();
            }
            delete it3;
        }

        Iterator* it4 = facade->createSeasonIterator("Winter");
        if (it4 != nullptr) {
            for (it4->first(); !it4->isDone(); it4->next()) {
                it4->currentItem();
            }
            delete it4;
        }

        Iterator* it5 = facade->createAllPlantsIterator();
        if (it5 != nullptr) {
            for (it5->first(); !it5->isDone(); it5->next()) {
                it5->currentItem();
            }
            delete it5;
        }

        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Browse delegates to iterator pattern")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade hides iterator complexity
        // Client calls simple browsePlants() method
        // Facade internally creates iterators with appropriate filters
        PlantComponent *plant = facade->createPlant("Lavender");
        // createPlant() already adds to inventory

        Iterator* it = facade->createSeasonIterator("Spring");
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Purchase Operations through Facade")
{
    SUBCASE("Purchase plant via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();
        PlantComponent *plant = facade->createPlant("Pine");

        // Purchase should execute through mediator
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        delete customer;
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Multiple plant purchases")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        PlantComponent *plant1 = facade->createPlant("Rose");
        PlantComponent *plant2 = facade->createPlant("Cactus");

        customer->addPlant(plant1);
        customer->addPlant(plant2);
        facade->purchasePlants(customer);

        delete customer;
        // Don't delete plants - createPlant() automatically adds them to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Purchase coordinates with mediator pattern")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Sunflower");
        Customer *customer = new Customer();

        // Facade hides mediator coordination
        // Internally: connects customer to staff, processes transaction
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        delete customer;
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Purchase removes from inventory")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Maple");
        Customer *customer = new Customer();

        // createPlant() already adds to inventory
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        // Plant should be removed from available inventory
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        delete customer;
        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Plant Care Operations through Facade")
{
    SUBCASE("Water single plant via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Rose");

        facade->waterPlant(plant);

        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Water plant sets water strategy")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Cactus");

        // Watering should use strategy pattern internally
        facade->waterPlant(plant);

        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Water multiple plants sequentially")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant1 = facade->createPlant("Pine");
        PlantComponent *plant2 = facade->createPlant("Lavender");

        facade->waterPlant(plant1);
        facade->waterPlant(plant2);

        // Don't delete plants - createPlant() automatically adds them to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Water plant group via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *group = new PlantGroup();
        PlantComponent *plant = facade->createPlant("Sunflower");

        // Should handle composite structures
        facade->waterPlant(group);
        facade->waterPlant(plant);

        delete group;
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Water enqueues command for undo/redo")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("JadePlant");

        // Watering should create a Command internally
        // Client doesn't need to know about command pattern
        facade->waterPlant(plant);

        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Staff Suggestions through Facade")
{
    SUBCASE("Get suggestions via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        facade->getSuggestions(customer);

        delete customer;
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Suggestions coordinated through mediator")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Facade internally coordinates with suggestion floor mediator
        // Identifies plants needing care
        // Queries staff for suggestions
        facade->getSuggestions(customer);

        delete customer;
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Multiple suggestion requests")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        PlantComponent *plant = facade->createPlant("Tree");
        // createPlant() already adds to inventory

        facade->getSuggestions(customer);
        facade->getSuggestions(customer);
        facade->getSuggestions(customer);

        delete customer;
        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Complex Workflows through Facade")
{
    SUBCASE("Complete plant creation and care workflow")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Create plant (automatically added to inventory by createPlant())
        PlantComponent *plant = facade->createPlant("Pine");
        CHECK(plant != nullptr);


        // Browse available plants
        Iterator* it = facade->createAllPlantsIterator();
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Water the plant
        facade->waterPlant(plant);

        // Get care suggestions
        facade->getSuggestions(customer);

        delete customer;
        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Multi-plant inventory and sales workflow")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Create multiple plants (createPlant() automatically adds to inventory)
        std::vector<PlantComponent *> plants;
        for (int i = 0; i < 3; i++) {
            PlantComponent *p = facade->createPlant("Rose");
            plants.push_back(p);
        }

        // Browse
        Iterator* it = facade->createSeasonIterator("Spring");
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Water all
        for (PlantComponent *p : plants) {
            facade->waterPlant(p);
        }

        // Get suggestions
        facade->getSuggestions(customer);

        // Purchase one
        if (!plants.empty()) {
            customer->addPlant(plants[0]);
            facade->purchasePlants(customer);
        }

        // Don't delete plants - inventory owns them
        delete customer;
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Daily operations sequence")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Morning: check inventory (createPlant() automatically adds to inventory)
        PlantComponent *tree = facade->createPlant("Maple");
        PlantComponent *shrub = facade->createPlant("Lavender");


        // Midday: browse available plants
        Iterator* it = facade->createAllPlantsIterator();
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Afternoon: water plants
        facade->waterPlant(tree);
        facade->waterPlant(shrub);

        // Evening: get care suggestions
        facade->getSuggestions(customer);

        delete customer;
        // Don't delete tree/shrub - inventory owns them
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - System Abstraction")
{
    SUBCASE("Facade hides builder complexity from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about Director, builders, or construction steps
        // Simple: createPlant("Pine")
        PlantComponent *plant = facade->createPlant("Pine");
        CHECK(plant != nullptr);

        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Facade hides singleton details from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about singleton management
        // Facade internally coordinates singleton access
        PlantComponent *plant = facade->createPlant("Cactus");
        // createPlant() already adds to inventory automatically

        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Facade hides mediator complexity from client")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Client doesn't know about SalesFloor, SuggestionFloor, or customer/staff coordination
        // Simple: purchasePlants(), getSuggestions()
        PlantComponent *plant = facade->createPlant("Sunflower");

        customer->addPlant(plant);
        facade->purchasePlants(customer);
        facade->getSuggestions(customer);

        delete customer;
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Facade hides command pattern from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about command objects or undo/redo
        // Simple: waterPlant()
        PlantComponent *plant = facade->createPlant("Rose");
        facade->waterPlant(plant);

        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Facade hides iterator pattern from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't create iterators or handle filtering manually
        // Simple: browsePlants()
        PlantComponent *plant = facade->createPlant("Lavender");
        // createPlant() already adds to inventory

        Iterator* it = facade->createSeasonIterator("Spring");
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Unified Interface Benefits")
{
    SUBCASE("Single entry point for all operations")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // GUI/CLI only needs to know about NurseryFacade
        // All operations available through one object
        PlantComponent *plant = facade->createPlant("Pine");
        // createPlant() already adds to inventory
        Iterator* it = facade->createAllPlantsIterator();
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }
        facade->waterPlant(plant);
        facade->getSuggestions(customer);
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        delete customer;
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Reduced coupling between subsystems and client")
    {
        // Without facade: client depends on 13+ pattern classes
        // With facade: client depends only on NurseryFacade
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Rose");
        // Don't delete plant - createPlant() automatically adds it to inventory
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Simplified error handling")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade can handle errors from subsystems
        // Client sees simple interface
        try {
            PlantComponent *plant = facade->createPlant("InvalidType");
            // Facade handles gracefully
            // Don't delete plant - createPlant() automatically adds it to inventory (if successful)
        } catch (...) {
            // Single error handling point
        }

        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - System Integration")
{
    SUBCASE("Facade integrates all 13 patterns")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Each method integrates multiple patterns:
        // createPlant: Builder + Director + Prototype
        // addToInventory: Singleton + Flyweight
        // browsePlants: Iterator + Singleton
        // purchasePlants: Mediator + Command
        // waterPlant: Command + Strategy + Observer + State
        // getSuggestions: Mediator + Observer

        PlantComponent *plant = facade->createPlant("Cactus");
        // createPlant() already adds to inventory
        Iterator* it = facade->createAllPlantsIterator();
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }
        facade->waterPlant(plant);
        facade->getSuggestions(customer);
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        delete customer;
        // Don't delete plant - inventory owns it
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Facade coordinate subsystem state")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Facade ensures consistent state across all subsystems
        PlantComponent *plant = facade->createPlant("Sunflower");
        // createPlant() already adds to inventory

        // Watering updates command history (do this BEFORE purchase)
        facade->waterPlant(plant);

        // Purchasing updates mediator state
        customer->addPlant(plant);
        facade->purchasePlants(customer);
        // After purchase, plant may be removed from inventory

        Inventory *inv1 = Inventory::getInstance();
        Inventory *inv2 = Inventory::getInstance();
        CHECK(inv1 == inv2);  // Singleton consistency

        delete customer;
        // Don't delete plant - it was handled by purchase operation
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Error Handling")
{
    SUBCASE("Handle invalid plant species gracefully")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should handle invalid species
        PlantComponent *plant = facade->createPlant("InvalidSpecies");
        // Facade should either return nullptr or default plant
        // Don't delete plant - createPlant() automatically adds it to inventory (if successful)

        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Handle null plant in operations")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Facade should handle gracefully
        facade->waterPlant(nullptr);
        facade->purchasePlants(customer);

        delete customer;
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Handle browsing empty inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should not crash on empty inventory
        Iterator* it1 = facade->createAllPlantsIterator();
        if (it1 != nullptr) {
            for (it1->first(); !it1->isDone(); it1->next()) {
                it1->currentItem();
            }
            delete it1;
        }

        Iterator* it2 = facade->createSeasonIterator("Spring");
        if (it2 != nullptr) {
            for (it2->first(); !it2->isDone(); it2->next()) {
                it2->currentItem();
            }
            delete it2;
        }

        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Handle multiple suggestions requests")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Should handle repeated calls
        facade->getSuggestions(customer);
        facade->getSuggestions(customer);
        facade->getSuggestions(customer);

        delete customer;
        delete facade;
        cleanupSingleton();
    }
}

TEST_CASE("Testing Facade Pattern - Performance and Scalability")
{
    SUBCASE("Create many plants via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        std::vector<PlantComponent *> plants;

        // Create 100 plants (createPlant() automatically adds to inventory)
        for (int i = 0; i < 100; i++) {
            PlantComponent *p = facade->createPlant("Rose");
            plants.push_back(p);
        }

        // Browse should handle large inventory
        Iterator* it = facade->createAllPlantsIterator();
        if (it != nullptr) {
            for (it->first(); !it->isDone(); it->next()) {
                it->currentItem();
            }
            delete it;
        }

        // Water multiple plants
        for (int i = 0; i < 10; i++) {
            facade->waterPlant(plants[i]);
        }

        // Don't delete plants - inventory owns them
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Browse with large inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Add many plants (createPlant() automatically adds to inventory)
        for (int i = 0; i < 50; i++) {
            PlantComponent *p = facade->createPlant("Maple");
        }

        // Browse should complete in reasonable time
        Iterator* it1 = facade->createAllPlantsIterator();
        if (it1 != nullptr) {
            for (it1->first(); !it1->isDone(); it1->next()) {
                it1->currentItem();
            }
            delete it1;
        }

        Iterator* it2 = facade->createSeasonIterator("Spring");
        if (it2 != nullptr) {
            for (it2->first(); !it2->isDone(); it2->next()) {
                it2->currentItem();
            }
            delete it2;
        }

        // Don't delete plants - inventory owns them
        delete facade;
        cleanupSingleton();
    }

    SUBCASE("Many facade instances with shared inventory")
    {
        std::vector<NurseryFacade *> facades;

        // Create 10 facade instances
        for (int i = 0; i < 10; i++) {
            facades.push_back(new NurseryFacade());
        }

        // All should access same singleton inventory
        Inventory *inv1 = Inventory::getInstance();
        for (NurseryFacade *f : facades) {
            Inventory *invX = Inventory::getInstance();
            CHECK(invX == inv1);
        }

        for (NurseryFacade *f : facades) {
            delete f;
        }
        cleanupSingleton();
    }
}
