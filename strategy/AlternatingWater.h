#ifndef AlternatingWater_h
#define AlternatingWater_h

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for alternating wet/dry watering cycles.
 *
 * Implements a watering strategy that alternates between wet and dry periods,
 * suitable for plants that prefer cyclical moisture patterns and need periods
 * of drought between watering sessions.
 *
 * **System Role:**
 * Specialized watering strategy for plants needing drought cycles (certain bulbs,
 * orchids). Applied via Builder. Most sophisticated water algorithm with cycle tracking.
 * Shared via flyweight factory across all alternating-water plants.
 *
 * **Pattern Role:** Concrete Strategy (implements cyclic-water algorithm)
 *
 * **Related Patterns:**
 * - WaterStrategy: Implements abstract interface
 * - LivingPlant: Context using this strategy
 * - Builder: Assigns to specialized plant types
 * - Singleton: Cached by flyweight factory
 *
 * **System Interactions:**
 * - Builder assigns to specialized/premium plant species
 * - water() applies cyclic watering pattern
 * - getID() returns consistent identifier for caching
 * - Requires stateful tracking between executions
 *
 * @see WaterStrategy (abstract interface)
 * @see LivingPlant (context)
 */
class AlternatingWater : public WaterStrategy
{
	public:
		/**
		 * @brief Applies alternating watering pattern to the plant.
		 * @return Integer representing the water amount for current cycle.
		 */
		int water();

		/**
		 * @brief Gets the unique identifier for the AlternatingWater strategy.
		 * @return Integer ID representing the AlternatingWater strategy.
		 */
		int getID();
};

#endif
