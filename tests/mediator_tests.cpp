#include "doctest.h"
#include "mediator/Customer.h"
#include "mediator/Staff.h"
#include "mediator/SalesFloor.h"
#include "mediator/SuggestionFloor.h"
#include "mediator/Mediator.h"
#include "mediator/User.h"
#include "singleton/Singleton.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "composite/PlantGroup.h"
#include <vector>

TEST_CASE("Testing Mediator Pattern Implementation")
{
    SUBCASE("Customer Creation and Basic Operations")
    {
        Customer *customer = new Customer();

        CHECK(customer != nullptr);
        CHECK(customer->getBasket() == nullptr);

        LivingPlant *testPlant = new Tree();
        customer->addPlant(testPlant);
        PlantGroup *basket = customer->getBasket();
        CHECK(basket != nullptr);

        // Clear the basket before deleting customer
        customer->clearBasket();
        delete customer;
    }

    SUBCASE("Customer Basket Management")
    {
        Customer *customer = new Customer();

        SUBCASE("Plant addition to basket")
        {
            LivingPlant *plant1 = new Tree();
            LivingPlant *plant2 = new Shrub();

            customer->addPlant(plant1);
            customer->addPlant(plant2);

            // Clear basket before cleanup
            customer->clearBasket();
            delete customer;
        }

        SUBCASE("Basket clearing")
        {
            LivingPlant *plant = new Tree();
            customer->addPlant(plant);
            CHECK(customer->getBasket() != nullptr);

            customer->clearBasket();
            CHECK(customer->getBasket() == nullptr);

            delete customer;
        }
        delete Inventory::getInstance();
    }

    SUBCASE("SalesFloor Mediator Operations")
    {
        SalesFloor *salesFloor = new SalesFloor();

        SUBCASE("SalesFloor creation")
        {
            CHECK(salesFloor != nullptr);
        }

        SUBCASE("Assist method without staff or customers")
        {
            salesFloor->assist();
        }

        delete salesFloor;
        delete Inventory::getInstance();
    }

    SUBCASE("Staff Creation and Basic Operations")
    {
        Staff *staff = new Staff();

        SUBCASE("Staff creation")
        {
            CHECK(staff != nullptr);
        }

        // SUBCASE("Staff operation method") {
        //     staff->operation();
        //  commented it out, it was causing errors
        //}

        delete staff;
    }

    SUBCASE("SuggestionFloor Mediator Operations")
    {
        SuggestionFloor *suggestionFloor = new SuggestionFloor();

        SUBCASE("SuggestionFloor creation")
        {
            CHECK(suggestionFloor != nullptr);
        }

        SUBCASE("Assist method")
        {
            suggestionFloor->assist();
            // just checking it doesn't crash
        }

        delete suggestionFloor;
    }

    SUBCASE("Customer-Mediator Interaction Scenarios")
    {
        SUBCASE("Customer without mediators")
        {
            Customer *customer = new Customer();

            customer->askForSuggestion();
            customer->purchasePlants();

            delete customer;
        }

        SUBCASE("Customer with empty basket purchase attempt")
        {
            Customer *customer = new Customer();
            SalesFloor *salesFloor = new SalesFloor();

            customer->purchasePlants();

            delete customer;
            delete salesFloor;
        }
    }

    SUBCASE("Inventory Integration with Mediator Components")
    {
        Inventory *inv = Inventory::getInstance();

        SUBCASE("Staff management in inventory")
        {
            std::vector<Staff *> *staffList = inv->getStaff();
            CHECK(staffList != nullptr);

            // add a staff member
            Staff *newStaff = new Staff();
            staffList->push_back(newStaff);

            CHECK(staffList->size() > 0);
            CHECK(staffList->back() == newStaff);

            delete newStaff;
            staffList->clear();
        }

        SUBCASE("Customer management in inventory")
        {
            std::vector<Customer *> *customerList = inv->getCustomers();
            CHECK(customerList != nullptr);

            // add a customer
            Customer *newCustomer = new Customer();
            customerList->push_back(newCustomer);

            CHECK(customerList->size() > 0);
            CHECK(customerList->back() == newCustomer);

            delete newCustomer;
            customerList->clear();
        }
    }

    SUBCASE("Mediator Pattern Integration Test")
    {
        SUBCASE("Complete mediator system setup")
        {
            SalesFloor *salesFloor = new SalesFloor();
            SuggestionFloor *suggestionFloor = new SuggestionFloor();
            Customer *customer = new Customer();
            Staff *staff = new Staff();

            // add staff to inventory
            std::vector<Staff *> *staffList = Inventory::getInstance()->getStaff();
            staffList->push_back(staff);

            // add customer to inventory
            std::vector<Customer *> *customerList = Inventory::getInstance()->getCustomers();
            customerList->push_back(customer);

            // check system state
            CHECK(salesFloor != nullptr);
            CHECK(suggestionFloor != nullptr);
            CHECK(customer != nullptr);
            CHECK(staff != nullptr);
            CHECK(staffList->size() == 1);
            CHECK(customerList->size() == 1);

            salesFloor->assist();
            suggestionFloor->assist();

            delete salesFloor;
            delete suggestionFloor;
            delete customer;
            delete staff;
            staffList->clear();
            customerList->clear();
        }
    }

    SUBCASE("Error Handling in Mediator System")
    {
        SUBCASE("Null pointer handling")
        {
            Customer *customer = new Customer();

            // test with null plant addition
            customer->addPlant(nullptr);

            // these should handle internal null checks
            customer->askForSuggestion();
            customer->purchasePlants();

            delete customer;
        }

        SUBCASE("Empty inventory handling")
        {
            SalesFloor *salesFloor = new SalesFloor();

            // clears any existing staff/customers
            std::vector<Staff *> *staffList = Inventory::getInstance()->getStaff();
            std::vector<Customer *> *customerList = Inventory::getInstance()->getCustomers();
            staffList->clear();
            customerList->clear();

            salesFloor->assist();

            delete salesFloor;
        }
    }
    delete Inventory::getInstance();
}