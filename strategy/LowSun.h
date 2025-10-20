#ifndef LowSun_h
#define LowSun_h

#include "SunStrategy.h"

/**
 * @brief Concrete strategy for low-intensity, shade-tolerant sunlight exposure.
 *
 * Implements a sun exposure strategy with low intensity and short durations,
 * suitable for shade-loving plants and indoor low-light environments.
 *
 * **System Role:**
 * Strategy for shade-tolerant plants (many Herbs, Ferns, indoor plants). Applied
 * via Builder. Enables indoor/low-light plant cultivation. Shared via flyweight
 * factory across all low-sun plants.
 *
 * **Pattern Role:** Concrete Strategy (implements low-sun algorithm)
 *
 * **Related Patterns:**
 * - SunStrategy: Implements abstract interface
 * - LivingPlant: Context using this strategy
 * - Builder: Assigns to shade-tolerant plant types
 * - Singleton: Cached by flyweight factory
 *
 * **System Interactions:**
 * - Builder assigns to shade-tolerant/indoor species
 * - addSun() applies minimal sun exposure
 * - getID() returns consistent identifier for caching
 * - Enables indoor nursery environments
 *
 * @see SunStrategy (abstract interface)
 * @see LivingPlant (context)
 */
class LowSun : public SunStrategy
{
	public:
		/**
		 * @brief Applies low-level sunlight exposure to the plant.
		 * @param plant Pointer to the LivingPlant receiving sunlight.
		 * @return Integer representing the minimal sun exposure applied.
		 */
		int addSun(LivingPlant* plant);

		/**
		 * @brief Gets the unique identifier for the LowSun strategy.
		 * @return Integer ID representing the LowSun strategy.
		 */
		static int getID();

		/**
		 * @brief Constructs a LowSun strategy with sensible defaults.
		 *
		 * Default sets intensity to 2 (low) and hoursNeeded to 3 (short exposure).
		 */
		LowSun();
};

#endif
