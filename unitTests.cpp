// please use testing like this.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "singleton/Singleton.h"
#include <doctest/doctest.h>

TEST_CASE("Overall Testing of flyweight strings")
{
    FlyweightFactory<int, string *> *fac = new FlyweightFactory<int, string *>();

    CHECK(fac != nullptr);

    fac->getFlyweight(0, new string("Insert1"));
    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");

    fac->getFlyweight(1, new string("Insert2"));
    CHECK(*fac->getFlyweight(1)->getState() == "Insert2");

    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");
    delete fac;
}
TEST_CASE("Overall Testing of flyweight water strategies")
{
    FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();

    fac->getFlyweight(LowWater::getID(), new LowWater());

    CHECK(fac->getFlyweight(LowWater::getID())->getState()->water(nullptr) == 10);

    fac->getFlyweight(MidWater::getID(), new MidWater());

    CHECK(fac->getFlyweight(MidWater::getID())->getState()->water(nullptr) == 20);
    delete fac;
}
TEST_CASE("Singleton basics")
{

    Inventory *inv = Inventory::getInstance();
    CHECK(inv == Inventory::getInstance());
    CHECK(inv->getWaterFly(LowWater::getID())->getState()->water(nullptr) == 10);
    CHECK(Inventory::getInstance()->getWaterFly(MidWater::getID())->getState()->water(nullptr) == 20);
    delete inv;
}