#ifndef SmallLeaf_h
#define SmallLeaf_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small leaves to plants.
 *
 * Physical feature decoration that adds small-sized leaves to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 *
 * **System Role:**
 * Leaf feature decoration for refined appearance. Adds visual detail with
 * delicate leaves. Stackable with flower/stem decorators.
 *
 * **Pattern Role:** Concrete Decorator (leaf feature)
 *
 * @see PlantAttributes (decorator base)
 * @see LargeLeaf (alternative size)
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
