#ifndef HighWater_h
#define HighWater_h

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for high-frequency, abundant watering.
 *
 * Implements a watering strategy with high water amounts and frequent
 * watering schedules, suitable for water-loving plants and tropical species.
 *
 * **System Role:**
 * Strategy for water-loving plants (Ferns, Tropical species). Applied via
 * Builder during plant construction. Executed by WaterPlantCommand during care.
 * Shared via flyweight factory across all high-water plants.
 *
 * **Pattern Role:** Concrete Strategy (implements high-water algorithm)
 *
 * **Related Patterns:**
 * - WaterStrategy: Implements abstract interface
 * - LivingPlant: Context using this strategy
 * - Builder: Assigns to water-loving plant types
 * - Singleton: Cached by flyweight factory
 *
 * **System Interactions:**
 * - Builder assigns to tropical/water-loving species
 * - water() applies abundant water amount
 * - getID() returns consistent identifier for caching
 * - Shared across all high-water plant instances
 *
 * @see WaterStrategy (abstract interface)
 * @see LivingPlant (context)
 */
class HighWater : public WaterStrategy
{
	public:
		/**
		 * @brief Applies high-level watering to the plant.
		 * @return Integer representing the abundant water amount applied.
		 */
		int water();

		/**
		 * @brief Gets the unique identifier for the HighWater strategy.
		 * @return Integer ID representing the HighWater strategy.
		 */
		int getID();
};

#endif
