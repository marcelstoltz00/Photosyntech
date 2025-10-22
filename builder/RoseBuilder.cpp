#include "RoseBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/MidWater.h"
#include "../prototype/Shrub.h"
#include "../decorator/plantDecorator/LargeFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Thorns.h"
#include "../state/Seed.h"

RoseBuilder::RoseBuilder() : plant(nullptr) {
}

void RoseBuilder::createObject() {
    if (!plant) {
        plant = new Shrub();
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

PlantComponent* RoseBuilder::getResult() {
    return plant->clone();
}

void RoseBuilder::addDecorators() {

// if (plant) {
    //     plant->addAttribute(new Spring(plant));
//         plant->addAttribute(new LargeFlowers(plant));
//         plant->addAttribute(new SmallLeaf(plant));
//         plant->addAttribute(new LargeStem(plant));
//         plant->addAttribute(new Thorns(plant));
//     }

}
void RoseBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);
        plant->setWaterLevel(60);
        plant->setSunExposure(60);
    }
}

RoseBuilder::~RoseBuilder() {
}