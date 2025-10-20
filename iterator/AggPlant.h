#ifndef AggPlant_h
#define AggPlant_h

#include "Aggregate.h"
#include "PlantIterator.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating unfiltered plant iterators.
 *
 * Creates PlantIterator instances that traverse all plants without filtering.
 *
 * **System Role:**
 * Factory for complete inventory iteration. Produces PlantIterator for browsing
 * entire inventory without filtering. Simple, unfiltered access for when users
 * want to see all available plants in the system.
 *
 * **Pattern Role:** Concrete Aggregate (iterator factory for all plants)
 *
 * **Related Patterns:**
 * - Aggregate: Implements abstract iterator factory
 * - Iterator: Creates PlantIterator instances
 * - Composite: Collection operates on PlantComponent hierarchy
 * - Facade: May use for default inventory browsing
 *
 * **System Interactions:**
 * - createIterator(plants) creates PlantIterator for complete traversal
 * - Returns iterator configured for unfiltered collection access
 * - Used by browse commands without seasonal/category filters
 * - Foundation for other specialized aggregate types
 *
 * @see Aggregate (abstract factory interface)
 * @see PlantIterator (concrete iterator created)
 */
class AggPlant : public Aggregate
{
	public:
		/**
		 * @brief Creates an unfiltered iterator for the given plant collection.
		 * @param plants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a PlantIterator for unfiltered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* plants);
};

#endif
