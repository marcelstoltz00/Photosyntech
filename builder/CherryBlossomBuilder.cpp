#include "CherryBlossomBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/MidWater.h"
#include "../prototype/Tree.h"
#include "../decorator/plantDecorator/LargeFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Spring.h"
#include "../state/Seed.h"

CherryBlossomBuilder::CherryBlossomBuilder() : plant(nullptr) {
}

void CherryBlossomBuilder::createObject() {
    if (!plant) {
        plant = new Tree();
    }
}

void CherryBlossomBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(MidWater::getID());
    }
}

void CherryBlossomBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(MidSun::getID());
    }
}

void CherryBlossomBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

PlantComponent* CherryBlossomBuilder::getResult() {
    return plant->getDecorator()->clone();
}

void CherryBlossomBuilder::addDecorators() {
    if (plant) {
        PlantComponent *season = new Spring();
        plant->setSeason(Inventory::getInstance()->getString(season->getName()));
        plant->addAttribute(season);

        plant->addAttribute(new LargeFlowers());
        plant->addAttribute(new SmallLeaf());
        plant->addAttribute(new LargeStem());
    }
}

void CherryBlossomBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);
        plant->setWaterLevel(60);   
        plant->setSunExposure(60);      
    }
}

CherryBlossomBuilder::~CherryBlossomBuilder() {
     if (plant)
    {
        delete plant->getDecorator();
        plant = nullptr;
    }
}