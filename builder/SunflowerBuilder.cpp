#include "SunflowerBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/MidWater.h"
#include "../prototype/Herb.h"
#include "../decorator/plantDecorator/LargeFlowers.h"
#include "../decorator/plantDecorator/LargeLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../state/Seed.h"

SunflowerBuilder::SunflowerBuilder() : plant(nullptr) {
}

void SunflowerBuilder::createObject() {
    if (!plant) {
        plant = new Herb();
    }
}

void SunflowerBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(MidWater::getID());
    }
}

void SunflowerBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(HighSun::getID());
    }
}

void SunflowerBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

LivingPlant* SunflowerBuilder::getResult() {
    return plant;
}

void SunflowerBuilder::addDecorators() {
// if (plant) {
//         plant->addAttribute(new LargeFlowers(plant));
//         plant->addAttribute(new LargeLeaf(plant)); 
//         plant->addAttribute(new LargeStem(plant));      
//     }
}

void SunflowerBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);  // Full health
        plant->setWaterLevel(60);    // Medium water requirement for sunflowers
        plant->setSunExposure(80);      // High sun requirement for sunflowers
    }
}

SunflowerBuilder::~SunflowerBuilder() {
}