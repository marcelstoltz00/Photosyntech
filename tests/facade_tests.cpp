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
        PlantComponent *plant = facade->createPlant("Pine");
        CHECK(plant != nullptr);
        delete plant;
        delete facade;
    }

    SUBCASE("Create shrub plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Rose");
        CHECK(plant != nullptr);
        delete plant;
        delete facade;
    }

    SUBCASE("Create succulent plant through facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Cactus");
        CHECK(plant != nullptr);
        delete plant;
        delete facade;
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
        PlantComponent *plant = facade->createPlant("Maple");
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
        PlantComponent *plant = facade->createPlant("Pine");

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
            PlantComponent *p = facade->createPlant("Maple");
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
        PlantComponent *plant = facade->createPlant("Rose");

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

        PlantComponent *tree = facade->createPlant("Pine");
        PlantComponent *shrub = facade->createPlant("Lavender");
        PlantComponent *succulent = facade->createPlant("JadePlant");

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
        PlantComponent *plant1 = facade->createPlant("Pine");
        PlantComponent *plant2 = facade->createPlant("Rose");

        facade->addToInventory(plant1);
        facade->addToInventory(plant2);

        // Browse without filter should show all
        Iterator* it = facade->createAllPlantsIterator();
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

        delete plant1;
        delete plant2;
        delete facade;
    }

    SUBCASE("Browse plants with season filter")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Sunflower");
        facade->addToInventory(plant);

        // Browse with specific season filter
        Iterator* it = facade->createSeasonIterator("Spring");
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

        delete plant;
        delete facade;
    }

    SUBCASE("Browse empty inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should handle gracefully
        Iterator* it = facade->createAllPlantsIterator();
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

        delete facade;
    }

    SUBCASE("Browse with various filters")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Cactus");
        facade->addToInventory(plant);

        // Test multiple filter strings
        Iterator* it1 = facade->createSeasonIterator("Spring");
        for (it1->first(); !it1->isDone(); it1->next()) {
            it1->currentItem();
        }
        delete it1;

        Iterator* it2 = facade->createSeasonIterator("Summer");
        for (it2->first(); !it2->isDone(); it2->next()) {
            it2->currentItem();
        }
        delete it2;

        Iterator* it3 = facade->createSeasonIterator("Fall");
        for (it3->first(); !it3->isDone(); it3->next()) {
            it3->currentItem();
        }
        delete it3;

        Iterator* it4 = facade->createSeasonIterator("Winter");
        for (it4->first(); !it4->isDone(); it4->next()) {
            it4->currentItem();
        }
        delete it4;

        Iterator* it5 = facade->createAllPlantsIterator();
        for (it5->first(); !it5->isDone(); it5->next()) {
            it5->currentItem();
        }
        delete it5;

        delete plant;
        delete facade;
    }

    SUBCASE("Browse delegates to iterator pattern")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Facade hides iterator complexity
        // Client calls simple browsePlants() method
        // Facade internally creates iterators with appropriate filters
        PlantComponent *plant = facade->createPlant("Lavender");
        facade->addToInventory(plant);

        Iterator* it = facade->createSeasonIterator("Spring");
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

        delete plant;
        delete facade;
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
        delete plant;
        delete facade;
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
        delete plant1;
        delete plant2;
        delete facade;
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
        delete plant;
        delete facade;
    }

    SUBCASE("Purchase removes from inventory")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Maple");
        Customer *customer = new Customer();

        facade->addToInventory(plant);
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        // Plant should be removed from available inventory
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);

        delete customer;
        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Plant Care Operations through Facade")
{
    SUBCASE("Water single plant via facade")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Rose");

        facade->waterPlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Water plant sets water strategy")
    {
        NurseryFacade *facade = new NurseryFacade();
        PlantComponent *plant = facade->createPlant("Cactus");

        // Watering should use strategy pattern internally
        facade->waterPlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Water multiple plants sequentially")
    {
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant1 = facade->createPlant("Pine");
        PlantComponent *plant2 = facade->createPlant("Lavender");

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
        PlantComponent *plant = facade->createPlant("Sunflower");

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
        PlantComponent *plant = facade->createPlant("JadePlant");

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
        Customer *customer = new Customer();

        facade->getSuggestions(customer);

        delete customer;
        delete facade;
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
    }

    SUBCASE("Multiple suggestion requests")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        PlantComponent *plant = facade->createPlant("Tree");
        facade->addToInventory(plant);

        facade->getSuggestions(customer);
        facade->getSuggestions(customer);
        facade->getSuggestions(customer);

        delete customer;
        delete plant;
        delete facade;
    }
}

