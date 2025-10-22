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

#include "prototype/LivingPlant.h"
#include "decorator/customerDecorator/PlantDecorationHeader.h"
#include "decorator/plantDecorator/PlantAttributesHeader.h"
/*
TEST_CASE("Overall Testing of flyweight strings + error handling")
{
    FlyweightFactory<int, string *> *fac = new FlyweightFactory<int, string *>();
<<<<<<< HEAD
    CHECK(fac != nullptr);
    fac->getFlyweight(0, new string("Insert1"));
    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");
    fac->getFlyweight(1, new string("Insert2"));
    CHECK(*fac->getFlyweight(1)->getState() == "Insert2");
    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");
=======

    SUBCASE("factory is created")
    {
        CHECK(fac != nullptr);
    }

    SUBCASE("Correct String is inserted and accessable")
    {
        fac->getFlyweight(0, new string("Insert1"));
        CHECK(*fac->getFlyweight(0)->getState() == "Insert1");
    }

    SUBCASE("Correct String is inserted and when multiple strings exist")
    {
        fac->getFlyweight(0, new string("Insert1"));
        fac->getFlyweight(1, new string("Insert2"));
        CHECK(*fac->getFlyweight(1)->getState() == "Insert2");
        CHECK(*fac->getFlyweight(0)->getState() == "Insert1");
    }
>>>>>>> singleton-Flyweight
    try
    {
        fac->getFlyweight(5);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';

        delete fac;
    }
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
*/
TEST_CASE("Singleton basics with water strategy testing and with state testing")
{
<<<<<<< HEAD
    Inventory *inv = Inventory::getInstance();
=======
>>>>>>> singleton-Flyweight

    LivingPlant *plant = new Tree();

    CHECK(inv == Inventory::getInstance());
    CHECK(inv->getWaterFly(LowWater::getID())->getState()->water(plant) == 10);
    CHECK(Inventory::getInstance()->getWaterFly(MidWater::getID())->getState()->water(plant) == 20);
    for (int i = 0; i < 7; i++)
    {
        Inventory::getInstance()->getStates(Seed::getID())->getState()->grow(plant);
    };

    CHECK(plant->getAge() == 7);
<<<<<<< HEAD
    CHECK(Inventory::getInstance()->getWaterFly(5000)->getState()->water(plant) == 10);
    CHECK(*Inventory::getInstance()->getString("Insert1")->getState() == "Insert1");
=======

    SUBCASE("Correct exception handling")
    {
        CHECK(Inventory::getInstance()->getWaterFly(5000)->getState()->water(plant) == 10);

        CHECK(*Inventory::getInstance()->getString("Insert1")->getState() == "Insert1");
    }
>>>>>>> singleton-Flyweight

    delete plant;
    delete inv;
}

TEST_CASE("Testing decorator")
{
 
}

// testing decorator
/*
#include <iostream>


int main()
{
    PlantComponent *myPlant = new LargePot();

    myPlant->addAttribute(new ShopThemedCharm());

    LivingPlant *herb = new LivingPlant("Herb", 30.00, 3, 3);

    herb->setWaterStrategy(2);
    herb->setSunStrategy(2);

    myPlant->addAttribute(herb);

    myPlant->water();
    myPlant->setOutside();

    myPlant->affectWater();
    myPlant->affectSunlight();

    std::cout << "Current Plant Info:\n"
              << myPlant->getInfo() << std::endl;
    std::cout << "Current Price: R" << myPlant->getPrice() << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Drought incoming, pasop oaks" << std::endl;

    for (int i = 0; i < 5; i++)
    {
        myPlant->affectWater();
    }

    std::cout << "Plant Info After Drought:\n"
              << myPlant->getInfo() << std::endl;
    std::cout << "Price: R" << myPlant->getPrice() << std::endl;
    std::cout << "----------------------------------" << std::endl;

    std::cout << "Infinite darkness. bruh." << std::endl;
    for (int i = 0; i < 5; i++)
    {
        myPlant->affectSunlight();
    }

    std::cout << "Plant Info After Darkness:\n"
              << myPlant->getInfo() << std::endl;
    std::cout << "Price: R" << myPlant->getPrice() << std::endl;
    std::cout << "----------------------------------" << std::endl;

    delete myPlant;
    delete Inventory::getInstance();

    return 0;
*/