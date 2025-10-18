#ifndef LargeLeaf_h
#define LargeLeaf_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large leaves to plants.
 *
 * Physical feature decoration that adds large-sized leaves to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 */
class LargeLeaf : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a LargeLeaf decorator with predefined characteristics.
		 */
		LargeLeaf();
};

#endif
