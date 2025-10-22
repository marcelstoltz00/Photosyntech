#ifndef LargeLeaf_h
#define LargeLeaf_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large leaves to plants.
 *
 * Physical feature decoration that adds large-sized leaves to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 *
 * **System Role:**
 * Leaf feature decoration for lush appearance. Adds prominent foliage. Premium
 * feature option. Stackable with other decorators.
 *
 * **Pattern Role:** Concrete Decorator (leaf feature)
 *
 * @see PlantAttributes (decorator base)
 * @see SmallLeaf (alternative size)
 */
class LargeLeaf : public PlantAttributes
{
public:
        /**
         * @brief Constructs a LargeLeaf decorator, wrapping the given component.
         * @param component The PlantComponent to decorate.
         */
        LargeLeaf();

        /**
         * @brief Copy constructor for cloning.
         */
        LargeLeaf(const LargeLeaf &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new LargeLeaf decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~LargeLeaf() {}
};

#endif
