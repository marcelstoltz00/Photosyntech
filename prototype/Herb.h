#ifndef Herb_h
#define Herb_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing an Herb plant type.
 *
 * Herbs are small, non-woody plants often used for culinary or medicinal purposes.
 * Typically require moderate to high water and moderate sun exposure.
 * Implements the Prototype pattern to enable cloning of herb instances.
 *
 * **System Role:**
 * Concrete plant type (one of four base types). Encapsulates herb-specific
 * characteristics with moderate care requirements. Created by Builder,
 * cloned for inventory, popular for decoration and kitchen use.
 *
 * **Pattern Role:** Concrete Prototype (implements cloning for herb species)
 *
 * **Related Patterns:**
 * - LivingPlant: Extends base plant class
 * - Builder: Creates herbs with moderate care strategies
 * - Composite: Leaf in plant hierarchy
 * - Prototype: clone() creates herb copies
 * - PlantComponent: Implements composite interface
 *
 * **System Interactions:**
 * - Constructor initializes herb-specific defaults (moderate care)
 * - clone() creates new Herb copy preserving characteristics
 * - Cloned herbs added to inventory for distribution
 * - Can be decorated with small pots, kitchen-themed charms
 * - Popular base for kitchen garden collections
 *
 * @see LivingPlant (base class)
 * @see Builder (plant creation)
 */
class Herb : public LivingPlant
{
	public:
		/**
		 * @brief Constructs a new Herb with default characteristics.
		 */
		Herb();

		/**
		 * @brief Constructs a copy of an existing herb.
		 *
		 * Performs a member-wise shallow copy for flyweights.
		 * and a deep copy for the decorator chain.
		 *
		 * @param other The herb object to copy.
		 */
		Herb(const Herb& other);

		/**
		 * @brief Clones this herb creating a deep copy.
		 * @return Pointer to a new Herb object that is a copy of this one.
		 */
		PlantComponent* clone();
};

#endif
