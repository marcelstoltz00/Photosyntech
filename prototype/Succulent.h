#ifndef Succulent_h
#define Succulent_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing a Succulent plant type.
 *
 * Succulents are drought-tolerant plants with thick, fleshy parts adapted to store water.
 * Typically require low water strategies and can tolerate varying sun conditions.
 * Implements the Prototype pattern to enable cloning of succulent instances.
 */
class Succulent : public LivingPlant
{
	public:
		/**
		 * @brief Constructs a new Succulent with default characteristics.
		 */
		Succulent();

		/**
		 * @brief Constructs a copy of an existing succulent.
		 *
		 * Performs a member-wise shallow copy for flyweights.
		 * and a deep copy for the decorator chain.
		 *
		 * @param other The succulent object to copy.
		 */
		Succulent(const Succulent& other);

		/**
		 * @brief Clones this succulent creating a deep copy.
		 * @return Pointer to a new Succulent object that is a copy of this one.
		 */
		PlantComponent* clone();
};

#endif
