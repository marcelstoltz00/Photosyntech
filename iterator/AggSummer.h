#ifndef __AggSummer_h__
#define __AggSummer_h__

#include "Aggregate.h"

/**
 * @brief Concrete aggregate for creating summer plant iterators.
 *
 * Creates SummerIterator instances that filter and return only summer-season plants.
 */
class AggSummer : public Aggregate
{
	public:
		/**
		 * @brief Creates a summer-filtered iterator for the given plant collection.
		 * @param aPlants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a SummerIterator for season-filtered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* aPlants);
};

#endif
