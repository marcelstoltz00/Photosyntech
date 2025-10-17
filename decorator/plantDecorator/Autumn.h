#ifndef __Autumn_h__
#define __Autumn_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as autumn-season plants.
 *
 * Seasonal decoration that categorizes the plant for autumn/fall growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 */
class Autumn : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs an Autumn decorator with autumn-specific characteristics.
		 */
		Autumn();
};

#endif
