#ifndef ROSEBUILDER_H
#define ROSEBUILDER_H

#include "../builder/Builder.h"

/**
 * @brief Concrete builder for Rose plants.
 *
 * Implements the Builder interface to construct Rose plants with specific attributes:
 * - Base Type: Shrub
 * - Sun Strategy: MidSun (60% initial exposure)
 * - Water Strategy: MidWater (60% initial level)
 * - Initial Health: 100%
 * - Decorators: Spring, Large Flowers, Small Leaves, Large Stem, Thorns
 * - Initial State: Seed
 *
 * @see Builder The abstract builder interface
 * @see Shrub The base plant type
 * @see MidSun The sun exposure strategy
 * @see MidWater The watering strategy
 * @see Seed The initial maturity state
 */
class RoseBuilder : public Builder
{
private:
	LivingPlant *plant = nullptr;


public:
    /**
     * @brief Constructor for RoseBuilder.
     */
    RoseBuilder();

    /**
     * @brief Creates a new Shrub object as the base for the Rose.
     */
    void createObject() override;

    /**
     * @brief Assigns MidWater strategy to the Rose plant.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns MidSun strategy to the Rose plant.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Rose plant.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Rose plant.
     */
    void setUp() override;

    /**
     * @brief Adds decorators to the LivingPlant.
     * 
     * Applies the following decorators in sequence:
     * - Spring season
     * - Large Flowers
     * - Small Leaves
     * - Large Stem
     * - Thorns
     */
    void addDecorators() override;
    /**
     * @brief Returns the fully constructed Rose plant.
     * @return Pointer to the constructed Rose plant.
     */
   PlantComponent *getResult() override;

    /**
     * @brief Destructor for RoseBuilder.
     */
    ~RoseBuilder();
};

#endif // ROSEBUILDER_H