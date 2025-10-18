#ifndef Summer_h
#define Summer_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as summer-season plants.
 *
 * Seasonal decoration that categorizes the plant for summer growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 */
class Summer : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a Summer decorator with summer-specific characteristics.
		 */
		Summer();
};

#endif
