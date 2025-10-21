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

MapleBuilder::~MapleBuilder() {
}