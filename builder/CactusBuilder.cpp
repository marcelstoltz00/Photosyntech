#include "CactusBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Succulent.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Thorns.h"
#include "../state/Seed.h"

CactusBuilder::CactusBuilder() : plant(nullptr) {
}

void CactusBuilder::createObject() {
    if (!plant) {
        plant = new Succulent();
    }
}

void CactusBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(LowWater::getID());
    }
}

void CactusBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(HighSun::getID());
    }
}

void CactusBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

LivingPlant* CactusBuilder::getResult() {
    return plant;
}

void CactusBuilder::addDecorators() {
    // if (plant) {
    //     plant->addAttribute(new Summer(plant));
    //     plant->addAttribute(new SmallFlowers(plant));
    //     plant->addAttribute(new LargeStem(plant));
    //     plant->addAttribute(new Thorns(plant));
    // }
}

void CactusBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);  
        plant->setWaterLevel(30);   
        plant->setSunExposure(80);      
    }
}

CactusBuilder::~CactusBuilder() {
}