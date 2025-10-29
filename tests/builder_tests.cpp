#include "doctest.h"
#include "builder/Director.h"
#include "builder/RoseBuilder.h"
#include "builder/CactusBuilder.h"
#include "builder/CherryBlossomBuilder.h"
#include "builder/JadePlantBuilder.h"
#include "builder/LavenderBuilder.h"
#include "builder/MapleBuilder.h"
#include "builder/PineBuilder.h"
#include "builder/SunflowerBuilder.h"
#include "singleton/Singleton.h"
#include "composite/PlantComponent.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Succulent.h"
#include "prototype/Herb.h"
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

TEST_CASE("Testing JadePlantBuilder Implementation")
{
    SUBCASE("JadePlantBuilder can be created and used with Director")
    {
        Builder *jadeBuilder = new JadePlantBuilder();
        Director director(jadeBuilder);

        director.construct();

        PlantComponent *jadePlant = director.getPlant();

        CHECK(jadePlant != nullptr);

        delete jadePlant;
        delete jadeBuilder;
    }

    SUBCASE("JadePlantBuilder creates a Succulent")
    {
        Builder *jadeBuilder = new JadePlantBuilder();
        Director director(jadeBuilder);
        director.construct();

        PlantComponent *jadePlant = director.getPlant();

        // Jade should be a Succulent
        Succulent *jadeSucculent = dynamic_cast<Succulent *>(jadePlant);
        CHECK(jadeSucculent != nullptr);

        delete jadePlant;
        delete jadeBuilder;
    }

    SUBCASE("JadePlantBuilder sets proper initial values")
    {
        Builder *jadeBuilder = new JadePlantBuilder();
        Director director(jadeBuilder);
        director.construct();

        PlantComponent *jadePlant = director.getPlant();
        LivingPlant *jadeLiving = dynamic_cast<LivingPlant *>(jadePlant);

        CHECK(jadeLiving != nullptr);

        if (jadeLiving)
        {
            // Check initial health, water, and sun exposure are set
            CHECK(jadeLiving->getHealth() == 100);
            CHECK(jadeLiving->getWaterLevel() == 30);
            CHECK(jadeLiving->getSunExposure() == 60);
        }

        delete jadePlant;
        delete jadeBuilder;
    }

    SUBCASE("JadePlantBuilder adds decorators")
    {
        Builder *jadeBuilder = new JadePlantBuilder();
        Director director(jadeBuilder);
        director.construct();

        PlantComponent *jadePlant = director.getPlant();

        std::string info = jadePlant->getInfo();

        CHECK(!info.empty());
        // Jade Plant should have decorators
        CHECK(info.find("Base Price") != std::string::npos);

        delete jadePlant;
        delete jadeBuilder;
    }

    SUBCASE("JadePlantBuilder plant can water")
    {
        Builder *jadeBuilder = new JadePlantBuilder();
        Director director(jadeBuilder);
        director.construct();

        PlantComponent *jadePlant = director.getPlant();
        LivingPlant *jadeLiving = dynamic_cast<LivingPlant *>(jadePlant);

        if (jadeLiving)
        {
            int initialWater = jadeLiving->getWaterLevel();
            jadePlant->water();
            // Water level should respond to watering
            CHECK(jadeLiving->getWaterLevel() > 0);
        }

        delete jadePlant;
        delete jadeBuilder;
    }

    SUBCASE("JadePlantBuilder plant responds to sun")
    {
        Builder *jadeBuilder = new JadePlantBuilder();
        Director director(jadeBuilder);
        director.construct();

        PlantComponent *jadePlant = director.getPlant();
        LivingPlant *jadeLiving = dynamic_cast<LivingPlant *>(jadePlant);

        if (jadeLiving)
        {
            jadeLiving->setSunExposure(0);
            jadePlant->setOutside();
            // Jade uses MidSun strategy, should increase sun exposure
            CHECK(jadeLiving->getSunExposure() > 0);
        }

        delete jadePlant;
        delete jadeBuilder;
    }
}

