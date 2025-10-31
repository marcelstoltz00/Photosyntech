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
#include <string>
#include <cstring>

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
        customer->clearBasket();
        delete customer;
    }

    SUBCASE("Customer Basket Management")
    {
        Customer *customer = new Customer();
        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();
        customer->addPlant(plant1);
        customer->addPlant(plant2);
        customer->clearBasket();
        delete customer;
        delete Inventory::getInstance();
    }

    SUBCASE("SalesFloor Mediator Operations")
    {
        SalesFloor *salesFloor = new SalesFloor();
        CHECK(salesFloor != nullptr);
        salesFloor->assist();
        delete salesFloor;
        delete Inventory::getInstance();
    }

    SUBCASE("Staff Creation and Basic Operations")
    {
        Staff *staff = new Staff();
        CHECK(staff != nullptr);
        delete staff;
    }

    SUBCASE("SuggestionFloor Mediator Operations")
    {
        SuggestionFloor *suggestionFloor = new SuggestionFloor();
        CHECK(suggestionFloor != nullptr);
        suggestionFloor->assist();
        delete suggestionFloor;
    }

    SUBCASE("Staff Suggestion Functionality")
    {
        Staff *staff = new Staff();

        std::string suggestion = staff->assistSuggestion();
        std::cout << "STAFF SUGGESTION: " << suggestion << std::endl;

        CHECK_FALSE(suggestion.empty());
        CHECK(suggestion.length() > 0);

        bool hasPlantReference = (suggestion.find("plant") != std::string::npos) ||
                                 (suggestion.find("Tree") != std::string::npos) ||
                                 (suggestion.find("Rose") != std::string::npos) ||
                                 (suggestion.find("Cactus") != std::string::npos) ||
                                 (suggestion.find("recommend") != std::string::npos);
        CHECK(hasPlantReference == true);

        delete staff;
    }

    SUBCASE("Customer-Mediator Interaction Scenarios")
    {
        Customer *customer = new Customer();
        customer->askForSuggestion();
        customer->purchasePlants();
        delete customer;
    }

    SUBCASE("Inventory Integration with Mediator Components")
    {
        Inventory *inv = Inventory::getInstance();
        std::vector<Staff *> *staffList = inv->getStaff();
        CHECK(staffList != nullptr);
        Staff *newStaff = new Staff();
        staffList->push_back(newStaff);
        CHECK(staffList->size() > 0);
        CHECK(staffList->back() == newStaff);
        delete newStaff;
        staffList->clear();
    }

    SUBCASE("Mediator Pattern Integration Test")
    {
        SalesFloor *salesFloor = new SalesFloor();
        SuggestionFloor *suggestionFloor = new SuggestionFloor();
        Customer *customer = new Customer();
        Staff *staff = new Staff();
        std::vector<Staff *> *staffList = Inventory::getInstance()->getStaff();
        staffList->push_back(staff);
        std::vector<Customer *> *customerList = Inventory::getInstance()->getCustomers();
        customerList->push_back(customer);
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
    std::cout << std::endl;
    SUBCASE("Realistic Customer-Staff Interaction")
    {
        Customer *customer = new Customer();
        Staff *staff = new Staff();

        LivingPlant *rose = new Tree();
        //rose->setName("Rose");
        Inventory::getInstance()->getInventory()->addComponent(rose);

        std::string staffSuggestion = staff->assistSuggestion();
        std::cout << "REAL-TIME SUGGESTION: " << staff->assistSuggestion() << std::endl;

        CHECK_FALSE(staffSuggestion.empty());
        CHECK(staffSuggestion.find("recommend") != std::string::npos);

        delete customer;
        delete staff;
    }

    SUBCASE("Multiple Staff Suggestions")
    {
        Staff *staff1 = new Staff();
        Staff *staff2 = new Staff();

        std::string suggestion1 = staff1->assistSuggestion();
        std::string suggestion2 = staff2->assistSuggestion();

        std::cout << "STAFF 1 SUGGESTION: " << suggestion1 << std::endl;
        std::cout << "STAFF 2 SUGGESTION: " << suggestion2 << std::endl;

        CHECK_FALSE(suggestion1.empty());
        CHECK_FALSE(suggestion2.empty());
        CHECK(suggestion1.length() > 10);
        CHECK(suggestion2.length() > 10);

        delete staff1;
        delete staff2;
    }

    SUBCASE("Suggestion Content Validation")
    {
        Staff *staff = new Staff();
        std::string suggestion = staff->assistSuggestion();

        CHECK(suggestion.find('.') != std::string::npos);
        CHECK(suggestion.length() >= 20);

        delete staff;
    }
    delete Inventory::getInstance();
}
