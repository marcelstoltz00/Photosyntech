#ifndef LAVENDERBUILDER_H
#define LAVENDERBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Lavender plants.
 *
 * Implements the Builder interface to construct Lavender plants with specific attributes:
 * - Base Type: Herb
 * - Sun Strategy: HighSun
 * - Water Strategy: LowWater
 * - Initial Health: 100%
 * - Decorators: Small Flowers, Small Leaves, Medium Stem, No Thorns
 * - Initial State: Seed
 *
 * @see Builder
 * @see Herb
 */
class LavenderBuilder : public Builder
{

 

public:
    /**
     * @brief Constructor for LavenderBuilder.
     */
    LavenderBuilder();

    /**
     * @brief Creates a new Herb object as the base for the Lavender.
     */
    void createObject() ;

    /**
     * @brief Assigns LowWater strategy to the Lavender plant.
     */
    void assignWaterStrategy() ;

    /**
     * @brief Assigns HighSun strategy to the Lavender plant.
     */
    void assignSunStrategy() ;

    /**
     * @brief Assigns initial Seed state to the Lavender plant.
     */
    void assignMaturityState() ;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Lavender plant.
     */
    void setUp() ;
    /**
     * @brief Adds decorators to the PlantComponent.
     */
    void addDecorators() ;

};

#endif // LAVENDERBUILDER_H