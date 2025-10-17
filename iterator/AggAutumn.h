#ifndef __AggAutumn_h__
#define __AggAutumn_h__

#include "Aggregate.h"

/**
 * @brief Concrete aggregate for creating autumn plant iterators.
 *
 * Creates AutumnIterator instances that filter and return only autumn-season plants.
 */
class AggAutumn : public Aggregate
{
	public:
		/**
		 * @brief Creates an autumn-filtered iterator for the given plant collection.
		 * @param aPlants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to an AutumnIterator for season-filtered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* aPlants);
};

#endif
