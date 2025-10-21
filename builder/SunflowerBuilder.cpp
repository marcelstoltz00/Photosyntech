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

SunflowerBuilder::~SunflowerBuilder() {
}