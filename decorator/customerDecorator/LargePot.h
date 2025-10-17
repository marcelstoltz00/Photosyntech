#ifndef __LargePot_h__
#define __LargePot_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a large pot customization to plants.
 *
 * Customer-facing decoration that adds a larger-sized pot to the plant,
 * modifying its visual appearance and increasing price.
 */
class LargePot : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a LargePot decorator with predefined characteristics.
		 */
		LargePot();
};

#endif
