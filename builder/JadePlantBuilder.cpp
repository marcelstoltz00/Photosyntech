#include "JadePlantBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Succulent.h"
#include "../decorator/plantDecorator/Winter.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../state/Seed.h"

JadePlantBuilder::JadePlantBuilder()  : Builder() {
}

void JadePlantBuilder::createObject() {
    if (!plant) {
        plant = new Succulent("Jade");
    }
}

void JadePlantBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(LowWater::getID());
    }
}

void JadePlantBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(MidSun::getID());
    }
}

void JadePlantBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}


void JadePlantBuilder::addDecorators() {
    if (plant) {
             PlantComponent *season = new Winter();
        plant->setSeason(Inventory::getInstance()->getString(season->getName()));
        plant->addAttribute(season);
    
        plant->addAttribute(new SmallFlowers());
        plant->addAttribute(new SmallLeaf());
        plant->addAttribute(new LargeStem());
    }
}

void JadePlantBuilder::setUp() {
    if (plant) {
        plant->setHealth(100); 
        plant->setWaterLevel(30);
        plant->setSunExposure(60);
    }
}

