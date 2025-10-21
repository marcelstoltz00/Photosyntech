#include "PineBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Tree.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../state/Seed.h"

PineBuilder::PineBuilder() : plant(nullptr) {
}

void PineBuilder::createObject() {
    if (!plant) {
        plant = new Tree();
    }
}

void PineBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(LowWater::getID());
    }
}

void PineBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(HighSun::getID());
    }
}

void PineBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

LivingPlant* PineBuilder::getResult() {
    return plant;
}

void PineBuilder::addDecorators() {
//  if (plant) {
//         plant->addAttribute(new SmallLeaf(plant));
//         plant->addAttribute(new LargeStem(plant));   
//     }
}
void PineBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);  // Full health
        plant->setWaterLevel(40);    // Low water requirement for pine trees
        plant->setSunExposure(80);      // High sun requirement for pine trees
    }
}

PineBuilder::~PineBuilder() {
}