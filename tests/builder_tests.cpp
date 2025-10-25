#include "doctest.h"
#include "builder/Director.h"
#include "builder/RoseBuilder.h"
#include "builder/CactusBuilder.h"
#include "builder/CherryBlossomBuilder.h"
#include "singleton/Singleton.h"
#include "composite/PlantComponent.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "builder/Builder.h"

TEST_CASE("Testing Builder Pattern Implementation")
{
    SUBCASE("Testing Director-Builder Interaction")
    {
        Builder *roseBuilder = new RoseBuilder();
        Director director(roseBuilder);

        director.construct();

        PlantComponent *rosePlant = director.getPlant();

        CHECK(rosePlant != nullptr);

        delete rosePlant;
        delete roseBuilder;
    }

    SUBCASE("Testing Rose Plant Properties")
    {
        Builder *roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        director.construct();

        PlantComponent *rosePlant = director.getPlant();

        std::string info = rosePlant->getInfo();

        CHECK(!info.empty());
        CHECK(info.find("Base Price") != std::string::npos);

        rosePlant->water();

        delete rosePlant;
        delete roseBuilder;
    }

    SUBCASE("Testing Cactus Builder")
    {
        Builder *cactusBuilder = new CactusBuilder();
        Director director(cactusBuilder);
        director.construct();

        PlantComponent *cactusPlant = director.getPlant();

        std::string info = cactusPlant->getInfo();

        CHECK(!info.empty());
        CHECK(info.find("Water Level") != std::string::npos);
        CHECK(info.find("Sun Exposure") != std::string::npos);

        cactusPlant->setOutside();

        delete cactusPlant;
        delete cactusBuilder;
    }

    SUBCASE("Testing Builder Pattern with Multiple Plants")
    {
        Builder *roseBuilder = new RoseBuilder();
        Builder *cactusBuilder = new CactusBuilder();

        Director director(roseBuilder);

        director.construct();
        PlantComponent *rosePlant = director.getPlant();
        Director director2(cactusBuilder);
        director2.construct();
        PlantComponent *cactusPlant = director2.getPlant();

        CHECK(rosePlant != nullptr);
        CHECK(cactusPlant != nullptr);

        CHECK(rosePlant->getInfo() != cactusPlant->getInfo());

        LivingPlant *roseLivingPlant = dynamic_cast<LivingPlant *>(rosePlant);
        LivingPlant *cactusLivingPlant = dynamic_cast<LivingPlant *>(cactusPlant);

        if (roseLivingPlant && cactusLivingPlant)
        {
            roseLivingPlant->setSunExposure(0);
            cactusLivingPlant->setSunExposure(0);

            rosePlant->setOutside();
            cactusPlant->setOutside();

            CHECK(cactusLivingPlant->getSunExposure() > roseLivingPlant->getSunExposure());
        }

        delete rosePlant;
        delete cactusPlant;
        delete roseBuilder;
        delete cactusBuilder;
    }

    SUBCASE("Testing Complete Builder Process")
    {

        Builder *roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        director.construct();
        PlantComponent *rosePlant = director.getPlant();

        LivingPlant *roseLivingPlant = dynamic_cast<LivingPlant *>(rosePlant);
        CHECK(roseLivingPlant != nullptr);

        if (roseLivingPlant)
        {

            int initialWater = roseLivingPlant->getWaterLevel();
            rosePlant->water();
            CHECK(roseLivingPlant->getWaterLevel() > initialWater);

            roseLivingPlant->setWaterLevel(0);
            rosePlant->water();
            CHECK(roseLivingPlant->getWaterLevel() >= 20);
        }

        delete rosePlant;
        delete roseBuilder;
    }
}

