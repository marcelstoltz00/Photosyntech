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
 * Stores the plant collection and provides access to PlantIterator through friend relationship.
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
 * - Iterator: Creates PlantIterator instances (declared as friend)
 * - Composite: Collection operates on PlantComponent hierarchy
 * - Facade: May use for default inventory browsing
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection
 * - createIterator() creates PlantIterator for complete traversal
 * - Returns iterator configured for unfiltered collection access
 * - Used by browse commands without seasonal/category filters
 * - Foundation for other specialized aggregate types
 *
 * @see Aggregate (abstract factory interface)
 * @see PlantIterator (concrete iterator created, has friend access)
 */
class AggPlant : public Aggregate
{
	friend class PlantIterator;

	public:
		/**
		 * @brief Constructor that initializes the aggregate with a plant collection.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 */
		AggPlant(std::list<PlantComponent*>* plants);

		/**
		 * @brief Creates an unfiltered iterator for this aggregate's plant collection.
		 * @return Pointer to a PlantIterator for unfiltered traversal.
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggPlant() {}
};

#endif
