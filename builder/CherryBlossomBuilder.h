#ifndef CHERRYBLOSSOMBUILDER_H
#define CHERRYBLOSSOMBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Cherry Blossom trees.
 *
 * Implements the Builder interface to construct Cherry Blossom trees with specific attributes:
 * - Base Type: Tree
 * - Sun Strategy: MidSun (60% initial exposure)
 * - Water Strategy: MidWater (60% initial level)
 * - Initial Health: 100%
 * - Decorators: Spring, Large Flowers, Small Leaves, Large Stem
 * - Initial State: Seed
 *
 * @see Builder The abstract builder interface
 * @see Tree The base plant type
 * @see MidSun The sun exposure strategy
 * @see MidWater The watering strategy
 * @see Seed The initial maturity state
 */
class CherryBlossomBuilder : public Builder
{
private:
	LivingPlant *plant = nullptr;
	PlantAttributes*season= nullptr;

public:
    /**
     * @brief Constructor for CherryBlossomBuilder.
     */
    CherryBlossomBuilder();

    /**
     * @brief Creates a new Tree object as the base for the Cherry Blossom.
     */
    void createObject() override;

    /**
     * @brief Assigns MidWater strategy to the Cherry Blossom tree.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns MidSun strategy to the Cherry Blossom tree.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Cherry Blossom tree.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Cherry Blossom tree.
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
     */
    void addDecorators() override;
    /**
     * @brief Returns the fully constructed Cherry Blossom tree.
     * @return Pointer to the constructed Cherry Blossom tree.
     */
      PlantComponent *getResult() override;

    /**
     * @brief Destructor for CherryBlossomBuilder.
     */
    ~CherryBlossomBuilder();
};

#endif // CHERRYBLOSSOMBUILDER_H