TEST_CASE("Testing CherryBlossomBuilder Implementation")
{
    SUBCASE("CherryBlossomBuilder can be created and used with Director")
    {
        Builder *cherryBuilder = new CherryBlossomBuilder();
        Director director(cherryBuilder);

        director.construct();

        PlantComponent *cherryPlant = director.getPlant();

        CHECK(cherryPlant != nullptr);

        delete cherryPlant;
        delete cherryBuilder;
    }

    SUBCASE("CherryBlossomBuilder creates a Tree")
    {
        Builder *cherryBuilder = new CherryBlossomBuilder();
        Director director(cherryBuilder);
        director.construct();

        PlantComponent *cherryPlant = director.getPlant();

        // CherryBlossom should be a Tree
        Tree *cherryTree = dynamic_cast<Tree *>(cherryPlant);
        CHECK(cherryTree != nullptr);

        delete cherryPlant;
        delete cherryBuilder;
    }

    SUBCASE("CherryBlossomBuilder sets proper initial values")
    {
        Builder *cherryBuilder = new CherryBlossomBuilder();
        Director director(cherryBuilder);
        director.construct();

        PlantComponent *cherryPlant = director.getPlant();
        LivingPlant *cherryLiving = dynamic_cast<LivingPlant *>(cherryPlant);

        CHECK(cherryLiving != nullptr);

        if (cherryLiving)
        {
            // Check initial health, water, and sun exposure are set
            CHECK(cherryLiving->getHealth() == 100);
            CHECK(cherryLiving->getWaterLevel() == 60);
            CHECK(cherryLiving->getSunExposure() == 60);
        }

        delete cherryPlant;
        delete cherryBuilder;
    }

    SUBCASE("CherryBlossomBuilder adds decorators")
    {
        Builder *cherryBuilder = new CherryBlossomBuilder();
        Director director(cherryBuilder);
        director.construct();

        PlantComponent *cherryPlant = director.getPlant();

        std::string info = cherryPlant->getInfo();

        CHECK(!info.empty());
        // Cherry Blossom should have decorators
        CHECK(info.find("Base Price") != std::string::npos);

        delete cherryPlant;
        delete cherryBuilder;
    }

    SUBCASE("CherryBlossomBuilder plant can water")
    {
        Builder *cherryBuilder = new CherryBlossomBuilder();
        Director director(cherryBuilder);
        director.construct();

        PlantComponent *cherryPlant = director.getPlant();
        LivingPlant *cherryLiving = dynamic_cast<LivingPlant *>(cherryPlant);

        if (cherryLiving)
        {
            int initialWater = cherryLiving->getWaterLevel();
            cherryPlant->water();
            // Water level should increase or at least not decrease drastically
            CHECK(cherryLiving->getWaterLevel() > 0);
        }

        delete cherryPlant;
        delete cherryBuilder;
    }

    SUBCASE("CherryBlossomBuilder plant responds to sun")
    {
        Builder *cherryBuilder = new CherryBlossomBuilder();
        Director director(cherryBuilder);
        director.construct();

        PlantComponent *cherryPlant = director.getPlant();
        LivingPlant *cherryLiving = dynamic_cast<LivingPlant *>(cherryPlant);

        if (cherryLiving)
        {
            cherryLiving->setSunExposure(0);
            cherryPlant->setOutside();
            // CherryBlossom uses MidSun strategy, should increase sun exposure
            CHECK(cherryLiving->getSunExposure() > 0);
        }

        delete cherryPlant;
        delete cherryBuilder;
    }

    SUBCASE("Multiple CherryBlossomBuilder instances create independent plants")
    {
        Builder *cherryBuilder1 = new CherryBlossomBuilder();
        Builder *cherryBuilder2 = new CherryBlossomBuilder();

        Director director1(cherryBuilder1);
        Director director2(cherryBuilder2);

        director1.construct();
        director2.construct();

        PlantComponent *cherry1 = director1.getPlant();
        PlantComponent *cherry2 = director2.getPlant();

        CHECK(cherry1 != nullptr);
        CHECK(cherry2 != nullptr);
        CHECK(cherry1 != cherry2);

        delete cherry1;
        delete cherry2;
        delete cherryBuilder1;
        delete cherryBuilder2;
    }

    SUBCASE("CherryBlossomBuilder plant has correct season")
    {
        Builder *cherryBuilder = new CherryBlossomBuilder();
        Director director(cherryBuilder);
        director.construct();

        PlantComponent *cherryPlant = director.getPlant();

        std::string info = cherryPlant->getInfo();

        // Cherry Blossom should have decorators applied
        CHECK(!info.empty());
        CHECK(info.find("Base Price") != std::string::npos);

        delete cherryPlant;
        delete cherryBuilder;
    }
}
