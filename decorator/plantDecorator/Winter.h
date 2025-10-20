#ifndef Winter_h
#define Winter_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as winter-season plants.
 *
 * Seasonal decoration that categorizes the plant for winter growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 *
 * **System Role:**
 * Winter season categorization. Marks plants as winter-hardy. Enables WinterIterator
 * filtering for seasonal browsing. Works with Iterator pattern for seasonal
 * inventory views.
 *
 * **Pattern Role:** Concrete Decorator (seasonal categorization)
 *
 * @see PlantAttributes (decorator base)
 * @see Spring, Summer, Autumn (seasonal variants)
 * @see WinterIterator (uses Winter decorator for filtering)
 */
class Winter : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a Winter decorator with winter-specific characteristics.
		 */
		Winter();
};

#endif
