#ifndef PINEBUILDER_H
#define PINEBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Pine trees.
 *
 * Implements the Builder interface to construct Pine trees with specific attributes:
 * - Base Type: Tree
 * - Sun Strategy: HighSun (80% initial exposure)
 * - Water Strategy: LowWater (40% initial level)
 * - Initial Health: 100%
 * - Decorators: Winter, Small Leaves, Large Stem
 * - Initial State: Seed
 *
 * @see Builder The abstract builder interface
 * @see Tree The base plant type
 * @see HighSun The sun exposure strategy
 * @see LowWater The watering strategy
 * @see Seed The initial maturity state
 */
class PineBuilder : public Builder
{
private:
  	LivingPlant *plant = nullptr;


public:
    /**
     * @brief Constructor for PineBuilder.
     */
    PineBuilder();

    /**
     * @brief Creates a new Tree object as the base for the Pine.
     */
    void createObject() override;

    /**
     * @brief Assigns LowWater strategy to the Pine tree.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns HighSun strategy to the Pine tree.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Pine tree.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Pine tree.
     */
    void setUp() override;
    /**
     * @brief Adds decorators to the LivingPlant.
     * 
     * Applies the following decorators in sequence:
     * - Winter season
     * - Small Leaves
     * - Large Stem
     */
    void addDecorators() override;
    /**
     * @brief Returns the fully constructed Pine tree.
     * @return Pointer to the constructed Pine tree.
     */
    PlantComponent *getResult() override;

    /**
     * @brief Destructor for PineBuilder.
     */
    ~PineBuilder();
};

#endif // PINEBUILDER_H