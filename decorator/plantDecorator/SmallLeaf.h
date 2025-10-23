#ifndef SmallLeaf_h
#define SmallLeaf_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding small leaves to plants.
 *
 * Physical feature decoration that adds small-sized leaves to the plant,
 * affecting visual appearance and potentially modifying water/sun requirements.
 *
 * **System Role:**
 * Leaf feature decoration for refined appearance. Adds visual detail with
 * delicate leaves. Stackable with flower/stem decorators.
 *
 * **Pattern Role:** Concrete Decorator (leaf feature)
 *
 * @see PlantAttributes (decorator base)
 * @see LargeLeaf (alternative size)
 */
class SmallLeaf : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a SmallLeaf decorator, wrapping the given component.
         * @param component The PlantComponent to decorate.
         */
        SmallLeaf();

        /**
         * @brief Copy constructor for cloning.
         */
        SmallLeaf(const SmallLeaf &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new SmallLeaf decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~SmallLeaf() {}
};

#endif
