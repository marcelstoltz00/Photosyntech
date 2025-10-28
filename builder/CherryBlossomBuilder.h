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


public:
    /**
     * @brief Constructor for CherryBlossomBuilder.
     */
    CherryBlossomBuilder();

    /**
     * @brief Creates a new Tree object as the base for the Cherry Blossom.
     */
    void createObject() ;

    /**
     * @brief Assigns MidWater strategy to the Cherry Blossom tree.
     */
    void assignWaterStrategy() ;

    /**
     * @brief Assigns MidSun strategy to the Cherry Blossom tree.
     */
    void assignSunStrategy() ;

    /**
     * @brief Assigns initial Seed state to the Cherry Blossom tree.
     */
    void assignMaturityState() ;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Cherry Blossom tree.
     */
    void setUp() ;

    /**
     * @brief Adds decorators to the PlantComponent.
     * 
     * Applies the following decorators in sequence:
     * - Spring season
     * - Large Flowers
     * - Small Leaves
     * - Large Stem
     */
    void addDecorators() ;



};

#endif // CHERRYBLOSSOMBUILDER_H