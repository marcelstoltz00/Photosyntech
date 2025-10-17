#ifndef __MidSun_h__
#define __MidSun_h__

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
		 * @return Integer representing the medium sun exposure applied.
		 */
		int addSun();

		/**
		 * @brief Gets the unique identifier for the MidSun strategy.
		 * @return Integer ID representing the MidSun strategy.
		 */
		int getID();
};

#endif
