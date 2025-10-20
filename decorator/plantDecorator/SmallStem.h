#ifndef SmallStem_h
#define SmallStem_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small stems to plants.
 *
 * Physical feature decoration that adds small-sized stems to the plant,
 * affecting visual appearance and plant structure.
 *
 * **System Role:**
 * Stem feature decoration for delicate structure. Adds visual finesse with
 * thin stems. Stackable with other plant features.
 *
 * **Pattern Role:** Concrete Decorator (stem feature)
 *
 * @see PlantAttributes (decorator base)
 * @see LargeStem (alternative size)
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
