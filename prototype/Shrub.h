#ifndef Shrub_h
#define Shrub_h

#include "LivingPlant.h"

/**
 * @brief Concrete prototype representing a Shrub plant type.
 *
 * Shrubs are woody plants smaller than trees, typically with multiple stems.
 * Require moderate water and sun exposure strategies.
 * Implements the Prototype pattern to enable cloning of shrub instances.
 *
 * **System Role:**
 * Concrete plant type (one of four base types). Encapsulates shrub-specific
 * characteristics and default strategies. Created by Builder pattern,
 * cloned for inventory multiplication, wrapped with decorators for customization.
 *
 * **Pattern Role:** Concrete Prototype (implements cloning for shrub species)
 *
 * **Related Patterns:**
 * - LivingPlant: Extends base plant class for shared behavior
 * - Builder: SunflowerBuilder can create shrubs (Builder pattern)
 * - Composite: Leaf in plant hierarchy
 * - Prototype: clone() creates shrub copies
 * - PlantComponent: Implements composite interface
 *
 * **System Interactions:**
 * - Constructor initializes shrub-specific defaults
 * - clone() creates new Shrub copy preserving all characteristics
 * - Cloned shrubs added to inventory for distribution
 * - Can be decorated with pots, charms, seasonal features
 * - Subject to lifecycle state changes via StatePattern
 *
 * @see LivingPlant (base class)
 * @see Builder (plant creation)
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
