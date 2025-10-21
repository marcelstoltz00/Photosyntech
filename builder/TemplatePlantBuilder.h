#ifndef TEMPLATEPLANTBUILDER_H
#define TEMPLATEPLANTBUILDER_H

#include "Builder.h"
#include "../prototype/LivingPlant.h"
#include "../state/Seed.h"

// Forward declarations
class Tree;
class Herb;
class Shrub;
class Succulent;

class HighSun;
class MidSun;
class LowSun;

class HighWater;
class MidWater;
class LowWater;

/**
 * @brief Template builder for creating different types of plants with configurable parameters.
 */
template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
class TemplatePlantBuilder : public Builder {
private:
    LivingPlant* plant;
    int initialHealth;
    int initialWater;
    int initialSun;

public:
    TemplatePlantBuilder(int health = 100, int water = 50, int sun = 50);
    void createObject() override;
    void assignWaterStrategy() override;
    void assignSunStrategy() override;
    void assignMaturityState() override;
    void setUp();
    LivingPlant* getResult() override;
    virtual ~TemplatePlantBuilder();
};


using CherryBlossomBuilder = TemplatePlantBuilder<Tree, MidSun, MidWater>;
using CactusBuilder = TemplatePlantBuilder<Succulent, HighSun, LowWater>;
using RoseBuilder = TemplatePlantBuilder<Shrub, MidSun, MidWater>;
using SunflowerBuilder = TemplatePlantBuilder<Herb, HighSun, MidWater>;

#include "TemplatePlantBuilder.hpp"

#endif // TEMPLATEPLANTBUILDER_H