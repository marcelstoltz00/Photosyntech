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
