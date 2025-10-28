#ifndef LargePot_h
#define LargePot_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a large pot customization to plants.
 *
 * Customer-facing decoration that adds a larger-sized pot to the plant,
 * modifying its visual appearance and increasing price.
 *
 * **System Role:**
 * Premium customer customization option. Upgrades plant presentation and increases
 * final price. Stacks with other decorators (charms, seasonal features) for
 * comprehensive customization. Popular upsell during sales.
 *
 * **Pattern Role:** Concrete Decorator (customer pot customization)
 *
 * **Related Patterns:**
 * - PlantAttributes: Extends decorator base class
 * - Composite: Wraps PlantComponent maintaining interface
 * - Prototype: clone() preserves pot decoration
 * - Builder: Applied after plant construction
 * - Decorator: Stackable with other decorations
 *
 * **System Interactions:**
 * - Increases plant price by pot premium
 * - Adds pot description to plant info
 * - Can be stacked with charms and features
 * - Cloning preserves pot selection
 * - Selected during customization phase
 *
 * @see PlantAttributes (decorator base)
 * @see RedPot (alternative pot decoration)
 */
class LargePot : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a LargePot decorator.
         */
        LargePot();

        /**
         * @brief Copy constructor for cloning.
         */
        LargePot(const LargePot &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new LargePot decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~LargePot() {}
};

#endif
