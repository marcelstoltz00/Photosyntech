// please use testing like this.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "singleton/Singleton.h"
#include "prototype/Tree.h"
#include "state/Seed.h"
#include "decorator/plantDecorator/Autumn.h"
#include "doctest.h"
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Succulent.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "strategy/AlternatingWater.h"
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
#include "builder/Director.h"
#include "builder/RoseBuilder.h"
#include "builder/CactusBuilder.h"
TEST_CASE("Overall Testing of flyweight strings + error handling")
{
    FlyweightFactory<int, string *> *fac = new FlyweightFactory<int, string *>();

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

    SUBCASE("Correct exception handling")
    {
        CHECK(Inventory::getInstance()->getWaterFly(5000)->getState()->water(plant) == 10);

        CHECK(*Inventory::getInstance()->getString("Insert1")->getState() == "Insert1");
    }

    delete plant;

    delete inv;
}

TEST_CASE("Testing decorator")
{
    LivingPlant *plant = new Tree();
    plant->addAttribute(new Autumn());
    delete Inventory::getInstance();
    delete plant->getDecorator();

    delete Inventory::getInstance();
}



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

        CHECK(plant->getWaterLevel() == 10);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(2); 
        plant->water();
        CHECK(plant->getWaterLevel() == 20);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(3); 
        plant->water();
        CHECK(plant->getWaterLevel() == 30);
    }
    
    SUBCASE("Sun strategy switching") {
        plant->setSunExposure(0);
        plant->setSunStrategy(1); 
        plant->setOutside();
        CHECK(plant->getSunExposure() == 6);

        plant->setSunExposure(0);
        plant->setSunStrategy(2); 
        plant->setOutside();
        CHECK(plant->getSunExposure() == 25);

        plant->setSunExposure(0);
        plant->setSunStrategy(3); 
        plant->setOutside();
        CHECK(plant->getSunExposure() == 72);
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

TEST_CASE("Testing Builder Pattern Implementation") {
    SUBCASE("Testing Director-Builder Interaction") {
        Builder* roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        
        director.construct();
        
        PlantComponent* rosePlant = director.getPlant();
        
        CHECK(rosePlant != nullptr);
        
        delete rosePlant;
        delete roseBuilder;
    }
    
    SUBCASE("Testing Rose Plant Properties") {
        Builder* roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        director.construct();
        
        PlantComponent* rosePlant = director.getPlant();
        
        std::string info = rosePlant->getInfo();
        
        CHECK(!info.empty());
        CHECK(info.find("Base Price") != std::string::npos);
        
        rosePlant->water();
        
        delete rosePlant;
        delete roseBuilder;
    }
    
    SUBCASE("Testing Cactus Builder") {
        Builder* cactusBuilder = new CactusBuilder();
        Director director(cactusBuilder);
        director.construct();
        
        PlantComponent* cactusPlant = director.getPlant();
        
        std::string info = cactusPlant->getInfo();
        
        CHECK(!info.empty());
        CHECK(info.find("Water Level") != std::string::npos);
        CHECK(info.find("Sun Exposure") != std::string::npos);
        
        cactusPlant->setOutside();
        
        delete cactusPlant;
        delete cactusBuilder;
    }
    
    SUBCASE("Testing Builder Pattern with Multiple Plants") {
        Builder* roseBuilder = new RoseBuilder();
        Builder* cactusBuilder = new CactusBuilder();
        
        Director director(roseBuilder);
        
        director.construct();
        PlantComponent* rosePlant = director.getPlant();
        Director director2(cactusBuilder);
        director2.construct();
        PlantComponent* cactusPlant = director2.getPlant();
        
        CHECK(rosePlant != nullptr);
        CHECK(cactusPlant != nullptr);
        
        CHECK(rosePlant->getInfo() != cactusPlant->getInfo());
        

        LivingPlant* roseLivingPlant = dynamic_cast<LivingPlant*>(rosePlant);
        LivingPlant* cactusLivingPlant = dynamic_cast<LivingPlant*>(cactusPlant);
        
        if (roseLivingPlant && cactusLivingPlant) {
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
    
    SUBCASE("Testing Complete Builder Process") {
      
        Builder* roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        director.construct();
        PlantComponent* rosePlant = director.getPlant();
        
        LivingPlant* roseLivingPlant = dynamic_cast<LivingPlant*>(rosePlant);
        CHECK(roseLivingPlant != nullptr);
        
        if (roseLivingPlant) {

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
