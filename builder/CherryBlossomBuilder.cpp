#include "CherryBlossomBuilder.h"
#include "../strategy/MidSun.h"
#include "../strategy/MidWater.h"
#include "../prototype/Tree.h"
#include "../decorator/plantDecorator/LargeFlowers.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../state/Seed.h"

CherryBlossomBuilder::CherryBlossomBuilder() : plant(nullptr) {
}

void CherryBlossomBuilder::createObject() {
    if (!plant) {
        plant = new Tree();
    }
}

void CherryBlossomBuilder::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(MidWater::getID());
    }
}

void CherryBlossomBuilder::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(MidSun::getID());
    }
}

void CherryBlossomBuilder::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

LivingPlant* CherryBlossomBuilder::getResult() {
    return plant;
}

void CherryBlossomBuilder::addDecorators(){
//  if (plant) {
//         plant->addAttribute(new LargeFlowers(plant));
//         plant->addAttribute(new SmallLeaf(plant));
//         plant->addAttribute(new LargeStem(plant));
//     }

}

CherryBlossomBuilder::~CherryBlossomBuilder() {
}