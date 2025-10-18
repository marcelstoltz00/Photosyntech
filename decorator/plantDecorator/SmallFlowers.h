#ifndef SmallFlowers_h
#define SmallFlowers_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small flowers to plants.
 *
 * Physical feature decoration that adds small-sized flowers to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
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
