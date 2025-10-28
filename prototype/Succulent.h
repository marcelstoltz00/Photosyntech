#ifndef Succulent_h
#define Succulent_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing a Succulent plant type.
 *
 * Succulents are drought-tolerant plants with thick, fleshy parts adapted to store water.
 * Typically require low water strategies and can tolerate varying sun conditions.
 * Implements the Prototype pattern to enable cloning of succulent instances.
 *
 * **System Role:**
 * Concrete plant type (one of four base types). Encapsulates succulent-specific
 * characteristics and default strategies. Created by Builder pattern,
 * cloned for inventory multiplication, wrapped with decorators for customization.
 *
 * **Pattern Role:** Concrete Prototype (implements cloning for succulent species)
 *
 * **Related Patterns:**
 * - LivingPlant: Extends base plant class for shared behavior
 * - Builder: CactusBuilder can create succulents (Builder pattern)
 * - Composite: Leaf in plant hierarchy
 * - Prototype: clone() creates succulent copies
 * - PlantComponent: Implements composite interface
 *
 * **System Interactions:**
 * - Constructor initializes succulent-specific defaults
 * - clone() creates new Succulent copy preserving all characteristics
 * - Cloned succulents added to inventory for distribution
 * - Can be decorated with pots, charms, seasonal features
 * - Subject to lifecycle state changes via StatePattern
 *
 * @see LivingPlant (base class)
 * @see Builder (plant creation)
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


			Succulent(std::string);
		/**
		 * @brief Clones this succulent creating a deep copy.
		 * @return Pointer to a new Succulent object that is a copy of this one.
		 */
		PlantComponent* clone();
};

#endif
