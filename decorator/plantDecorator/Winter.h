#ifndef Winter_h
#define Winter_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as winter-season plants.
 *
 * Seasonal decoration that categorizes the plant for winter growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 *
 * **System Role:**
 * Winter season categorization. Marks plants as winter-hardy. Enables WinterIterator
 * filtering for seasonal browsing. Works with Iterator pattern for seasonal
 * inventory views.
 *
 * **Pattern Role:** Concrete Decorator (seasonal categorization)
 *
 * @see PlantAttributes (decorator base)
 * @see Spring, Summer, Autumn (seasonal variants)
 * @see WinterIterator (uses Winter decorator for filtering)
 */
class Winter : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a Winter decorator.
         */
        Winter();

        /**
         * @brief Copy constructor for cloning.
         */
        Winter(const Winter &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new Winter decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~Winter() {}
};

#endif
