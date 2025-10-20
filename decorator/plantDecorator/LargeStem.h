#ifndef LargeStem_h
#define LargeStem_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large stems to plants.
 *
 * Physical feature decoration that adds large-sized stems to the plant,
 * affecting visual appearance and plant structure.
 *
 * **System Role:**
 * Stem feature decoration for robust structure. Adds strong plant framework with
 * thick stems. Premium structural option.
 *
 * **Pattern Role:** Concrete Decorator (stem feature)
 *
 * @see PlantAttributes (decorator base)
 * @see SmallStem (alternative size)
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
