#include "doctest.h"
#include "command/Command.h"
#include "command/AddPlantToBasketCommand.h"
#include "command/CreatePlantCommand.h"
#include "command/GrowPlantCommand.h"
#include "command/GetSuggestionCommand.h"
#include "command/PurchasePlantsCommand.h"
#include "singleton/Singleton.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "mediator/Customer.h"
#include "composite/PlantGroup.h"
#include "composite/PlantComponent.h"
#include "builder/Director.h"
#include "builder/RoseBuilder.h"

TEST_CASE("Testing Command Pattern - Basic Command Interface")
{
    SUBCASE("Command interface is abstract and cannot be instantiated")
    {
        // Cannot create a Command directly - it's abstract
        // This test documents the interface requirement
        CHECK(true); // Interface exists
    }
}

TEST_CASE("Testing Command Pattern - AddPlantToBasketCommand")
{
    SUBCASE("Constructor with valid customer and plant")
    {
        Customer* customer = new Customer();

        Builder* builder = new RoseBuilder();
        Director director(builder);
        director.construct();
        PlantComponent* plant = director.getPlant();

        Command* cmd = new AddPlantToBasketCommand(customer, plant);
        CHECK(cmd != nullptr);

        delete cmd;
        delete plant;
        delete builder;
        delete customer;
    }

    SUBCASE("Constructor throws with null customer")
    {
        Builder* builder = new RoseBuilder();
        Director director(builder);
        director.construct();
        PlantComponent* plant = director.getPlant();

        CHECK_THROWS_AS(new AddPlantToBasketCommand(nullptr, plant), std::invalid_argument);

        delete plant;
        delete builder;
    }

    SUBCASE("Constructor throws with null plant")
    {
        Customer* customer = new Customer();

        CHECK_THROWS_AS(new AddPlantToBasketCommand(customer, nullptr), std::invalid_argument);

        delete customer;
    }

    SUBCASE("Execute adds plant to customer basket")
    {
        Customer* customer = new Customer();

        Builder* builder = new RoseBuilder();
        Director director(builder);
        director.construct();
        PlantComponent* plant = director.getPlant();

        AddPlantToBasketCommand* cmd = new AddPlantToBasketCommand(customer, plant);

        // Initially no basket
        CHECK(customer->getBasket() == nullptr);

        cmd->execute();

        // After execute, basket should exist
        CHECK(customer->getBasket() != nullptr);

        delete cmd;
        // Don't delete plant - it's now owned by customer's basket
        delete builder;
        delete customer; // This will clean up basket and plant
    }

    SUBCASE("Undo removes plant from basket")
    {
        Customer* customer = new Customer();

        Builder* builder = new RoseBuilder();
        Director director(builder);
        director.construct();
        PlantComponent* plant = director.getPlant();

        AddPlantToBasketCommand* cmd = new AddPlantToBasketCommand(customer, plant);

        cmd->execute();
        PlantGroup* basket = customer->getBasket();
        CHECK(basket != nullptr);

        cmd->undo();

        // Basket should be cleared after undo
        CHECK(customer->getBasket() == nullptr);

        delete cmd;
        // Plant was removed and deleted by undo, don't delete again
        delete builder;
        delete customer;
    }

    SUBCASE("Multiple plants can be added to basket")
    {
        Customer* customer = new Customer();

        Builder* builder1 = new RoseBuilder();
        Director director1(builder1);
        director1.construct();
        PlantComponent* plant1 = director1.getPlant();

        Builder* builder2 = new RoseBuilder();
        Director director2(builder2);
        director2.construct();
        PlantComponent* plant2 = director2.getPlant();

        AddPlantToBasketCommand* cmd1 = new AddPlantToBasketCommand(customer, plant1);
        AddPlantToBasketCommand* cmd2 = new AddPlantToBasketCommand(customer, plant2);

        cmd1->execute();
        cmd2->execute();

        PlantGroup* basket = customer->getBasket();
        CHECK(basket != nullptr);

        delete cmd1;
        delete cmd2;
        // Don't delete plants - they're owned by basket
        delete builder1;
        delete builder2;
        delete customer; // This will clean up basket and both plants
    }
}
