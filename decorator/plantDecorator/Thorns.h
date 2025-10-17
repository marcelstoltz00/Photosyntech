#ifndef __Thorns_h__
#define __Thorns_h__

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding thorns to plants.
 *
 * Physical feature decoration that adds thorns or spikes to the plant,
 * affecting visual appearance and handling characteristics.
 */
class Thorns : public PlantAttributes
{
	public:
		/**
		 * @brief Constructs a Thorns decorator with predefined characteristics.
		 */
		Thorns();
};

#endif
