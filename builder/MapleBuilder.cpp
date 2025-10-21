#include "MapleBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/MidWater.h"
#include "../prototype/Tree.h"
#include "../decorator/plantDecorator/LargeLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../state/Seed.h"

MapleBuilder::MapleBuilder() : plant(nullptr) {
}

void MapleBuilder::createObject() {
    if (!plant) {
        plant = new Tree();
    }
}

void MapleBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(MidWater::getID());
    }
}

void MapleBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(MidSun::getID());
    }
}

void MapleBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

LivingPlant* MapleBuilder::getResult() {
    return plant;
}
void MapleBuilder::addDecorators() {
// if (plant) {
//         plant->addAttribute(new LargeLeaf(plant));
//         plant->addAttribute(new LargeStem(plant));   
//     }

}

void MapleBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);  // Full health
        plant->setWaterLevel(60);    // Medium water requirement for maple trees
        plant->setSunExposure(60);      // Medium sun requirement for maple trees
    }
}

MapleBuilder::~MapleBuilder() {
}