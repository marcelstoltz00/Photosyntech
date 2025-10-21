#include "LavenderBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Herb.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
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

LivingPlant* LavenderBuilder::getResult() {
    return plant;
}

void LavenderBuilder::addDecorators() {

    // if (plant) {
    //     plant->addAttribute(new SmallFlowers(plant));
    //     plant->addAttribute(new SmallLeaf(plant));
    //     plant->addAttribute(new LargeStem(plant));
    // }
}

void LavenderBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);  // Full health
        plant->setWaterLevel(40);    // Low water requirement for lavender
        plant->setSunExposure(80);      // High sun requirement for lavender
    }
}

LavenderBuilder::~LavenderBuilder() {
}