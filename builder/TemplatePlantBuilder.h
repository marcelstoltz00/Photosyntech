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
    void createObject() ;
    void assignWaterStrategy() ;
    void assignSunStrategy() ;
    void assignMaturityState() ;
    void setUp() ;
    PlantComponent* getResult() ;
    virtual ~TemplatePlantBuilder();
};


typedef TemplatePlantBuilder<Tree, MidSun, MidWater> CherryBlossomBuilder;
typedef TemplatePlantBuilder<Succulent, HighSun, LowWater> CactusBuilder;
typedef TemplatePlantBuilder<Shrub, MidSun, MidWater> RoseBuilder;
typedef TemplatePlantBuilder<Herb, HighSun, MidWater> SunflowerBuilder;



#endif // TEMPLATEPLANTBUILDER_H