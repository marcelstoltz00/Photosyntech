#ifndef Shrub_h
#define Shrub_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing a Shrub plant type.
 *
 * Shrubs are woody plants smaller than trees, typically with multiple stems.
 * Require moderate water and sun exposure strategies.
 * Implements the Prototype pattern to enable cloning of shrub instances.
 */
class Shrub : public LivingPlant
{
	public:
		/**
		 * @brief Constructs a new Shrub with default characteristics.
		 */
		Shrub();

		/**
		 * @brief Clones this shrub creating a deep copy.
		 * @return Pointer to a new Shrub object that is a copy of this one.
		 */
		PlantComponent* clone();
};

#endif
