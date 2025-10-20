#ifndef SmallFlowers_h
#define SmallFlowers_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small flowers to plants.
 *
 * Physical feature decoration that adds small-sized flowers to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 *
 * **System Role:**
 * Plant feature decoration for delicate flowering. Adds visual appeal with
 * modest flower sizes. Modifies care requirements. Stackable with sizes.
 *
 * **Pattern Role:** Concrete Decorator (flower feature)
 *
 * @see PlantAttributes (decorator base)
 * @see LargeFlowers (alternative size)
 */
class SmallFlowers : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a SmallFlowers decorator with predefined characteristics.
		 */
		SmallFlowers();
};

#endif
