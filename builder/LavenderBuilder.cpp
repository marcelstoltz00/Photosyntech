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

void LavenderBuilder::addDecorators() {}

LavenderBuilder::~LavenderBuilder() {
}