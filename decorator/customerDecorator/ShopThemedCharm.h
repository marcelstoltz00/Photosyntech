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
		 * @brief Constructs a ShopThemedCharm decorator with predefined characteristics.
		 */
		ShopThemedCharm();
};

#endif
