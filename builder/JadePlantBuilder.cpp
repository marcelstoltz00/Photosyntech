#include "JadePlantBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Succulent.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../state/Seed.h"

JadePlantBuilder::JadePlantBuilder() : plant(nullptr) {
}

void JadePlantBuilder::createObject() {
    if (!plant) {
        plant = new Succulent();
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

LivingPlant* JadePlantBuilder::getResult() {
    return plant;
}
void JadePlantBuilder::addDecorators() {
// if (plant) {
//         plant->addAttribute(new SmallFlowers(plant));
//         plant->addAttribute(new SmallLeaf(plant));
//         plant->addAttribute(new LargeStem(plant));
//     }

}

void JadePlantBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);  // Full health
        plant->setWaterLevel(30);    // Low water requirement for jade plants
        plant->setSunExposure(60);      // Medium sun requirement for jade plants
    }
}

JadePlantBuilder::~JadePlantBuilder() {
}