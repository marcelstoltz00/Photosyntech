#include "doctest.h"
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
#include "strategy/WaterStrategy.h"
#include "strategy/SunStrategy.h"

TEST_CASE("Testing WaterStrategy implementations")
{
    LivingPlant *plant = new Tree();

    SUBCASE("LowWater strategy")
    {
        WaterStrategy *lowWater = new LowWater();
        CHECK(lowWater->water(plant) == 35);
        delete lowWater;
    }

    SUBCASE("MidWater strategy")
    {
        WaterStrategy *midWater = new MidWater();
        CHECK(midWater->water(plant) == 45);
        delete midWater;
    }

    SUBCASE("HighWater strategy")
    {
        WaterStrategy *highWater = new HighWater();
        CHECK(highWater->water(plant) == 65);
        delete highWater;
    }

    SUBCASE("AlternatingWater strategy")
    {
        WaterStrategy *altWater = new AlternatingWater();
        int first = altWater->water(plant);
        int second = altWater->water(plant);
        CHECK(first != second);
        CHECK((first >= 2 && first <= 50));
        CHECK((second >= 2 && second <= 50));
        delete altWater;
    }

    delete plant;
    delete Inventory::getInstance();
}

TEST_CASE("Testing SunStrategy implementations")
{
    LivingPlant *plant = new Tree();

    SUBCASE("LowSun strategy")
    {
        SunStrategy *lowSun = new LowSun();
        CHECK(lowSun->addSun(plant) == 12);
        delete lowSun;
    }

    SUBCASE("MidSun strategy")
    {
        SunStrategy *midSun = new MidSun();
        CHECK(midSun->addSun(plant) == 40);
        delete midSun;
    }

    SUBCASE("HighSun strategy")
    {
        SunStrategy *highSun = new HighSun();
        CHECK(highSun->addSun(plant) == 72);
        delete highSun;
    }

    SUBCASE("AlternatingSun strategy")
    {
        SunStrategy *altSun = new AlternatingSun();
        int first = altSun->addSun(plant);
        int second = altSun->addSun(plant);
        CHECK(first != second);
        CHECK((first == 16 || first == 36));
        CHECK((second == 16 || second == 36));
        delete altSun;
    }

    delete plant;
    delete Inventory::getInstance();
}

TEST_CASE("Testing strategy switching in LivingPlant")
{
    LivingPlant *plant = new LivingPlant("Test Plant", 25.0, 5, 5);

    SUBCASE("Water strategy switching")
    {
        plant->setWaterLevel(0);
        plant->setWaterStrategy(1);
        plant->water();

        CHECK(plant->getWaterLevel() == 35);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(2);
        plant->water();
        CHECK(plant->getWaterLevel() == 45);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(3);
        plant->water();
        CHECK(plant->getWaterLevel() == 65);
    }

    SUBCASE("Sun strategy switching")
    {
        plant->setSunExposure(0);
        plant->setSunStrategy(1);
        plant->setOutside();
        CHECK(plant->getSunExposure() == 12);

        plant->setSunExposure(0);
        plant->setSunStrategy(2);
        plant->setOutside();
        CHECK(plant->getSunExposure() == 40);

        plant->setSunExposure(0);
        plant->setSunStrategy(3);
        plant->setOutside();
        CHECK(plant->getSunExposure() == 72);
    }

    delete plant;
    delete Inventory::getInstance();
}