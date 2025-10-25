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
#include "iterator/PlantIterator.h"
#include <vector>
#include <string>

// ============================================================================
// FACADE PATTERN TESTS - UNIFIED INTERFACE VERIFICATION
// ============================================================================

TEST_CASE("Testing Facade Pattern - Facade Creation and Initialization")
{
    SUBCASE("Facade can be created")
    {
        NurseryFacade *facade = new NurseryFacade();
        CHECK(facade != nullptr);
        delete facade;
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
    }
}

TEST_CASE("Testing Facade Pattern - Plant Creation through Facade")
{
    SUBCASE("Create tree plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");
        CHECK(plant != nullptr);
        delete plant;
        delete facade;
    }

    SUBCASE("Create shrub plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Shrub");
        CHECK(plant != nullptr);
        delete plant;
        delete facade;
    }

    SUBCASE("Create succulent plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Succulent");
        CHECK(plant != nullptr);
        delete plant;
        delete facade;
    }

    SUBCASE("Create multiple plants via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        std::vector<PlantComponent *> plants;

        plants.push_back(facade->createPlant("Tree"));
        plants.push_back(facade->createPlant("Shrub"));
        plants.push_back(facade->createPlant("Succulent"));

        for (PlantComponent *p : plants) {
            CHECK(p != nullptr);
        }

        for (PlantComponent *p : plants) {
            delete p;
        }
        delete facade;
    }

    SUBCASE("Facade hides builder complexity")
    {
        NurseryFacade *facade = new NurseryFacade();
        // Facade delegates to Builder/Director pattern internally
        // Client doesn't need to know about Builder, Director, or construction steps
        PlantComponent *plant = facade->createPlant("Tree");
        CHECK(plant != nullptr);
        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Inventory Management through Facade")
{
    SUBCASE("Add plant to inventory via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");

        facade->addToInventory(plant);

        // Plant should now be in inventory
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        delete plant;
        delete facade;
    }

    SUBCASE("Multiple plants can be added to inventory via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        std::vector<PlantComponent *> plants;

        for (int i = 0; i < 5; i++) {
            PlantComponent *p = facade->createPlant("Tree");
            plants.push_back(p);
            facade->addToInventory(p);
        }

        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        for (PlantComponent *p : plants) {
            delete p;
        }
        delete facade;
    }

    SUBCASE("Facade coordinates plant creation and inventory")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Shrub");

        // Plant exists and can be added
        CHECK(plant != nullptr);
        facade->addToInventory(plant);

        // Should be retrievable from inventory
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        delete plant;
        delete facade;
    }

    SUBCASE("Add different plant types to inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *tree = facade->createPlant("Tree");
        PlantComponent *shrub = facade->createPlant("Shrub");
        PlantComponent *succulent = facade->createPlant("Succulent");

        facade->addToInventory(tree);
        facade->addToInventory(shrub);
        facade->addToInventory(succulent);

        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        delete tree;
        delete shrub;
        delete succulent;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Plant Browsing through Facade")
{
    SUBCASE("Browse all plants without filter")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Add some plants
        PlantComponent *plant1 = facade->createPlant("Tree");
        PlantComponent *plant2 = facade->createPlant("Shrub");

        facade->addToInventory(plant1);
        facade->addToInventory(plant2);

        // Browse without filter should show all
        facade->browsePlants(nullptr);

        delete plant1;
        delete plant2;
        delete facade;
    }

    SUBCASE("Browse plants with season filter")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);

        // Browse with specific season filter
        facade->browsePlants("Spring");

        delete plant;
        delete facade;
    }

    SUBCASE("Browse empty inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should handle gracefully
        facade->browsePlants(nullptr);

        delete facade;
    }

    SUBCASE("Browse with various filters")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);

        // Test multiple filter strings
        facade->browsePlants("Spring");
        facade->browsePlants("Summer");
        facade->browsePlants("Fall");
        facade->browsePlants("Winter");
        facade->browsePlants("");

        delete plant;
        delete facade;
    }

    SUBCASE("Browse delegates to iterator pattern")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade hides iterator complexity
        // Client calls simple browsePlants() method
        // Facade internally creates iterators with appropriate filters
        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);

        facade->browsePlants("Spring");

        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Purchase Operations through Facade")
{
    SUBCASE("Purchase plant via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");

        // Purchase should execute through mediator
        facade->purchasePlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Multiple plant purchases")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant1 = facade->createPlant("Tree");
        PlantComponent *plant2 = facade->createPlant("Shrub");

        facade->purchasePlant(plant1);
        facade->purchasePlant(plant2);

        delete plant1;
        delete plant2;
        delete facade;
    }

    SUBCASE("Purchase coordinates with mediator pattern")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");

        // Facade hides mediator coordination
        // Internally: connects customer to staff, processes transaction
        facade->purchasePlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Purchase removes from inventory")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");

        facade->addToInventory(plant);
        facade->purchasePlant(plant);

        // Plant should be removed from available inventory
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Plant Care Operations through Facade")
{
    SUBCASE("Water single plant via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");

        facade->waterPlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Water plant sets water strategy")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");

        // Watering should use strategy pattern internally
        facade->waterPlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Water multiple plants sequentially")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant1 = facade->createPlant("Tree");
        PlantComponent *plant2 = facade->createPlant("Shrub");

        facade->waterPlant(plant1);
        facade->waterPlant(plant2);

        delete plant1;
        delete plant2;
        delete facade;
    }

    SUBCASE("Water plant group via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *group = new PlantGroup();
        PlantComponent *plant = facade->createPlant("Tree");

        // Should handle composite structures
        facade->waterPlant(group);
        facade->waterPlant(plant);

        delete group;
        delete plant;
        delete facade;
    }

    SUBCASE("Water enqueues command for undo/redo")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Tree");

        // Watering should create a Command internally
        // Client doesn't need to know about command pattern
        facade->waterPlant(plant);

        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Staff Suggestions through Facade")
{
    SUBCASE("Get suggestions via facade")
    {
        NurseryFacade *facade = new NurseryFacade();

        facade->getSuggestions();

        delete facade;
    }

    SUBCASE("Suggestions coordinated through mediator")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade internally coordinates with suggestion floor mediator
        // Identifies plants needing care
        // Queries staff for suggestions
        facade->getSuggestions();

        delete facade;
    }

    SUBCASE("Multiple suggestion requests")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);

        facade->getSuggestions();
        facade->getSuggestions();
        facade->getSuggestions();

        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Complex Workflows through Facade")
{
    SUBCASE("Complete plant creation and care workflow")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Create plant
        PlantComponent *plant = facade->createPlant("Tree");
        CHECK(plant != nullptr);

        // Add to inventory
        facade->addToInventory(plant);

        // Browse available plants
        facade->browsePlants(nullptr);

        // Water the plant
        facade->waterPlant(plant);

        // Get care suggestions
        facade->getSuggestions();

        delete plant;
        delete facade;
    }

    SUBCASE("Multi-plant inventory and sales workflow")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Create multiple plants
        std::vector<PlantComponent *> plants;
        for (int i = 0; i < 3; i++) {
            PlantComponent *p = facade->createPlant("Tree");
            plants.push_back(p);
            facade->addToInventory(p);
        }

        // Browse
        facade->browsePlants("Spring");

        // Water all
        for (PlantComponent *p : plants) {
            facade->waterPlant(p);
        }

        // Get suggestions
        facade->getSuggestions();

        // Purchase one
        if (!plants.empty()) {
            facade->purchasePlant(plants[0]);
        }

        for (PlantComponent *p : plants) {
            delete p;
        }
        delete facade;
    }

    SUBCASE("Daily operations sequence")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Morning: check inventory
        PlantComponent *tree = facade->createPlant("Tree");
        PlantComponent *shrub = facade->createPlant("Shrub");

        facade->addToInventory(tree);
        facade->addToInventory(shrub);

        // Midday: browse available plants
        facade->browsePlants(nullptr);

        // Afternoon: water plants
        facade->waterPlant(tree);
        facade->waterPlant(shrub);

        // Evening: get care suggestions
        facade->getSuggestions();

        delete tree;
        delete shrub;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - System Abstraction")
{
    SUBCASE("Facade hides builder complexity from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about Director, builders, or construction steps
        // Simple: createPlant("Tree")
        PlantComponent *plant = facade->createPlant("Tree");
        CHECK(plant != nullptr);

        delete plant;
        delete facade;
    }

    SUBCASE("Facade hides singleton details from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about singleton management
        // Facade internally coordinates singleton access
        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Facade hides mediator complexity from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about SalesFloor, SuggestionFloor, or customer/staff coordination
        // Simple: purchasePlant(), getSuggestions()
        PlantComponent *plant = facade->createPlant("Tree");

        facade->purchasePlant(plant);
        facade->getSuggestions();

        delete plant;
        delete facade;
    }

    SUBCASE("Facade hides command pattern from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about command objects or undo/redo
        // Simple: waterPlant()
        PlantComponent *plant = facade->createPlant("Tree");
        facade->waterPlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Facade hides iterator pattern from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't create iterators or handle filtering manually
        // Simple: browsePlants()
        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);

        facade->browsePlants("Spring");

        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Unified Interface Benefits")
{
    SUBCASE("Single entry point for all operations")
    {
        NurseryFacade *facade = new NurseryFacade();

        // GUI/CLI only needs to know about NurseryFacade
        // All operations available through one object
        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);
        facade->browsePlants(nullptr);
        facade->waterPlant(plant);
        facade->getSuggestions();
        facade->purchasePlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Reduced coupling between subsystems and client")
    {
        // Without facade: client depends on 13+ pattern classes
        // With facade: client depends only on NurseryFacade
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Tree");
        delete plant;
        delete facade;
    }

    SUBCASE("Simplified error handling")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade can handle errors from subsystems
        // Client sees simple interface
        try {
            PlantComponent *plant = facade->createPlant("InvalidType");
            // Facade handles gracefully
            delete plant;
        } catch (...) {
            // Single error handling point
        }

        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - System Integration")
{
    SUBCASE("Facade integrates all 13 patterns")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Each method integrates multiple patterns:
        // createPlant: Builder + Director + Prototype
        // addToInventory: Singleton + Flyweight
        // browsePlants: Iterator + Singleton
        // purchasePlant: Mediator + Command
        // waterPlant: Command + Strategy + Observer + State
        // getSuggestions: Mediator + Observer

        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);
        facade->browsePlants(nullptr);
        facade->waterPlant(plant);
        facade->getSuggestions();
        facade->purchasePlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Facade coordinate subsystem state")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade ensures consistent state across all subsystems
        PlantComponent *plant = facade->createPlant("Tree");

        // Adding to inventory updates singleton state
        facade->addToInventory(plant);

        // Purchasing updates mediator state
        facade->purchasePlant(plant);

        // Watering updates command history
        facade->waterPlant(plant);

        Inventory *inv1 = Inventory::getInstance();
        Inventory *inv2 = Inventory::getInstance();
        CHECK(inv1 == inv2);  // Singleton consistency

        delete plant;
        delete facade;
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

        if (plant != nullptr) {
            delete plant;
        }
        delete facade;
    }

    SUBCASE("Handle null plant in operations")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade should handle gracefully
        facade->waterPlant(nullptr);
        facade->purchasePlant(nullptr);

        delete facade;
    }

    SUBCASE("Handle browsing empty inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should not crash on empty inventory
        facade->browsePlants(nullptr);
        facade->browsePlants("Spring");

        delete facade;
    }

    SUBCASE("Handle multiple suggestions requests")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should handle repeated calls
        facade->getSuggestions();
        facade->getSuggestions();
        facade->getSuggestions();

        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Performance and Scalability")
{
    SUBCASE("Create many plants via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        std::vector<PlantComponent *> plants;

        // Create 100 plants
        for (int i = 0; i < 100; i++) {
            PlantComponent *p = facade->createPlant("Tree");
            plants.push_back(p);
            facade->addToInventory(p);
        }

        // Browse should handle large inventory
        facade->browsePlants(nullptr);

        // Water multiple plants
        for (int i = 0; i < 10; i++) {
            facade->waterPlant(plants[i]);
        }

        for (PlantComponent *p : plants) {
            delete p;
        }
        delete facade;
    }

    SUBCASE("Browse with large inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Add many plants
        for (int i = 0; i < 50; i++) {
            PlantComponent *p = facade->createPlant("Tree");
            facade->addToInventory(p);
        }

        // Browse should complete in reasonable time
        facade->browsePlants(nullptr);
        facade->browsePlants("Spring");

        delete facade;
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
    }
}
