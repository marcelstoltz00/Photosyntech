#ifndef SUNFLOWERBUILDER_H
#define SUNFLOWERBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Sunflower plants.
 *
 * Implements the Builder interface to construct Sunflower plants with specific attributes:
 * - Base Type: Herb
 * - Sun Strategy: HighSun (80% initial exposure)
 * - Water Strategy: MidWater (60% initial level)
 * - Initial Health: 100%
 * - Decorators: Summer, Large Flowers, Large Leaves, Large Stem
 * - Initial State: Seed
 *
 * @see Builder The abstract builder interface
 * @see Herb The base plant type
 * @see HighSun The sun exposure strategy
 * @see MidWater The watering strategy
 * @see Seed The initial maturity state
 */
class SunflowerBuilder : public Builder
{


public:
    /**
     * @brief Constructor for SunflowerBuilder.
     */
    SunflowerBuilder();

    /**
     * @brief Creates a new Herb object as the base for the Sunflower.
     */
    void createObject() override;

    /**
     * @brief Assigns MidWater strategy to the Sunflower plant.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns HighSun strategy to the Sunflower plant.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Sunflower plant.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Sunflower plant.
     */
    void setUp() override;
    /**
     * @brief Adds decorators to the LivingPlant.
     * 
     * Applies the following decorators in sequence:
     * - Summer season
     * - Large Flowers
     * - Large Leaves
     * - Large Stem
     */
    void addDecorators() override;

};

#endif // SUNFLOWERBUILDER_H