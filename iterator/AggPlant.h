#ifndef __AggPlant_h__
#define __AggPlant_h__

#include "Aggregate.h"

/**
 * @brief Concrete aggregate for creating unfiltered plant iterators.
 *
 * Creates PlantIterator instances that traverse all plants without filtering.
 */
class AggPlant : public Aggregate
{
	public:
		/**
		 * @brief Creates an unfiltered iterator for the given plant collection.
		 * @param aPlants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a PlantIterator for unfiltered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* aPlants);
};

#endif
