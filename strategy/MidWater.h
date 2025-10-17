#ifndef __MidWater_h__
#define __MidWater_h__

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for moderate watering.
 *
 * Implements a watering strategy with medium water amounts and regular
 * watering schedules, suitable for most common houseplants.
 */
class MidWater : public WaterStrategy
{
	public:
		/**
		 * @brief Applies moderate watering to the plant.
		 * @return Integer representing the medium water amount applied.
		 */
		int water();

		/**
		 * @brief Gets the unique identifier for the MidWater strategy.
		 * @return Integer ID representing the MidWater strategy.
		 */
		int getID();
};

#endif
