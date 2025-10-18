#ifndef LargeFlowers_h
#define LargeFlowers_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large flowers to plants.
 *
 * Physical feature decoration that adds large-sized flowers to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 */
class LargeFlowers : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a LargeFlowers decorator with predefined characteristics.
		 */
		LargeFlowers();
};

#endif
