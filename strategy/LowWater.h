#ifndef LowWater_h
#define LowWater_h

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for low-frequency, minimal watering.
 *
 * Implements a watering strategy with low water amounts and infrequent
 * watering schedules, suitable for drought-tolerant plants like succulents.
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
