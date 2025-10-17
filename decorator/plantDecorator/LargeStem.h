#ifndef __LargeStem_h__
#define __LargeStem_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large stems to plants.
 *
 * Physical feature decoration that adds large-sized stems to the plant,
 * affecting visual appearance and plant structure.
 */
class LargeStem : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a LargeStem decorator with predefined characteristics.
		 */
		LargeStem();
};

#endif