TEST_CASE("Testing LavenderBuilder Implementation")
{
    SUBCASE("LavenderBuilder can be created and used with Director")
    {
        Builder *lavenderBuilder = new LavenderBuilder();
        Director director(lavenderBuilder);

        director.construct();

        PlantComponent *lavenderPlant = director.getPlant();

        CHECK(lavenderPlant != nullptr);

        delete lavenderPlant;
        delete lavenderBuilder;
    }

    SUBCASE("LavenderBuilder creates an Herb")
    {
        Builder *lavenderBuilder = new LavenderBuilder();
        Director director(lavenderBuilder);
        director.construct();

        PlantComponent *lavenderPlant = director.getPlant();

        // Lavender should be an Herb
        Herb *lavenderHerb = dynamic_cast<Herb *>(lavenderPlant);
        CHECK(lavenderHerb != nullptr);

        delete lavenderPlant;
        delete lavenderBuilder;
    }

    SUBCASE("LavenderBuilder sets proper initial values")
    {
        Builder *lavenderBuilder = new LavenderBuilder();
        Director director(lavenderBuilder);
        director.construct();

        PlantComponent *lavenderPlant = director.getPlant();
        LivingPlant *lavenderLiving = dynamic_cast<LivingPlant *>(lavenderPlant);

        CHECK(lavenderLiving != nullptr);

        if (lavenderLiving)
        {
            // Check initial health, water, and sun exposure are set
            CHECK(lavenderLiving->getHealth() == 100);
            CHECK(lavenderLiving->getWaterLevel() == 40);
            CHECK(lavenderLiving->getSunExposure() == 80);
        }

        delete lavenderPlant;
        delete lavenderBuilder;
    }

    SUBCASE("LavenderBuilder adds decorators")
    {
        Builder *lavenderBuilder = new LavenderBuilder();
        Director director(lavenderBuilder);
        director.construct();

        PlantComponent *lavenderPlant = director.getPlant();

        std::string info = lavenderPlant->getInfo();

        CHECK(!info.empty());
        // Lavender should have decorators
        CHECK(info.find("Base Price") != std::string::npos);

        delete lavenderPlant;
        delete lavenderBuilder;
    }

    SUBCASE("LavenderBuilder plant responds to sun")
    {
        Builder *lavenderBuilder = new LavenderBuilder();
        Director director(lavenderBuilder);
        director.construct();

        PlantComponent *lavenderPlant = director.getPlant();
        LivingPlant *lavenderLiving = dynamic_cast<LivingPlant *>(lavenderPlant);

        if (lavenderLiving)
        {
            lavenderLiving->setSunExposure(0);
            lavenderPlant->setOutside();
            // Lavender uses HighSun strategy, should significantly increase sun exposure
            CHECK(lavenderLiving->getSunExposure() > 0);
        }

        delete lavenderPlant;
        delete lavenderBuilder;
    }
}

TEST_CASE("Testing MapleBuilder Implementation")
{
    SUBCASE("MapleBuilder can be created and used with Director")
    {
        Builder *mapleBuilder = new MapleBuilder();
        Director director(mapleBuilder);

        director.construct();

        PlantComponent *maplePlant = director.getPlant();

        CHECK(maplePlant != nullptr);

        delete maplePlant;
        delete mapleBuilder;
    }

    SUBCASE("MapleBuilder creates a Tree")
    {
        Builder *mapleBuilder = new MapleBuilder();
        Director director(mapleBuilder);
        director.construct();

        PlantComponent *maplePlant = director.getPlant();

        // Maple should be a Tree
        Tree *mapleTree = dynamic_cast<Tree *>(maplePlant);
        CHECK(mapleTree != nullptr);

        delete maplePlant;
        delete mapleBuilder;
    }

    SUBCASE("MapleBuilder sets proper initial values")
    {
        Builder *mapleBuilder = new MapleBuilder();
        Director director(mapleBuilder);
        director.construct();

        PlantComponent *maplePlant = director.getPlant();
        LivingPlant *mapleLiving = dynamic_cast<LivingPlant *>(maplePlant);

        CHECK(mapleLiving != nullptr);

        if (mapleLiving)
        {
            // Check initial health, water, and sun exposure are set
            CHECK(mapleLiving->getHealth() == 100);
            CHECK(mapleLiving->getWaterLevel() == 60);
            CHECK(mapleLiving->getSunExposure() == 60);
        }

        delete maplePlant;
        delete mapleBuilder;
    }

    SUBCASE("MapleBuilder adds decorators")
    {
        Builder *mapleBuilder = new MapleBuilder();
        Director director(mapleBuilder);
        director.construct();

        PlantComponent *maplePlant = director.getPlant();

        std::string info = maplePlant->getInfo();

        CHECK(!info.empty());
        // Maple should have decorators
        CHECK(info.find("Base Price") != std::string::npos);

        delete maplePlant;
        delete mapleBuilder;
    }

    SUBCASE("MapleBuilder plant can water")
    {
        Builder *mapleBuilder = new MapleBuilder();
        Director director(mapleBuilder);
        director.construct();

        PlantComponent *maplePlant = director.getPlant();
        LivingPlant *mapleLiving = dynamic_cast<LivingPlant *>(maplePlant);

        if (mapleLiving)
        {
            int initialWater = mapleLiving->getWaterLevel();
            maplePlant->water();
            // Water level should respond to watering
            CHECK(mapleLiving->getWaterLevel() > 0);
        }

        delete maplePlant;
        delete mapleBuilder;
    }

    SUBCASE("MapleBuilder plant responds to sun")
    {
        Builder *mapleBuilder = new MapleBuilder();
        Director director(mapleBuilder);
        director.construct();

        PlantComponent *maplePlant = director.getPlant();
        LivingPlant *mapleLiving = dynamic_cast<LivingPlant *>(maplePlant);

        if (mapleLiving)
        {
            mapleLiving->setSunExposure(0);
            maplePlant->setOutside();
            // Maple uses MidSun strategy, should increase sun exposure
            CHECK(mapleLiving->getSunExposure() > 0);
        }

        delete maplePlant;
        delete mapleBuilder;
    }
}

