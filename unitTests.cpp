// please use testing like this.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "singleton/Singleton.h"
#include <doctest/doctest.h>

TEST_CASE("Checking construction")
{
    Inventory *inv = Inventory::getInstance();
    CHECK(inv == Inventory::getInstance());
    delete inv;
}

