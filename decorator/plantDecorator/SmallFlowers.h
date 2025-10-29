#ifndef SmallFlowers_h
#define SmallFlowers_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small flowers to plants.
 *
 * Physical feature decoration that adds small-sized flowers to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 *
 * **System Role:**
 * Plant feature decoration for delicate flowering. Adds visual appeal with
 * modest flower sizes. Modifies care requirements. Stackable with sizes.
 *
 * **Pattern Role:** Concrete Decorator (flower feature)
 *
 * @see PlantAttributes (decorator base)
 * @see LargeFlowers (alternative size)
 */
class SmallFlowers : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a SmallFlowers decorator.
         */
        SmallFlowers();

        /**
         * @brief Copy constructor for cloning.
         */
        SmallFlowers(const SmallFlowers &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new SmallFlowers decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~SmallFlowers() {}
};

#endif
