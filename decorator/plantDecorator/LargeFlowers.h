#ifndef LargeFlowers_h
#define LargeFlowers_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large flowers to plants.
 *
 * Physical feature decoration that adds large-sized flowers to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 *
 * **System Role:**
 * Plant feature decoration for bold flowering. Adds dramatic visual appeal with
 * prominent flowers. Increases care requirements. Premium feature option.
 *
 * **Pattern Role:** Concrete Decorator (flower feature)
 *
 * @see PlantAttributes (decorator base)
 * @see SmallFlowers (alternative size)
 */
class LargeFlowers : public PlantAttributes
{
public:
        /**
         * @brief Constructs a LargeFlowers decorator, wrapping the given component.
         * @param component The PlantComponent to decorate.
         */
        LargeFlowers(PlantComponent* component);

        /**
         * @brief Copy constructor for cloning.
         */
        LargeFlowers(const LargeFlowers &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new LargeFlowers decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~LargeFlowers() {}
};

#endif
