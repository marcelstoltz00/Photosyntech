#ifndef __PlantCharm_h__
#define __PlantCharm_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a decorative charm to plants.
 *
 * Customer-facing decoration that adds a charm or ornament to the plant,
 * enhancing its visual appeal and affecting price.
 */
class PlantCharm : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a PlantCharm decorator with predefined characteristics.
		 */
		PlantCharm();
};

#endif
