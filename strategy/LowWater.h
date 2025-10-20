#ifndef LowWater_h
#define LowWater_h

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for low-frequency, minimal watering.
 *
 * Implements a watering strategy with low water amounts and infrequent
 * watering schedules, suitable for drought-tolerant plants like succulents.
 *
 * **System Role:**
 * Strategy for drought-tolerant plants (Succulents, some Herbs). Applied via
 * Builder during plant construction. Executed by WaterPlantCommand during care.
 * Shared via flyweight factory across all low-water plants.
 *
 * **Pattern Role:** Concrete Strategy (implements low-water algorithm)
 *
 * **Related Patterns:**
 * - WaterStrategy: Implements abstract interface
 * - LivingPlant: Context using this strategy
 * - Builder: Assigns to appropriate plant types
 * - Singleton: Cached by flyweight factory
 *
 * **System Interactions:**
 * - Builder assigns to drought-tolerant plant species
 * - water() applies minimal water amount
 * - getID() returns consistent identifier for caching
 * - Shared across all succulent instances
 *
 * @see WaterStrategy (abstract interface)
 * @see LivingPlant (context)
 */
class LowWater : public WaterStrategy
{
	public:
		/**
		 * @brief Applies low-level watering to the plant.
		 * @return Integer representing the minimal water amount applied.
		 */
		int water();

		/**
		 * @brief Gets the unique identifier for the LowWater strategy.
		 * @return Integer ID representing the LowWater strategy.
		 */
		int getID();
};

#endif
