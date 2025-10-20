#ifndef Aggregate_h
#define Aggregate_h

#include <list>
#include "Iterator.h"
#include "../composite/PlantComponent.h"


/**
 * @brief Abstract aggregate interface for creating iterators.
 *
 * Declares the interface for creating iterator objects that traverse
 * plant collections. Concrete aggregates create specific iterator types
 * with appropriate filtering logic.
 *
 * **System Role:**
 * Factory interface for iterator creation. Different aggregates create
 * different iterator types (all plants vs. seasonal). Enables factories
 * to encapsulate iterator creation logic and filtering rules.
 *
 * **Pattern Role:** Abstract Aggregate (iterator factory interface)
 *
 * **Related Patterns:**
 * - Iterator: Creates concrete instances of iterators
 * - Composite: Aggregates operate on plant hierarchies
 * - Facade: Facade may use aggregates for convenient iteration
 *
 * **System Interactions:**
 * - createIterator(plants) creates appropriate iterator type
 * - Concrete aggregates implement filtering-specific iterators
 * - Returns new Iterator configured with filtering logic
 * - Enables polymorphic iterator creation
 *
 * @see Iterator (created by aggregate)
 * @see Concrete aggregates: AggPlant, AggSpring, AggSummer, etc.
 */
class Aggregate
{
	public:
		/**
		 * @brief Creates an iterator for the given plant collection.
		 * @param plants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a new Iterator configured for this aggregate type.
		 */
		virtual Iterator* createIterator(std::list<PlantComponent*>* plants) = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Aggregate() {}
};

#endif
