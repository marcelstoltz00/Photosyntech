#ifndef AggPlant_h
#define AggPlant_h

#include "Aggregate.h"
#include <list>
#include "../composite/PlantComponent.h"

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
		 * @param plants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a PlantIterator for unfiltered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* plants);
};

#endif
