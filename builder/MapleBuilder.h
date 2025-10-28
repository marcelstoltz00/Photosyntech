#ifndef MAPLEBUILDER_H
#define MAPLEBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Maple trees.
 *
 * Implements the Builder interface to construct Maple trees with specific attributes:
 * - Base Type: Tree
 * - Sun Strategy: MidSun
 * - Water Strategy: MidWater
 * - Initial Health: 100%
 * - Decorators: No Flowers, Large Leaves, Large Stem, No Thorns
 * - Initial State: Seed
 *
 * @see Builder
 * @see Tree
 */
class MapleBuilder : public Builder
{


public:
    /**
     * @brief Constructor for MapleBuilder.
     */
    MapleBuilder();

    /**
     * @brief Creates a new Tree object as the base for the Maple.
     */
    void createObject() ;

    /**
     * @brief Assigns MidWater strategy to the Maple tree.
     */
    void assignWaterStrategy() ;

    /**
     * @brief Assigns MidSun strategy to the Maple tree.
     */
    void assignSunStrategy() ;

    /**
     * @brief Assigns initial Seed state to the Maple tree.
     */
    void assignMaturityState() ;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Maple tree.
     */
    void setUp() ;
    /**
     * @brief Adds decorators to the PlantComponent.
     */
    void addDecorators() ;

};

#endif // MAPLEBUILDER_H