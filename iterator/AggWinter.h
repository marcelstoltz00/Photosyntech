#ifndef AggWinter_h
#define AggWinter_h

#include "Aggregate.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating winter plant iterators.
 *
 * Creates WinterIterator instances that filter and return only winter-season plants.
 */
class AggWinter : public Aggregate
{
	public:
		/**
		 * @brief Creates a winter-filtered iterator for the given plant collection.
		 * @param plants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a WinterIterator for season-filtered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* plants);
};

#endif
