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


public:
  /**
   * @brief Constructor for RoseBuilder.
   */
  RoseBuilder();

  /**
   * @brief Creates a new Shrub object as the base for the Rose.
   */
  void createObject() ;

  /**
   * @brief Assigns MidWater strategy to the Rose plant.
   */
  void assignWaterStrategy() ;

  /**
   * @brief Assigns MidSun strategy to the Rose plant.
   */
  void assignSunStrategy() ;

  /**
   * @brief Assigns initial Seed state to the Rose plant.
   */
  void assignMaturityState() ;

  /**
   * @brief Sets up the initial health, water, and sun levels for the Rose plant.
   */
  void setUp() ;

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
  void addDecorators() ;

};

#endif // ROSEBUILDER_H