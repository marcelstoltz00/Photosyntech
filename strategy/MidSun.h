#ifndef MidSun_h
#define MidSun_h

#include "SunStrategy.h"

/**
 * @brief Concrete strategy for moderate sunlight exposure.
 *
 * Implements a sun exposure strategy with medium intensity and duration,
 * suitable for plants that prefer partial shade or indirect sunlight.
 */
class MidSun : public SunStrategy
{
	public:
		/**
		 * @brief Applies moderate sunlight exposure to the plant.
		 * @param plant Pointer to the LivingPlant receiving sunlight.
		 * @return Integer representing the medium sun exposure applied.
		 */
		int addSun(LivingPlant* plant);

		/**
		 * @brief Gets the unique identifier for the MidSun strategy.
		 * @return Integer ID representing the MidSun strategy.
		 */
		static int getID();

		/**
		 * @brief Constructs a MidSun strategy with sensible defaults.
		 *
		 * Default sets intensity to 5 (moderate) and hoursNeeded to 5 (medium exposure).
		 */
		MidSun();
};

#endif
