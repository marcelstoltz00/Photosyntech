#ifndef __Winter_h__
#define __Winter_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as winter-season plants.
 *
 * Seasonal decoration that categorizes the plant for winter growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 */
class Winter : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a Winter decorator with winter-specific characteristics.
		 */
		Winter();
};

#endif
