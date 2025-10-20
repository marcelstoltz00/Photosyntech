#ifndef Autumn_h
#define Autumn_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as autumn-season plants.
 *
 * Seasonal decoration that categorizes the plant for autumn/fall growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 *
 * **System Role:**
 * Autumn season categorization. Marks plants as autumn-appropriate. Enables
 * AutumnIterator filtering for seasonal browsing. Works with Iterator pattern
 * for seasonal inventory views.
 *
 * **Pattern Role:** Concrete Decorator (seasonal categorization)
 *
 * @see PlantAttributes (decorator base)
 * @see Spring, Summer, Winter (seasonal variants)
 * @see AutumnIterator (uses Autumn decorator for filtering)
 */
class Autumn : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs an Autumn decorator with autumn-specific characteristics.
		 */
		Autumn();
};

#endif
