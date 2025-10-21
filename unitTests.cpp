// please use testing like this.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "singleton/Singleton.h"
#include <doctest/doctest.h>
#include "prototype/Tree.h"
#include "state/Seed.h"

TEST_CASE("Overall Testing of flyweight strings + error handling")
{
    FlyweightFactory<int, string *> *fac = new FlyweightFactory<int, string *>();

    CHECK(fac != nullptr);

    fac->getFlyweight(0, new string("Insert1"));
    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");

    fac->getFlyweight(1, new string("Insert2"));
    CHECK(*fac->getFlyweight(1)->getState() == "Insert2");

    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");

    try
    {
        fac->getFlyweight(5);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }

    delete fac;
}
TEST_CASE("Overall Testing of flyweight water strategies")
{
    FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();
    LivingPlant *plant = new Tree();
    fac->getFlyweight(LowWater::getID(), new LowWater());

    CHECK(fac->getFlyweight(LowWater::getID())->getState()->water(plant) == 10);

    fac->getFlyweight(MidWater::getID(), new MidWater());

    CHECK(fac->getFlyweight(MidWater::getID())->getState()->water(plant) == 20);
    delete fac;
    delete plant;
}
TEST_CASE("Singleton basics with water strategy testing and with state testing")
{
    LivingPlant *plant = new Tree();

    Inventory *inv = Inventory::getInstance();
    CHECK(inv == Inventory::getInstance());
    CHECK(inv->getWaterFly(LowWater::getID())->getState()->water(plant) == 10);
    CHECK(Inventory::getInstance()->getWaterFly(MidWater::getID())->getState()->water(plant) == 20);

    for (int i = 0; i < 7; i++)
    {
        Inventory::getInstance()->getStates(Seed::getID())->getState()->grow(plant);
    };
    CHECK(plant->getAge() == 7);

    CHECK(Inventory::getInstance()->getWaterFly(5000)->getState()->water(plant) == 10);

    delete inv;
    delete plant;
}
