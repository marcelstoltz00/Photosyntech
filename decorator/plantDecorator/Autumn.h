#ifndef Autumn_h
#define Autumn_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator marking plants as autumn-season plants.
 *
 * Seasonal decoration that categorizes the plant for autumn/fall growing season.
 * Enables seasonal filtering via Iterator pattern and may affect care requirements.
 *
 * **System Role:**
 * Autumn season categorization. Marks plants as autumn-appropriate. Enables
 * AutumnIterator filtering for seasonal browsing. Works with Iterator pattern
 * for seasonal inventory views.
 *
 * **Pattern Role:** Concrete Decorator (seasonal categorization)
 *
 * @see PlantAttributes (decorator base)
 * @see Spring, Summer, Winter (seasonal variants)
 * @see AutumnIterator (uses Autumn decorator for filtering)
 */
class Autumn : public PlantAttributes
{
	public:
		/**
         * @brief Constructs an Autumn decorator, wrapping the given component.
         * * Calls the base PlantAttributes constructor with specific Autumn
         * decoration details (name, price modifier, and care modifiers).
         * * @param component The PlantComponent to decorate.
         */
        Autumn();

        /**
         * @brief Copy constructor for cloning.
         * * Utilizes the base PlantAttributes copy constructor to deep-copy the
         * underlying component chain.
         * * @param other The Autumn object to copy.
         */
        Autumn(const Autumn &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * * Creates a deep copy of this Autumn decorator and the entire wrapped
         * component chain.
         * * @return Pointer to a new Autumn decorator wrapping a clone of the 
         * underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~Autumn() {}
};

#endif
