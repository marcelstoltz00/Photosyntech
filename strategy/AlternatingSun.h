#ifndef AlternatingSun_h
#define AlternatingSun_h

#include "SunStrategy.h"

/**
 * @brief Concrete strategy for high-intensity, full sunlight exposure.
 *
 * Implements a sun exposure strategy with high intensity and long durations,
 * suitable for sun-loving plants that thrive in direct, bright sunlight.
 *
 * **System Role:**
 * Strategy for sun-loving plants (Succulents, Sunflowers, Shrubs). Applied via
 * Builder during plant construction. Staff care routines apply via strategy.
 * Shared via flyweight factory across all high-sun plants.
 *
 * **Pattern Role:** Concrete Strategy (implements high-sun algorithm)
 *
 * **Related Patterns:**
 * - SunStrategy: Implements abstract interface
 * - LivingPlant: Context using this strategy
 * - Builder: Assigns to sun-loving plant types
 * - Singleton: Cached by flyweight factory
 *
 * **System Interactions:**
 * - Builder assigns to sun-demanding species
 * - addSun() applies high-intensity sun exposure
 * - getID() returns consistent identifier for caching
 * - Shared across all high-sun plant instances
 *
 * @see SunStrategy (abstract interface)
 * @see LivingPlant (context)
 */
class AlternatingSun : public SunStrategy
{
	public:
		/**
		 * @brief Applies high-level sunlight exposure to the plant.
		 * @param plant Pointer to the LivingPlant receiving sunlight.
		 * @return Integer representing the abundant sun exposure applied.
		 */
		int addSun(LivingPlant* plant);

		/**
		 * @brief Gets the unique identifier for the AlternatingSun strategy.
		 * @return Integer ID representing the AlternatingSun strategy.
		 */
		static int getID();

		/**
		 * @brief Constructs a AlternatingSun strategy with sensible defaults.
		 *
		 * Default sets intensity to alternating levels and hoursNeeded to alternating durations.
		 */
		AlternatingSun();
};

#endif
