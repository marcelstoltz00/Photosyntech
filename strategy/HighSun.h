#ifndef HighSun_h
#define HighSun_h

#include "SunStrategy.h"

/**
 * @brief Concrete strategy for high-intensity, full sunlight exposure.
 *
 * Implements a sun exposure strategy with high intensity and long durations,
 * suitable for sun-loving plants that thrive in direct, bright sunlight.
 */
class HighSun : public SunStrategy
{
	public:
		/**
		 * @brief Applies high-level sunlight exposure to the plant.
		 * @return Integer representing the abundant sun exposure applied.
		 */
		int addSun();

		/**
		 * @brief Gets the unique identifier for the HighSun strategy.
		 * @return Integer ID representing the HighSun strategy.
		 */
		int getID();
};

#endif
