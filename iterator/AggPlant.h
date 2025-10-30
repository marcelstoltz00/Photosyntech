#ifndef AggPlant_h
#define AggPlant_h

#include "Aggregate.h"
#include "PlantIterator.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating unfiltered bidirectional plant iterators.
 *
 * Creates PlantIterator instances that traverse all plants without filtering,
 * supporting both forward and backward navigation. Stores the plant collection
 * and provides access to PlantIterator through friend relationship.
 *
 * **System Role:**
 * Factory for complete inventory iteration. Produces bidirectional PlantIterator
 * for browsing entire inventory without filtering. Simple, unfiltered access for
 * when users want to see all available plants in the system with full navigation
 * control.
 *
 * **Pattern Role:** Concrete Aggregate (bidirectional iterator factory for all plants)
 *
 * **Related Patterns:**
 * - Aggregate: Implements abstract bidirectional iterator factory
 * - Iterator: Creates bidirectional PlantIterator instances (declared as friend)
 * - Composite: Collection operates on PlantComponent hierarchy
 * - Facade: May use for default inventory browsing
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection
 * - createIterator() creates bidirectional PlantIterator for complete traversal
 * - Returns iterator configured for unfiltered collection access with next()/back()
 * - Used by browse commands without seasonal/category filters
 * - Foundation for other specialized aggregate types
 *
 * @see Aggregate (abstract factory interface)
 * @see PlantIterator (concrete bidirectional iterator created, has friend access)
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
		 * @brief Creates an unfiltered bidirectional iterator for this aggregate's plant collection.
		 * @return Pointer to a PlantIterator for unfiltered bidirectional traversal (supports next() and back()).
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggPlant() {}
};

#endif
