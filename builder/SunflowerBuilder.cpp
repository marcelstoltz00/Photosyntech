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

PlantComponent* SunflowerBuilder::getResult() {
    return plant->clone();
}

void SunflowerBuilder::addDecorators() {
    if (plant) {
        plant->addAttribute(new Summer());
        plant->addAttribute(new LargeFlowers());
        plant->addAttribute(new LargeLeaf());
        plant->addAttribute(new LargeStem());
    }
}

void SunflowerBuilder::setUp() {
    if (plant) {
        plant->setHealth(100); 
        plant->setWaterLevel(60);   
        plant->setSunExposure(80);      
    }
}

SunflowerBuilder::~SunflowerBuilder() {
}