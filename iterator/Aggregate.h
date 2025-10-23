#ifndef Aggregate_h
#define Aggregate_h

#include <list>
#include "Iterator.h"
#include "../composite/PlantComponent.h"


/**
 * @brief Abstract aggregate interface for creating iterators.
 *
 * Declares the interface for creating iterator objects that traverse
 * plant collections. Concrete aggregates store a collection and create
 * specific iterator types with appropriate filtering logic.
 *
 * **System Role:**
 * Factory interface for iterator creation. Different aggregates create
 * different iterator types (all plants vs. seasonal). Stores the collection
 * and provides access to iterators that traverse it.
 *
 * **Pattern Role:** Abstract Aggregate (iterator factory interface)
 *
 * **Related Patterns:**
 * - Iterator: Creates concrete instances of iterators (declared as friend)
 * - Composite: Aggregates operate on plant hierarchies
 * - Facade: Facade may use aggregates for convenient iteration
 *
 * **System Interactions:**
 * - Stores reference to plant collection
 * - createIterator() creates appropriate iterator type
 * - Concrete aggregates implement filtering-specific iterators
 * - Returns new Iterator configured with filtering logic
 * - Enables polymorphic iterator creation
 *
 * @see Iterator (created by aggregate, has friend access)
 * @see Concrete aggregates: AggPlant, AggSpring, AggSummer, etc.
 */
class Aggregate
{
	friend class Iterator;

	protected:
		/**
		 * @brief Pointer to the plant collection this aggregate manages.
		 */
		std::list<PlantComponent*>* plants;

		/**
		 * @brief Constructor that initializes the aggregate with a plant collection.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 */
		Aggregate(std::list<PlantComponent*>* plants);

	public:
		/**
		 * @brief Creates an iterator for this aggregate's plant collection.
		 * @return Pointer to a new Iterator configured for this aggregate type.
		 */
		virtual Iterator* createIterator() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Aggregate() {}
};

#endif
