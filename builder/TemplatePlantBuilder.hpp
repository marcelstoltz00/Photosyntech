#ifndef TEMPLATEPLANTBUILDER_HPP
#define TEMPLATEPLANTBUILDER_HPP

// Implementation file for TemplatePlantBuilder; the corresponding header
// TemplatePlantBuilder.h should include this .hpp instead of including the
// header here to avoid recursive inclusion during preamble compilation.

#include "TemplatePlantBuilder.h"
#include "../prototype/LivingPlant.h"
#include "../state/Seed.h"


template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::TemplatePlantBuilder(
    int health, int water, int sun)
    : plant(NULL), initialHealth(health), initialWater(water), initialSun(sun) {}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::createObject() {
    if (!plant) {
        plant = new PlantType();
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(WaterStrategyType::getID());
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(SunStrategyType::getID());
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::setUp() {
    if (plant) {
        plant->setHealth(initialHealth);
        plant->setWaterLevel(initialWater);
        plant->setSunExposure(initialSun);
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
PlantComponent* TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::getResult() {
    if (!plant) return NULL;
    return plant->clone();
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::~TemplatePlantBuilder() {
    if (plant) {
        delete plant->getDecorator();
        plant = NULL;
    }
}

#endif // TEMPLATEPLANTBUILDER_HPP