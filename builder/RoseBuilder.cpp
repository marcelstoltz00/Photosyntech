#include "RoseBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/MidWater.h"
#include "../prototype/Shrub.h"
#include "../decorator/plantDecorator/LargeFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Thorns.h"
#include "../decorator/plantDecorator/Spring.h"
#include "../state/Seed.h"

RoseBuilder::RoseBuilder() : Builder() {
}

void RoseBuilder::createObject() {
    if (!plant) {
        plant = new Shrub("Rose");
    }
}

void RoseBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(MidWater::getID());
    }
}

void RoseBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(MidSun::getID());
    }
}

void RoseBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}



void RoseBuilder::addDecorators() {
    if (plant) {
          PlantComponent *season = new Spring();
        plant->setSeason(Inventory::getInstance()->getString(season->getName()));
        plant->addAttribute(season);
        plant->addAttribute(new LargeFlowers());
        plant->addAttribute(new SmallLeaf());
        plant->addAttribute(new LargeStem());
        plant->addAttribute(new Thorns());
    }
}
void RoseBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);
        plant->setWaterLevel(60);
        plant->setSunExposure(60);
    }
}

