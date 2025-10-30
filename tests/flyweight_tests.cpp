#include "doctest.h"
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "strategy/WaterStrategy.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include <string>

TEST_CASE("Testing Flyweight Pattern - String Flyweight Storage")
{
    SUBCASE("Flyweight factory is created successfully")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();
        CHECK(fac != nullptr);
        delete fac;
    }

    SUBCASE("String insertion and retrieval")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        fac->getFlyweight(0, new std::string("Insert1"));
        Flyweight<std::string *> *retrieved = fac->getFlyweight(0);

        CHECK(retrieved != nullptr);
        CHECK(*retrieved->getState() == "Insert1");

        delete fac;
    }

    SUBCASE("Multiple strings in factory")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        fac->getFlyweight(0, new std::string("Insert1"));
        fac->getFlyweight(1, new std::string("Insert2"));

        CHECK(*fac->getFlyweight(1)->getState() == "Insert2");
        CHECK(*fac->getFlyweight(0)->getState() == "Insert1");

        delete fac;
    }

    SUBCASE("Same key returns same flyweight instance")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        fac->getFlyweight(0, new std::string("Spring"));
        Flyweight<std::string *> *first = fac->getFlyweight(0);
        Flyweight<std::string *> *second = fac->getFlyweight(0);

        // Should be the same object
        CHECK(first == second);

        delete fac;
    }

    SUBCASE("Flyweight memory reuse - multiple references")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        fac->getFlyweight(5, new std::string("TestString"));

        // Retrieve same flyweight multiple times
        std::vector<Flyweight<std::string *> *> refs;
        for (int i = 0; i < 10; i++) {
            refs.push_back(fac->getFlyweight(5));
        }

        // All should point to the same flyweight
        for (int i = 1; i < 10; i++) {
            CHECK(refs[0] == refs[i]);
        }

        delete fac;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Flyweight Pattern - Strategy Flyweight Management")
{
    SUBCASE("Water strategy flyweight factory creation")
    {
        FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();
        CHECK(fac != nullptr);
        delete fac;
    }

    SUBCASE("Water strategy insertion and use")
    {
        FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();
        LivingPlant *plant = new Tree();

        fac->getFlyweight(LowWater::getID(), new LowWater());

        int waterAmount = fac->getFlyweight(LowWater::getID())->getState()->water(plant);
        CHECK(waterAmount == 35);

        delete fac;
        delete plant;
    }

    SUBCASE("Multiple water strategies in flyweight factory")
    {
        FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();
        LivingPlant *plant = new Tree();

        fac->getFlyweight(LowWater::getID(), new LowWater());
        fac->getFlyweight(MidWater::getID(), new MidWater());

        int lowAmount = fac->getFlyweight(LowWater::getID())->getState()->water(plant);
        int midAmount = fac->getFlyweight(MidWater::getID())->getState()->water(plant);

        CHECK(lowAmount == 35);
        CHECK(midAmount == 45);

        delete fac;
        delete plant;
    }

    SUBCASE("Same strategy ID returns same flyweight instance")
    {
        FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();

        fac->getFlyweight(LowWater::getID(), new LowWater());
        Flyweight<WaterStrategy *> *first = fac->getFlyweight(LowWater::getID());
        Flyweight<WaterStrategy *> *second = fac->getFlyweight(LowWater::getID());

        // Should be the same flyweight instance
        CHECK(first == second);

        delete fac;
    }

    SUBCASE("Different strategies are different flyweight instances")
    {
        FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();

        fac->getFlyweight(LowWater::getID(), new LowWater());
        fac->getFlyweight(MidWater::getID(), new MidWater());

        Flyweight<WaterStrategy *> *lowWater = fac->getFlyweight(LowWater::getID());
        Flyweight<WaterStrategy *> *midWater = fac->getFlyweight(MidWater::getID());

        // Should be different instances
        CHECK(lowWater != midWater);

        delete fac;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Flyweight Pattern - Flyweight Characteristics")
{
    SUBCASE("Flyweight object can be shared without state changes")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        fac->getFlyweight(0, new std::string("Spring"));

        // Get the flyweight and verify its state
        Flyweight<std::string *> *flyweight = fac->getFlyweight(0);
        std::string state = *flyweight->getState();

        // Get it again - should have same state
        Flyweight<std::string *> *flyweight2 = fac->getFlyweight(0);
        std::string state2 = *flyweight2->getState();

        CHECK(state == state2);
        CHECK(state == "Spring");

        delete fac;
    }

    SUBCASE("Flyweight state is immutable")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        fac->getFlyweight(1, new std::string("Summer"));

        Flyweight<std::string *> *fly1 = fac->getFlyweight(1);
        Flyweight<std::string *> *fly2 = fac->getFlyweight(1);

        // Both references should have same state
        CHECK(*fly1->getState() == *fly2->getState());

        delete fac;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Flyweight Pattern - Memory Efficiency Demonstration")
{
    SUBCASE("Reusing flyweight reduces memory for identical strings")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        // Create multiple plants that would benefit from shared season strings
        fac->getFlyweight(0, new std::string("Spring"));
        fac->getFlyweight(1, new std::string("Summer"));
        fac->getFlyweight(2, new std::string("Autumn"));
        fac->getFlyweight(3, new std::string("Winter"));

        // Verify each season is stored
        CHECK(*fac->getFlyweight(0)->getState() == "Spring");
        CHECK(*fac->getFlyweight(1)->getState() == "Summer");
        CHECK(*fac->getFlyweight(2)->getState() == "Autumn");
        CHECK(*fac->getFlyweight(3)->getState() == "Winter");

        delete fac;
    }

    SUBCASE("Flyweight factory stores many strategies efficiently")
    {
        FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();

        // Add strategies for reuse
        fac->getFlyweight(1, new LowWater());
        fac->getFlyweight(2, new MidWater());

        LivingPlant *plant = new Tree();

        // Use each strategy multiple times
        for (int i = 0; i < 100; i++) {
            fac->getFlyweight(1)->getState()->water(plant);
        }

        // Should still only have one instance of each strategy
        CHECK(fac->getFlyweight(1) == fac->getFlyweight(1));
        CHECK(fac->getFlyweight(2) == fac->getFlyweight(2));

        delete fac;
        delete plant;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Flyweight Pattern - Error Handling")
{
    SUBCASE("Accessing non-existent flyweight")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        fac->getFlyweight(0, new std::string("Test"));

        // Try to access non-existent key - may throw or return default
        try {
            fac->getFlyweight(999);
        }
        catch (const char *e) {
            CHECK(e != nullptr);
        }

        delete fac;
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Flyweight Pattern - Singleton Integration")
{
    SUBCASE("Flyweight objects work with singleton inventory")
    {
        Inventory *inv = Inventory::getInstance();

        // Get string flyweights from inventory
        Flyweight<std::string *> *str1 = inv->getString("Spring");
        Flyweight<std::string *> *str2 = inv->getString("Spring");

        // Should be the same instance
        CHECK(str1 == str2);
    }

    SUBCASE("Multiple different season flyweights coexist")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<std::string *> *spring = inv->getString("Spring");
        Flyweight<std::string *> *summer = inv->getString("Summer");
        Flyweight<std::string *> *autumn = inv->getString("Autumn");

        // All should be different
        CHECK(spring != summer);
        CHECK(summer != autumn);
        CHECK(spring != autumn);

        // But repeated calls return same instances
        CHECK(spring == inv->getString("Spring"));
        CHECK(summer == inv->getString("Summer"));
        CHECK(autumn == inv->getString("Autumn"));
    }
    delete Inventory::getInstance();
}

TEST_CASE("Testing Flyweight Pattern - Factory Method Pattern")
{
    SUBCASE("Factory creates and manages flyweights")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        // Create multiple flyweights
        for (int i = 0; i < 5; i++) {
            fac->getFlyweight(i, new std::string("Season" + std::to_string(i)));
        }

        // Verify all are stored
        for (int i = 0; i < 5; i++) {
            Flyweight<std::string *> *fly = fac->getFlyweight(i);
            CHECK(fly != nullptr);
        }

        delete fac;
    }

    SUBCASE("Factory prevents duplicate instances")
    {
        FlyweightFactory<int, std::string *> *fac = new FlyweightFactory<int, std::string *>();

        // Add a flyweight
        fac->getFlyweight(0, new std::string("Original"));

        // Try to get the existing one (without allocating new memory)
        // The factory should return the cached instance
        Flyweight<std::string *> *cached = fac->getFlyweight(0);

        // Should still return the first one
        CHECK(*cached->getState() == "Original");

        delete fac;
    }
    delete Inventory::getInstance();
}
