#ifndef PlantCharm_h
#define PlantCharm_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding a decorative charm to plants.
 *
 * Customer-facing decoration that adds a charm or ornament to the plant,
 * enhancing its visual appeal and affecting price.
 *
 * **System Role:**
 * Customer charm decoration option. Stacks with pots and other features for
 * complete customization. Increases plant appeal and price.
 *
 * **Pattern Role:** Concrete Decorator (charm decoration)
 *
 * @see PlantAttributes (decorator base)
 * @see ShopThemedCharm (alternative charm)
 */
class PlantCharm : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a PlantCharm decorator, wrapping the given component.
         * @param component The PlantComponent to decorate.
         */
        PlantCharm(PlantComponent* component);

        /**
         * @brief Copy constructor for cloning.
         */
        PlantCharm(const PlantCharm &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new PlantCharm decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~PlantCharm() {}
};

#endif
