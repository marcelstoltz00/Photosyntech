#ifndef Spring_h
#define Spring_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as spring-season plants.
 *
 * Seasonal decoration that categorizes the plant for spring growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 *
 * **System Role:**
 * Seasonal categorization mechanism. Marks plants as spring-season appropriate.
 * Enables SpringIterator filtering for seasonal browsing. Works with Iterator
 * pattern to provide season-specific inventory views. Part of seasonal decorator set.
 *
 * **Pattern Role:** Concrete Decorator (seasonal categorization)
 *
 * **Related Patterns:**
 * - PlantAttributes: Extends decorator base
 * - Composite: Wraps PlantComponent preserving interface
 * - Iterator: Enables SpringIterator filtering
 * - Prototype: clone() preserves season marking
 * - Decorator: Stackable with pot/charm decorators
 *
 * **System Interactions:**
 * - Marks plant with spring season classification
 * - Enables identification by SpringIterator
 * - May modify care requirements for spring
 * - Stacks with customer decorations
 * - Cloning preserves seasonal marking
 * - Used during seasonal inventory management
 *
 * @see PlantAttributes (decorator base)
 * @see Summer, Autumn, Winter (seasonal variants)
 * @see SpringIterator (uses Spring decorator for filtering)
 */
class Spring : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a Spring decorator.
         */
        Spring();

        /**
         * @brief Copy constructor for cloning.
         */
        Spring(const Spring &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new Spring decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~Spring() {}
};

#endif
