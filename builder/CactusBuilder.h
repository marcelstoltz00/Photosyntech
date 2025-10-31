#ifndef CACTUSBUILDER_H
#define CACTUSBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Cactus plants.
 *
 * Implements the Builder interface to construct Cactus plants with specific attributes:
 * - Base Type: Succulent
 * - Sun Strategy: HighSun (80% initial exposure)
 * - Water Strategy: LowWater (30% initial level)
 * - Initial Health: 100%
 * - Decorators: Summer, Small Flowers, Large Stem, Thorns
 * - Initial State: Seed
 *
 * @see Builder The abstract builder interface
 * @see Succulent The base plant type
 * @see HighSun The sun exposure strategy
 * @see LowWater The watering strategy
 * @see Seed The initial maturity state
 */
class CactusBuilder : public Builder
{

 

public:
    /**
     * @brief Constructor for CactusBuilder.
     */
    CactusBuilder();
	virtual ~CactusBuilder(){};
    /**
     * @brief Creates a new Succulent object as the base for the Cactus.
     */
    void createObject();

    /**
     * @brief Assigns LowWater strategy to the Cactus plant.
     */
    void assignWaterStrategy();

    /**
     * @brief Assigns HighSun strategy to the Cactus plant.
     */
    void assignSunStrategy();

    /**
     * @brief Assigns initial Seed state to the Cactus plant.
     */
    void assignMaturityState();

    /**
     * @brief Sets up the initial health, water, and sun levels for the Cactus plant.
     */
    void setUp();
    /**
     * @brief Adds decorators to the PlantComponent.
     * 
     * Applies the following decorators in sequence:
     * - Summer season
     * - Small Flowers
     * - Large Stem
     * - Thorns
     */
    void addDecorators();

};

#endif // CACTUSBUILDER_H