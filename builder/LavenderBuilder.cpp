#include "LavenderBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Herb.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Autumn.h"
#include "../state/Seed.h"


LavenderBuilder::LavenderBuilder() : plant(nullptr) {
}

void LavenderBuilder::createObject() {
    if (!plant) {
        plant = new Herb();
    }
}

void LavenderBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(LowWater::getID());
    }
}

void LavenderBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(HighSun::getID());
    }
}

void LavenderBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

PlantComponent* LavenderBuilder::getResult() {
    return plant->clone();
}

void LavenderBuilder::addDecorators() {
    if (plant) {
           PlantComponent *season = new Autumn();
        plant->setSeason(Inventory::getInstance()->getString(season->getName()));
        plant->addAttribute(season);
        plant->addAttribute(new SmallFlowers());
        plant->addAttribute(new SmallLeaf());
        plant->addAttribute(new LargeStem());
    }
}

void LavenderBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);  
        plant->setWaterLevel(40);
        plant->setSunExposure(80);    
    }
}

LavenderBuilder::~LavenderBuilder() {
}