#include "doctest.h"
#include "singleton/Singleton.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "mediator/Staff.h"
#include "mediator/Customer.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "strategy/LowSun.h"
#include "strategy/MidSun.h"
#include "state/Seed.h"
#include "state/Vegetative.h"

TEST_CASE("Testing Singleton Pattern - Basic Instance")
{
    SUBCASE("getInstance returns non-null instance")
    {
        Inventory *inv = Inventory::getInstance();
        CHECK(inv != nullptr);
    }

    SUBCASE("getInstance returns same instance on multiple calls")
    {
        Inventory *inv1 = Inventory::getInstance();
        Inventory *inv2 = Inventory::getInstance();
        CHECK(inv1 == inv2);
    }

    SUBCASE("Instance is the same across different variables")
    {
        Inventory *invA = Inventory::getInstance();
        Inventory *invB = Inventory::getInstance();
        Inventory *invC = Inventory::getInstance();

        CHECK(invA == invB);
        CHECK(invB == invC);
        CHECK(invA == invC);
    }
    delete Inventory::getInstance();
}


TEST_CASE("Testing Singleton Pattern - Flyweight Strategy Integration")
{
    SUBCASE("Inventory manages water strategies")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Get water strategies from singleton
        Flyweight<WaterStrategy *> *lowWaterFly = inv->getWaterFly(LowWater::getID());
        CHECK(lowWaterFly != nullptr);

        // Use the strategy
        int waterAmount = lowWaterFly->getState()->water(plant);
        CHECK(waterAmount == 15);

        delete plant;
    }

    SUBCASE("Inventory manages multiple water strategies")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Get different strategies
        Flyweight<WaterStrategy *> *lowWater = inv->getWaterFly(LowWater::getID());
        Flyweight<WaterStrategy *> *midWater = inv->getWaterFly(MidWater::getID());

        CHECK(lowWater != nullptr);
        CHECK(midWater != nullptr);
        CHECK(lowWater != midWater);

        int low = lowWater->getState()->water(plant);
        int mid = midWater->getState()->water(plant);

        CHECK(low == 15);
        CHECK(mid == 20);

        delete plant;
    }

    SUBCASE("Singleton returns same strategy flyweight instance")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<WaterStrategy *> *strategy1 = inv->getWaterFly(LowWater::getID());
        Flyweight<WaterStrategy *> *strategy2 = inv->getWaterFly(LowWater::getID());

        // Should be the same flyweight instance due to flyweight pattern
        CHECK(strategy1 == strategy2);
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Singleton Pattern - State Management")
{
    SUBCASE("Inventory manages plant maturity states")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Get seed state
        Flyweight<MaturityState *> *seedState = inv->getStates(Seed::getID());
        CHECK(seedState != nullptr);

        // Use the state
        plant->setMaturity(Seed::getID());
        plant->setAge(5);
        plant->setHealth(50);
        plant->setWaterLevel(30);
        plant->setSunExposure(20);

        seedState->getState()->grow(plant);

        // State should have been applied
        CHECK(plant->getAge() > 0);

        delete plant;
    }

    SUBCASE("Singleton returns same state instance")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<MaturityState *> *state1 = inv->getStates(Seed::getID());
        Flyweight<MaturityState *> *state2 = inv->getStates(Seed::getID());

        // Should be the same flyweight instance
        CHECK(state1 == state2);
    }

    SUBCASE("Different states are different instances")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<MaturityState *> *seedState = inv->getStates(Seed::getID());
        Flyweight<MaturityState *> *vegState = inv->getStates(Vegetative::getID());

        CHECK(seedState != vegState);
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Singleton Pattern - String Flyweight Management")
{
    SUBCASE("Inventory manages string flyweights")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<std::string *> *str1 = inv->getString("Spring");
        CHECK(str1 != nullptr);
        CHECK(*str1->getState() == "Spring");
    }

    SUBCASE("Same string returns same flyweight instance")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<std::string *> *str1 = inv->getString("Summer");
        Flyweight<std::string *> *str2 = inv->getString("Summer");

        // Should be the same flyweight instance
        CHECK(str1 == str2);
        CHECK(*str1->getState() == *str2->getState());
    }

    SUBCASE("Different strings return different flyweights")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<std::string *> *autumn = inv->getString("Autumn");
        Flyweight<std::string *> *winter = inv->getString("Winter");

        CHECK(autumn != winter);
        CHECK(*autumn->getState() != *winter->getState());
        delete Inventory::getInstance();
    }

    SUBCASE("Multiple string instances can coexist")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<std::string *> *spring = inv->getString("Spring");
        Flyweight<std::string *> *summer = inv->getString("Summer");
        Flyweight<std::string *> *autumn = inv->getString("Autumn");
        Flyweight<std::string *> *winter = inv->getString("Winter");

        CHECK(spring != summer);
        CHECK(summer != autumn);
        CHECK(autumn != winter);
        CHECK(spring != winter);
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Singleton Pattern - Mediator Component Integration")
{
    SUBCASE("Inventory manages staff members")
    {
        Inventory *inv = Inventory::getInstance();
        std::vector<Staff *> *staffList = inv->getStaff();

        CHECK(staffList != nullptr);

        // Clear and add test staff
        staffList->clear();
        Staff *testStaff = new Staff();
        staffList->push_back(testStaff);

        CHECK(staffList->size() > 0);
        CHECK(staffList->back() == testStaff);

        delete testStaff;
        staffList->clear();
        delete Inventory::getInstance();
    }

    SUBCASE("Inventory manages customers")
    {
        Inventory *inv = Inventory::getInstance();
        std::vector<Customer *> *customerList = inv->getCustomers();

        CHECK(customerList != nullptr);

        // Clear and add test customer
        customerList->clear();
        Customer *testCustomer = new Customer();
        customerList->push_back(testCustomer);

        CHECK(customerList->size() > 0);
        CHECK(customerList->back() == testCustomer);

        delete testCustomer;
        customerList->clear();
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Singleton Pattern - Error Handling with Invalid IDs")
{
    SUBCASE("Invalid water strategy ID falls back to default")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Request non-existent strategy ID
        Flyweight<WaterStrategy *> *invalidStrategy = inv->getWaterFly(9999);

        // Should still return a valid strategy (default fallback)
        CHECK(invalidStrategy != nullptr);
        CHECK(invalidStrategy->getState() != nullptr);

        delete plant;
        delete Inventory::getInstance();
    }

    SUBCASE("Invalid state ID falls back to default")
    {
        Inventory *inv = Inventory::getInstance();

        // Request non-existent state ID
        Flyweight<MaturityState *> *invalidState = inv->getStates(9999);

        // Should still return a valid state (default fallback)
        CHECK(invalidState != nullptr);
        CHECK(invalidState->getState() != nullptr);
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Singleton Pattern - Global State Consistency")
{
    SUBCASE("Modifications via singleton are globally visible")
    {
        
        Inventory *inv1 = Inventory::getInstance();
        Inventory *inv2 = Inventory::getInstance();

        // Get staff list from inv1
        std::vector<Staff *> *staffList1 = inv1->getStaff();
        staffList1->clear();

        // Get same list from inv2
        std::vector<Staff *> *staffList2 = inv2->getStaff();

        // Should both be empty since same underlying instance
        CHECK(staffList1->size() == 0);
        CHECK(staffList2->size() == 0);
        CHECK(staffList1 == staffList2);
        delete Inventory::getInstance();
    }

    SUBCASE("Strategy flyweights are shared across references")
    {
        Inventory *inv1 = Inventory::getInstance();
        Inventory *inv2 = Inventory::getInstance();

        Flyweight<WaterStrategy *> *strategy1 = inv1->getWaterFly(LowWater::getID());
        Flyweight<WaterStrategy *> *strategy2 = inv2->getWaterFly(LowWater::getID());

        // Should be identical instances
        CHECK(strategy1 == strategy2);
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Singleton Pattern - Memory Efficiency Verification")
{
    SUBCASE("Repeated singleton calls don't allocate new instances")
    {
        Inventory *firstCall = Inventory::getInstance();
        Inventory *secondCall = Inventory::getInstance();
        Inventory *thirdCall = Inventory::getInstance();

        // All should be the same memory location
        CHECK(firstCall == secondCall);
        CHECK(secondCall == thirdCall);
        delete Inventory::getInstance();
    }

    SUBCASE("Flyweight strategy sharing reduces memory usage")
    {
        Inventory *inv = Inventory::getInstance();

        // Request same strategy multiple times
        Flyweight<WaterStrategy *> *strat1 = inv->getWaterFly(MidWater::getID());
        Flyweight<WaterStrategy *> *strat2 = inv->getWaterFly(MidWater::getID());
        Flyweight<WaterStrategy *> *strat3 = inv->getWaterFly(MidWater::getID());

        // All should point to the same strategy (flyweight reuse)
        CHECK(strat1 == strat2);
        CHECK(strat2 == strat3);
      

       

        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

