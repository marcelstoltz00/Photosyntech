#include "MapleBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/MidWater.h"
#include "../prototype/Tree.h"
#include "../decorator/plantDecorator/LargeLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Autumn.h"
#include "../state/Seed.h"

MapleBuilder::MapleBuilder() : plant(nullptr) {
}

void MapleBuilder::createObject() {
    if (!plant) {
        plant = new Tree();
    }
}

void MapleBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(MidWater::getID());
    }
}

void MapleBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(MidSun::getID());
    }
}

void MapleBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

PlantComponent* MapleBuilder::getResult() {
    return plant->clone();
}
void MapleBuilder::addDecorators() {
    if (plant) {
        PlantComponent *season = new Autumn();
        plant->setSeason(Inventory::getInstance()->getString(season->getName()));
        plant->addAttribute(season);
        plant->addAttribute(new LargeLeaf());
        plant->addAttribute(new LargeStem());
    }
}

void MapleBuilder::setUp() {
    if (plant) {
        plant->setHealth(100); 
        plant->setWaterLevel(60);   
        plant->setSunExposure(60);    
    }
}

MapleBuilder::~MapleBuilder() {
     if (plant)
    {
        delete plant;
        plant = nullptr;
    }
}