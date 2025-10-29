#ifndef Thorns_h
#define Thorns_h

#include "../PlantAttributes.h"

/**
 * @brief Concrete decorator adding thorns to plants.
 *
 * Physical feature decoration that adds thorns or spikes to the plant,
 * affecting visual appearance and handling characteristics.
 *
 * **System Role:**
 * Specialty feature decoration for certain plant types. Adds defensive spikes.
 * Affects handling and care characteristics. Premium feature.
 *
 * **Pattern Role:** Concrete Decorator (specialty feature)
 *
 * @see PlantAttributes (decorator base)
 */
class Thorns : public PlantAttributes
{
	public:
        /**
         * @brief Constructs a Thorns decorator.
         */
        Thorns();

        /**
         * @brief Copy constructor for cloning.
         */
        Thorns(const Thorns &other);

        /**
         * @brief Clones the decorated plant component (Prototype pattern).
         * @return Pointer to a new Thorns decorator wrapping a clone of the underlying component.
         */
        PlantComponent* clone();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~Thorns() {}
};

#endif
