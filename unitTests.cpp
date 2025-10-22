#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "strategy/HighWater.h"
#include "strategy/AlternatingWater.h"
#include "strategy/LowSun.h"
#include "strategy/MidSun.h"
#include "strategy/HighSun.h"
#include "strategy/AlternatingSun.h"
#include "singleton/Singleton.h"
#include "state/Seed.h"
#include "state/Vegetative.h"
#include "state/Mature.h"
#include "state/Dead.h"


TEST_CASE("Testing WaterStrategy implementations") {
    LivingPlant* plant = new Tree();
    
    SUBCASE("LowWater strategy") {
        WaterStrategy* lowWater = new LowWater();
        CHECK(lowWater->water(plant) == 10);
        delete lowWater;
    }
    
    SUBCASE("MidWater strategy") {
        WaterStrategy* midWater = new MidWater();
        CHECK(midWater->water(plant) == 20);
        delete midWater;
    }
    
    SUBCASE("HighWater strategy") {
        WaterStrategy* highWater = new HighWater();
        CHECK(highWater->water(plant) == 30);
        delete highWater;
    }
    
    SUBCASE("AlternatingWater strategy") {
        WaterStrategy* altWater = new AlternatingWater();
        int first = altWater->water(plant);
        int second = altWater->water(plant);
        CHECK(first != second);
        CHECK((first >= 2 && first <= 5));
        CHECK((second >= 2 && second <= 5));
        delete altWater;
    }
    
    delete plant;
}

TEST_CASE("Testing SunStrategy implementations") {
    LivingPlant* plant = new Tree();
    
    SUBCASE("LowSun strategy") {
        SunStrategy* lowSun = new LowSun();
    CHECK(lowSun->addSun(plant) == 6);
        delete lowSun;
    }
    
    SUBCASE("MidSun strategy") {
        SunStrategy* midSun = new MidSun();
    CHECK(midSun->addSun(plant) == 25);
        delete midSun;
    }
    
    SUBCASE("HighSun strategy") {
        SunStrategy* highSun = new HighSun();
    CHECK(highSun->addSun(plant) == 72);
        delete highSun;
    }
    
    SUBCASE("AlternatingSun strategy") {
        SunStrategy* altSun = new AlternatingSun();
    int first = altSun->addSun(plant);
    int second = altSun->addSun(plant);
        CHECK(first != second);
        CHECK((first == 16 || first == 36));
        CHECK((second == 16 || second == 36));
        delete altSun;
    }
    
    delete plant;
}

TEST_CASE("Testing strategy switching in LivingPlant") {
    LivingPlant* plant = new LivingPlant("Test Plant", 25.0, 5, 5);
    
    SUBCASE("Water strategy switching") {
        plant->setWaterLevel(0);
        plant->setWaterStrategy(1);
        plant->water();

        CHECK(plant->getWaterLevel() == 20);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(2); 
        plant->water();
        CHECK(plant->getWaterLevel() == 40);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(3); 
        plant->water();
        CHECK(plant->getWaterLevel() == 60);
    }
    
    SUBCASE("Sun strategy switching") {
        plant->setSunExposure(0);
        plant->setSunStrategy(1); 
        plant->setOutside();
        CHECK(plant->getSunExposure() == 12);

        plant->setSunExposure(0);
        plant->setSunStrategy(2); 
        plant->setOutside();
        CHECK(plant->getSunExposure() == 50);

        plant->setSunExposure(0);
        plant->setSunStrategy(3); 
        plant->setOutside();
        CHECK(plant->getSunExposure() == 144);
    }
    
    delete plant;
}

TEST_CASE("Testing MaturityState transitions and behavior") {
    Inventory* inv = Inventory::getInstance(); 
    LivingPlant* plant = new Tree();

    SUBCASE("Seed -> Vegetative transition") {
    plant->setAge(6);
    plant->setHealth(50);

    plant->setWaterLevel(56);
    plant->setSunExposure(30);
        plant->setMaturity(Seed::getID());

        inv->getStates(Seed::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 25);
        CHECK(plant->getSunExposure() == 50);
        CHECK(plant->getHealth() >= 50);
    }

    SUBCASE("Vegetative -> Mature transition") {
    plant->setAge(29);
    plant->setHealth(60);
    // Vegetative::grow subtracts 10 units of water before checking transition,
    // so start with 50 so it remains >=40 after subtraction and triggers transition
    plant->setWaterLevel(50);
    plant->setSunExposure(50);
        plant->setMaturity(Vegetative::getID());

        inv->getStates(Vegetative::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 40);
        CHECK(plant->getSunExposure() == 60);
        CHECK(plant->getHealth() >= 60);
    }

    SUBCASE("Mature -> Dead transition by age") {
        plant->setAge(119);
        plant->setHealth(10);
        plant->setWaterLevel(40);
        plant->setSunExposure(40);
        plant->setMaturity(Mature::getID());

        inv->getStates(Mature::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 0);
        CHECK(plant->getSunExposure() == 0);
        CHECK(plant->getHealth() == 0);
    }

    SUBCASE("Dead state grow increments age only and keeps zeros") {
        plant->setAge(120);
        plant->setHealth(0);
        plant->setWaterLevel(0);
        plant->setSunExposure(0);
        plant->setMaturity(Dead::getID());

        inv->getStates(Dead::getID())->getState()->grow(plant);

        CHECK(plant->getAge() == 121);
        CHECK(plant->getWaterLevel() == 0);
        CHECK(plant->getHealth() == 0);
    }

    delete plant;
}
