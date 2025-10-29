#ifndef RedPot_h
#define RedPot_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a red pot customization to plants.
 *
 * Customer-facing decoration that adds a red colored pot to the plant,
 * modifying its visual appearance and potentially affecting price.
 *
 * **System Role:**
 * Customer pot choice offering. Provides red pot styling option. Stacks with
 * other decorators for complete customization. Increases plant price and appeal.
 *
 * **Pattern Role:** Concrete Decorator (customer pot styling)
 *
 * @see PlantAttributes (decorator base)
 * @see LargePot (alternative pot decoration)
 */
class RedPot : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a RedPot decorator.
         */
        RedPot();

        /**
         * @brief Copy constructor for cloning.
         */
        RedPot(const RedPot &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new RedPot decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~RedPot() {}
};

#endif
