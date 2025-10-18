#ifndef Spring_h
#define Spring_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as spring-season plants.
 *
 * Seasonal decoration that categorizes the plant for spring growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 */
class Spring : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a Spring decorator with spring-specific characteristics.
		 */
		Spring();
};

#endif
