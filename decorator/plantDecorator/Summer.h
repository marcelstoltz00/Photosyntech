#ifndef Summer_h
#define Summer_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as summer-season plants.
 *
 * Seasonal decoration that categorizes the plant for summer growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 *
 * **System Role:**
 * Summer season categorization. Marks plants as summer-appropriate. Enables
 * SummerIterator filtering for seasonal browsing. Works with Iterator pattern
 * for seasonal inventory views.
 *
 * **Pattern Role:** Concrete Decorator (seasonal categorization)
 *
 * @see PlantAttributes (decorator base)
 * @see Spring, Autumn, Winter (seasonal variants)
 * @see SummerIterator (uses Summer decorator for filtering)
 */
class Summer : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a Summer decorator, wrapping the given component.
         * @param component The PlantComponent to decorate.
         */
        Summer(PlantComponent* component);

        /**
         * @brief Copy constructor for cloning.
         */
        Summer(const Summer &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new Summer decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~Summer() {}
};

#endif