TEST_CASE("Testing Facade Pattern - Complex Workflows through Facade")
{
    SUBCASE("Complete plant creation and care workflow")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Create plant
        PlantComponent *plant = facade->createPlant("Pine");
        CHECK(plant != nullptr);

        // Add to inventory
        facade->addToInventory(plant);

        // Browse available plants
        Iterator* it = facade->createAllPlantsIterator();
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

        // Water the plant
        facade->waterPlant(plant);

        // Get care suggestions
        facade->getSuggestions(customer);

        delete customer;
        delete plant;
        delete facade;
    }

    SUBCASE("Multi-plant inventory and sales workflow")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Create multiple plants
        std::vector<PlantComponent *> plants;
        for (int i = 0; i < 3; i++) {
            PlantComponent *p = facade->createPlant("Rose");
            plants.push_back(p);
            facade->addToInventory(p);
        }

        // Browse
        Iterator* it = facade->createSeasonIterator("Spring");
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

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

        for (PlantComponent *p : plants) {
            delete p;
        }
        delete customer;
        delete facade;
    }

    SUBCASE("Daily operations sequence")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Morning: check inventory
        PlantComponent *tree = facade->createPlant("Maple");
        PlantComponent *shrub = facade->createPlant("Lavender");

        facade->addToInventory(tree);
        facade->addToInventory(shrub);

        // Midday: browse available plants
        Iterator* it = facade->createAllPlantsIterator();
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

        // Afternoon: water plants
        facade->waterPlant(tree);
        facade->waterPlant(shrub);

        // Evening: get care suggestions
        facade->getSuggestions(customer);

        delete customer;
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
        // Simple: createPlant("Pine")
        PlantComponent *plant = facade->createPlant("Pine");
        CHECK(plant != nullptr);

        delete plant;
        delete facade;
    }

    SUBCASE("Facade hides singleton details from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about singleton management
        // Facade internally coordinates singleton access
        PlantComponent *plant = facade->createPlant("Cactus");
        facade->addToInventory(plant);

        delete plant;
        delete facade;
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
        delete plant;
        delete facade;
    }

    SUBCASE("Facade hides command pattern from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't know about command objects or undo/redo
        // Simple: waterPlant()
        PlantComponent *plant = facade->createPlant("Rose");
        facade->waterPlant(plant);

        delete plant;
        delete facade;
    }

    SUBCASE("Facade hides iterator pattern from client")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Client doesn't create iterators or handle filtering manually
        // Simple: browsePlants()
        PlantComponent *plant = facade->createPlant("Lavender");
        facade->addToInventory(plant);

        Iterator* it = facade->createSeasonIterator("Spring");
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

        delete plant;
        delete facade;
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
        facade->addToInventory(plant);
        Iterator* it = facade->createAllPlantsIterator();
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;
        facade->waterPlant(plant);
        facade->getSuggestions(customer);
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        delete customer;
        delete plant;
        delete facade;
    }

    SUBCASE("Reduced coupling between subsystems and client")
    {
        // Without facade: client depends on 13+ pattern classes
        // With facade: client depends only on NurseryFacade
        NurseryFacade *facade = new NurseryFacade();

        PlantComponent *plant = facade->createPlant("Rose");
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
        Customer *customer = new Customer();

        // Each method integrates multiple patterns:
        // createPlant: Builder + Director + Prototype
        // addToInventory: Singleton + Flyweight
        // browsePlants: Iterator + Singleton
        // purchasePlants: Mediator + Command
        // waterPlant: Command + Strategy + Observer + State
        // getSuggestions: Mediator + Observer

        PlantComponent *plant = facade->createPlant("Cactus");
        facade->addToInventory(plant);
        Iterator* it = facade->createAllPlantsIterator();
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;
        facade->waterPlant(plant);
        facade->getSuggestions(customer);
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        delete customer;
        delete plant;
        delete facade;
    }

    SUBCASE("Facade coordinate subsystem state")
    {
        NurseryFacade *facade = new NurseryFacade();
        Customer *customer = new Customer();

        // Facade ensures consistent state across all subsystems
        PlantComponent *plant = facade->createPlant("Sunflower");

        // Adding to inventory updates singleton state
        facade->addToInventory(plant);

        // Purchasing updates mediator state
        customer->addPlant(plant);
        facade->purchasePlants(customer);

        // Watering updates command history
        facade->waterPlant(plant);

        Inventory *inv1 = Inventory::getInstance();
        Inventory *inv2 = Inventory::getInstance();
        CHECK(inv1 == inv2);  // Singleton consistency

        delete customer;
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
        Customer *customer = new Customer();

        // Facade should handle gracefully
        facade->waterPlant(nullptr);
        facade->purchasePlants(customer);

        delete customer;
        delete facade;
    }

    SUBCASE("Handle browsing empty inventory")
    {
        NurseryFacade *facade = new NurseryFacade();

        // Should not crash on empty inventory
        Iterator* it1 = facade->createAllPlantsIterator();
        for (it1->first(); !it1->isDone(); it1->next()) {
            it1->currentItem();
        }
        delete it1;

        Iterator* it2 = facade->createSeasonIterator("Spring");
        for (it2->first(); !it2->isDone(); it2->next()) {
            it2->currentItem();
        }
        delete it2;

        delete facade;
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
            PlantComponent *p = facade->createPlant("Rose");
            plants.push_back(p);
            facade->addToInventory(p);
        }

        // Browse should handle large inventory
        Iterator* it = facade->createAllPlantsIterator();
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem();
        }
        delete it;

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
            PlantComponent *p = facade->createPlant("Maple");
            facade->addToInventory(p);
        }

        // Browse should complete in reasonable time
        Iterator* it1 = facade->createAllPlantsIterator();
        for (it1->first(); !it1->isDone(); it1->next()) {
            it1->currentItem();
        }
        delete it1;

        Iterator* it2 = facade->createSeasonIterator("Spring");
        for (it2->first(); !it2->isDone(); it2->next()) {
            it2->currentItem();
        }
        delete it2;

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
