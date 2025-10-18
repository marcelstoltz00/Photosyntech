#ifndef Herb_h
#define Herb_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing an Herb plant type.
 *
 * Herbs are small, non-woody plants often used for culinary or medicinal purposes.
 * Typically require moderate to high water and moderate sun exposure.
 * Implements the Prototype pattern to enable cloning of herb instances.
 */
class Herb : public LivingPlant
{
	public:
		/**
		 * @brief Constructs a new Herb with default characteristics.
		 */
		Herb();

		/**
		 * @brief Clones this herb creating a deep copy.
		 * @return Pointer to a new Herb object that is a copy of this one.
		 */
		PlantComponent* clone();
};

#endif
