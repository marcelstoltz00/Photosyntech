#ifndef Tree_h
#define Tree_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing a Tree plant type.
 *
 * Trees are large woody plants with a single main stem (trunk) and branches.
 * Typically require high water and sun exposure strategies due to their size.
 * Implements the Prototype pattern to enable cloning of tree instances.
 */
class Tree : public LivingPlant
{
	public:
		/**
		 * @brief Constructs a new Tree with default characteristics.
		 */
		Tree();

		/**
		 * @brief Clones this tree creating a deep copy.
		 * @return Pointer to a new Tree object that is a copy of this one.
		 */
		PlantComponent* clone();
};

#endif
