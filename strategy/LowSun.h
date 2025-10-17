#ifndef __LowSun_h__
#define __LowSun_h__

#include "SunStrategy.h"

/**
 * @brief Concrete strategy for low-intensity, shade-tolerant sunlight exposure.
 *
 * Implements a sun exposure strategy with low intensity and short durations,
 * suitable for shade-loving plants and indoor low-light environments.
 */
class LowSun : public SunStrategy
{
	public:
		/**
		 * @brief Applies low-level sunlight exposure to the plant.
		 * @return Integer representing the minimal sun exposure applied.
		 */
		int addSun();

		/**
		 * @brief Gets the unique identifier for the LowSun strategy.
		 * @return Integer ID representing the LowSun strategy.
		 */
		int getID();
};

#endif
