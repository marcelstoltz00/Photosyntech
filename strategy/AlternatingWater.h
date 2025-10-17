#ifndef __AlternatingWater_h__
#define __AlternatingWater_h__

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for alternating wet/dry watering cycles.
 *
 * Implements a watering strategy that alternates between wet and dry periods,
 * suitable for plants that prefer cyclical moisture patterns and need periods
 * of drought between watering sessions.
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
