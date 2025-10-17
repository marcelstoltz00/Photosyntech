#ifndef __RedPot_h__
#define __RedPot_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a red pot customization to plants.
 *
 * Customer-facing decoration that adds a red colored pot to the plant,
 * modifying its visual appearance and potentially affecting price.
 */
class RedPot : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a RedPot decorator with predefined characteristics.
		 */
		RedPot();
};

#endif
