#ifndef __Aggregate_h__
#define __Aggregate_h__

#include <list>

class Iterator;
class PlantComponent;

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
		 * @param aPlants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a new Iterator configured for this aggregate type.
		 */
		virtual Iterator* createIterator(std::list<PlantComponent*>* aPlants) = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Aggregate() {}
};

#endif
