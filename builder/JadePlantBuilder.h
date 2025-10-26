#ifndef JADEPLANTBUILDER_H
#define JADEPLANTBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Jade plants.
 *
 * Implements the Builder interface to construct Jade plants with specific attributes:
 * - Base Type: Succulent
 * - Sun Strategy: MidSun
 * - Water Strategy: LowWater
 * - Decorators: Small Flowers, Small Leaves, Medium Stem, No Thorns
 *
 * @see Builder
 * @see Succulent
 */
class JadePlantBuilder : public Builder
{


public:
    /**
     * @brief Constructor for JadePlantBuilder.
     */
    JadePlantBuilder();

    /**
     * @brief Creates a new Succulent object as the base for the Jade plant.
     */
    void createObject() ;

    /**
     * @brief Assigns LowWater strategy to the Jade plant.
     */
    void assignWaterStrategy() ;

    /**
     * @brief Assigns MidSun strategy to the Jade plant.
     */
    void assignSunStrategy() ;

    /**
     * @brief Assigns initial Seed state to the Jade plant.
     */
    void assignMaturityState() ;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Jade plant.
     */
    void setUp() ;

    /**
     * @brief Adds decorators to the LivingPlant.
     */
    void addDecorators() ;


};

#endif // JADEPLANTBUILDER_H