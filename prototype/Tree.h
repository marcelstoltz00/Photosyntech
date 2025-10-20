#ifndef Tree_h
#define Tree_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing a Tree plant type.
 *
 * Trees are large woody plants with a single main stem (trunk) and branches.
 * Typically require high water and sun exposure strategies due to their size.
 * Implements the Prototype pattern to enable cloning of tree instances.
 *
 * **System Role:**
 * Concrete plant type (one of four base types). Encapsulates tree-specific
 * characteristics with high-care requirements. Created by Builder, cloned
 * for inventory, customizable through decorators. Premium plant category.
 *
 * **Pattern Role:** Concrete Prototype (implements cloning for tree species)
 *
 * **Related Patterns:**
 * - LivingPlant: Extends base plant class
 * - Builder: Creates trees with high water/sun strategies
 * - Composite: Leaf in plant hierarchy
 * - Prototype: clone() creates tree copies
 * - PlantComponent: Implements composite interface
 *
 * **System Interactions:**
 * - Constructor initializes tree-specific defaults (high care needs)
 * - clone() creates new Tree copy preserving characteristics
 * - Cloned trees added to inventory for distribution
 * - Can be decorated with large pots, premium charms
 * - Subject to lifecycle with typically longer growth periods
 *
 * @see LivingPlant (base class)
 * @see Builder (plant creation)
 */
class Tree : public LivingPlant
{
	public:
		/**
		 * @brief Constructs a new Tree with default characteristics.
		 */
		Tree();

		/**
		 * @brief Constructs a copy of an existing tree.
		 *
		 * Performs a member-wise shallow copy for flyweights.
		 * and a deep copy for the decorator chain.
		 *
		 * @param other The tree object to copy.
		 */
		Tree(const Tree& other);

		/**
		 * @brief Clones this tree creating a deep copy.
		 * @return Pointer to a new Tree object that is a copy of this one.
		 */
		PlantComponent* clone();
};

#endif