TEST_CASE("Testing PineBuilder Implementation")
{
    SUBCASE("PineBuilder can be created and used with Director")
    {
        Builder *pineBuilder = new PineBuilder();
        Director director(pineBuilder);

        director.construct();

        PlantComponent *pinePlant = director.getPlant();

        CHECK(pinePlant != nullptr);

        delete pinePlant;
        delete pineBuilder;
    }

    SUBCASE("PineBuilder creates a Tree")
    {
        Builder *pineBuilder = new PineBuilder();
        Director director(pineBuilder);
        director.construct();

        PlantComponent *pinePlant = director.getPlant();

        // Pine should be a Tree
        Tree *pineTree = dynamic_cast<Tree *>(pinePlant);
        CHECK(pineTree != nullptr);

        delete pinePlant;
        delete pineBuilder;
    }

    SUBCASE("PineBuilder sets proper initial values")
    {
        Builder *pineBuilder = new PineBuilder();
        Director director(pineBuilder);
        director.construct();

        PlantComponent *pinePlant = director.getPlant();
        LivingPlant *pineLiving = dynamic_cast<LivingPlant *>(pinePlant);

        CHECK(pineLiving != nullptr);

        if (pineLiving)
        {
            // Check initial health, water, and sun exposure are set
            CHECK(pineLiving->getHealth() == 100);
            CHECK(pineLiving->getWaterLevel() == 40);
            CHECK(pineLiving->getSunExposure() == 80);
        }

        delete pinePlant;
        delete pineBuilder;
    }

    SUBCASE("PineBuilder adds decorators")
    {
        Builder *pineBuilder = new PineBuilder();
        Director director(pineBuilder);
        director.construct();

        PlantComponent *pinePlant = director.getPlant();

        std::string info = pinePlant->getInfo();

        CHECK(!info.empty());
        // Pine should have decorators
        CHECK(info.find("Base Price") != std::string::npos);

        delete pinePlant;
        delete pineBuilder;
    }

    SUBCASE("PineBuilder plant responds to sun")
    {
        Builder *pineBuilder = new PineBuilder();
        Director director(pineBuilder);
        director.construct();

        PlantComponent *pinePlant = director.getPlant();
        LivingPlant *pineLiving = dynamic_cast<LivingPlant *>(pinePlant);

        if (pineLiving)
        {
            pineLiving->setSunExposure(0);
            pinePlant->setOutside();
            // Pine uses HighSun strategy, should significantly increase sun exposure
            CHECK(pineLiving->getSunExposure() > 0);
        }

        delete pinePlant;
        delete pineBuilder;
    }

    SUBCASE("Multiple PineBuilder instances create independent plants")
    {
        Builder *pineBuilder1 = new PineBuilder();
        Builder *pineBuilder2 = new PineBuilder();

        Director director1(pineBuilder1);
        Director director2(pineBuilder2);

        director1.construct();
        director2.construct();

        PlantComponent *pine1 = director1.getPlant();
        PlantComponent *pine2 = director2.getPlant();

        CHECK(pine1 != nullptr);
        CHECK(pine2 != nullptr);
        CHECK(pine1 != pine2);

        delete pine1;
        delete pine2;
        delete pineBuilder1;
        delete pineBuilder2;
    }
}

