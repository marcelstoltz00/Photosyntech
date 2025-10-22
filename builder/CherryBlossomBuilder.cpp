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

PlantComponent* CherryBlossomBuilder::getResult() {
    return plant->clone();
}

void CherryBlossomBuilder::addDecorators(){
//  if (plant) {
  //     plant->addAttribute(new Spring(plant));
//         plant->addAttribute(new LargeFlowers(plant));
//         plant->addAttribute(new SmallLeaf(plant));
//         plant->addAttribute(new LargeStem(plant));
//     }
}

void CherryBlossomBuilder::setUp() {
    if (plant) {
        plant->setHealth(100);
        plant->setWaterLevel(60);   
        plant->setSunExposure(60);      
    }
}

CherryBlossomBuilder::~CherryBlossomBuilder() {
}