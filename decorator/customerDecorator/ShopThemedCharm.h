#ifndef ShopThemedCharm_h
#define ShopThemedCharm_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a shop-themed charm to plants.
 *
 * Customer-facing decoration that adds a charm with the shop's branding or theme,
 * enhancing visual appeal and potentially offering promotional pricing.
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
