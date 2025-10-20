#ifndef LargeLeaf_h
#define LargeLeaf_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large leaves to plants.
 *
 * Physical feature decoration that adds large-sized leaves to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 *
 * **System Role:**
 * Leaf feature decoration for lush appearance. Adds prominent foliage. Premium
 * feature option. Stackable with other decorators.
 *
 * **Pattern Role:** Concrete Decorator (leaf feature)
 *
 * @see PlantAttributes (decorator base)
 * @see SmallLeaf (alternative size)
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
