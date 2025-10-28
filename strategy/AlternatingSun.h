#ifndef AlternatingSun_h
#define AlternatingSun_h

#include "SunStrategy.h"

/**
 * @brief Concrete strategy for alternating sun exposure.
 *
 * Implements a sun exposure strategy that alternates between high and low intensity.
 */
class AlternatingSun : public SunStrategy
{
	public:
		/**
		 * @brief Applies alternating sunlight exposure to the plant.
		 * @param plant Pointer to the LivingPlant receiving sunlight.
		 * @return Integer representing the sun exposure applied.
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
