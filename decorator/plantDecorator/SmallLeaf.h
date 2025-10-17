#ifndef __SmallLeaf_h__
#define __SmallLeaf_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small leaves to plants.
 *
 * Physical feature decoration that adds small-sized leaves to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 */
class SmallLeaf : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a SmallLeaf decorator with predefined characteristics.
		 */
		SmallLeaf();
};

#endif
