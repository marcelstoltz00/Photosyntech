#ifndef ShopThemedCharm_h
#define ShopThemedCharm_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a shop-themed charm to plants.
 *
 * Customer-facing decoration that adds a charm with the shop's branding or theme,
 * enhancing visual appeal and potentially offering promotional pricing.
 *
 * **System Role:**
 * Shop-branded charm decoration. Features shop branding for marketing. Premium
 * option with promotional potential. Stacks with other decorations.
 *
 * **Pattern Role:** Concrete Decorator (branded charm decoration)
 *
 * @see PlantAttributes (decorator base)
 * @see PlantCharm (generic charm alternative)
 */
class ShopThemedCharm : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a ShopThemedCharm decorator, wrapping the given component.
         * @param component The PlantComponent to decorate.
         */
        ShopThemedCharm();

        /**
         * @brief Copy constructor for cloning.
         */
        ShopThemedCharm(const ShopThemedCharm &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new ShopThemedCharm decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~ShopThemedCharm() {}
};

#endif