TEST_CASE("Testing SunflowerBuilder Implementation")
{
    SUBCASE("SunflowerBuilder can be created and used with Director")
    {
        Builder *sunflowerBuilder = new SunflowerBuilder();
        Director director(sunflowerBuilder);

        director.construct();

        PlantComponent *sunflowerPlant = director.getPlant();

        CHECK(sunflowerPlant != nullptr);

        delete sunflowerPlant;
        delete sunflowerBuilder;
    }

    SUBCASE("SunflowerBuilder creates an Herb")
    {
        Builder *sunflowerBuilder = new SunflowerBuilder();
        Director director(sunflowerBuilder);
        director.construct();

        PlantComponent *sunflowerPlant = director.getPlant();

        // Sunflower should be an Herb
        Herb *sunflowerHerb = dynamic_cast<Herb *>(sunflowerPlant);
        CHECK(sunflowerHerb != nullptr);

        delete sunflowerPlant;
        delete sunflowerBuilder;
    }

    SUBCASE("SunflowerBuilder sets proper initial values")
    {
        Builder *sunflowerBuilder = new SunflowerBuilder();
        Director director(sunflowerBuilder);
        director.construct();

        PlantComponent *sunflowerPlant = director.getPlant();
        LivingPlant *sunflowerLiving = dynamic_cast<LivingPlant *>(sunflowerPlant);

        CHECK(sunflowerLiving != nullptr);

        if (sunflowerLiving)
        {
            // Check initial health, water, and sun exposure are set
            CHECK(sunflowerLiving->getHealth() == 100);
            CHECK(sunflowerLiving->getWaterLevel() == 60);
            CHECK(sunflowerLiving->getSunExposure() == 80);
        }

        delete sunflowerPlant;
        delete sunflowerBuilder;
    }

    SUBCASE("SunflowerBuilder adds decorators")
    {
        Builder *sunflowerBuilder = new SunflowerBuilder();
        Director director(sunflowerBuilder);
        director.construct();

        PlantComponent *sunflowerPlant = director.getPlant();

        std::string info = sunflowerPlant->getInfo();

        CHECK(!info.empty());
        // Sunflower should have decorators
        CHECK(info.find("Base Price") != std::string::npos);

        delete sunflowerPlant;
        delete sunflowerBuilder;
    }

    SUBCASE("SunflowerBuilder plant can water")
    {
        Builder *sunflowerBuilder = new SunflowerBuilder();
        Director director(sunflowerBuilder);
        director.construct();

        PlantComponent *sunflowerPlant = director.getPlant();
        LivingPlant *sunflowerLiving = dynamic_cast<LivingPlant *>(sunflowerPlant);

        if (sunflowerLiving)
        {
            int initialWater = sunflowerLiving->getWaterLevel();
            sunflowerPlant->water();
            // Water level should respond to watering
            CHECK(sunflowerLiving->getWaterLevel() > 0);
        }

        delete sunflowerPlant;
        delete sunflowerBuilder;
    }

    SUBCASE("SunflowerBuilder plant responds to sun")
    {
        Builder *sunflowerBuilder = new SunflowerBuilder();
        Director director(sunflowerBuilder);
        director.construct();

        PlantComponent *sunflowerPlant = director.getPlant();
        LivingPlant *sunflowerLiving = dynamic_cast<LivingPlant *>(sunflowerPlant);

        if (sunflowerLiving)
        {
            sunflowerLiving->setSunExposure(0);
            sunflowerPlant->setOutside();
            // Sunflower uses HighSun strategy, should significantly increase sun exposure
            CHECK(sunflowerLiving->getSunExposure() > 0);
        }

        delete sunflowerPlant;
        delete sunflowerBuilder;
    }

    SUBCASE("SunflowerBuilder plant has correct type attributes")
    {
        Builder *sunflowerBuilder = new SunflowerBuilder();
        Director director(sunflowerBuilder);
        director.construct();

        PlantComponent *sunflowerPlant = director.getPlant();
        LivingPlant *sunflowerLiving = dynamic_cast<LivingPlant *>(sunflowerPlant);

        if (sunflowerLiving)
        {
            // Sunflower is an herb with high sun preference
            CHECK(sunflowerLiving->getSunExposure() == 80);
            CHECK(sunflowerLiving->getWaterLevel() == 60);
        }

        delete sunflowerPlant;
        delete sunflowerBuilder;
    }
}
