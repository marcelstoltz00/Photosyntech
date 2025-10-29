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
 * Builder during plant construction. Executed via Facade during plant care operations.
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
 * - water() applies abundant water amount directly to plant object
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
	 * @param plant Pointer to the plant to be watered.
	 * @return Integer representing the abundant water amount applied.
	 */
	int water(LivingPlant *plant);

	/**
	 * @brief Gets the unique identifier for the HighWater strategy.
	 * @return Integer ID representing the HighWater strategy.
	 */
	static int getID();

	/**
	 * @brief Constructs a HighWater strategy with a sensible default amount.
	 *
	 * Default sets WaterStrategy::waterAmount to 5 (abundant watering).
	 */
	HighWater();
};

#endif
