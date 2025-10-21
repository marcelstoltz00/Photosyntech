#ifndef LargeStem_h
#define LargeStem_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding large stems to plants.
 *
 * Physical feature decoration that adds large-sized stems to the plant,
 * affecting visual appearance and plant structure.
 *
 * **System Role:**
 * Stem feature decoration for robust structure. Adds strong plant framework with
 * thick stems. Premium structural option.
 *
 * **Pattern Role:** Concrete Decorator (stem feature)
 *
 * @see PlantAttributes (decorator base)
 * @see SmallStem (alternative size)
 */
class LargeStem : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a LargeStem decorator, wrapping the given component.
         * @param component The PlantComponent to decorate.
         */
        LargeStem(PlantComponent* component);

        /**
         * @brief Copy constructor for cloning.
         */
        LargeStem(const LargeStem &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new LargeStem decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~LargeStem() {}
};

#endif
