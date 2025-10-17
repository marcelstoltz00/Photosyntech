#ifndef __SmallStem_h__
#define __SmallStem_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small stems to plants.
 *
 * Physical feature decoration that adds small-sized stems to the plant,
 * affecting visual appearance and plant structure.
 */
class SmallStem : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a SmallStem decorator with predefined characteristics.
		 */
		SmallStem();
};

#endif
