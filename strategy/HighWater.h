#ifndef __HighWater_h__
#define __HighWater_h__

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for high-frequency, abundant watering.
 *
 * Implements a watering strategy with high water amounts and frequent
 * watering schedules, suitable for water-loving plants and tropical species.
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
