#ifndef AggSpring_h
#define AggSpring_h

#include "Aggregate.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating spring plant iterators.
 *
 * Creates SpringIterator instances that filter and return only spring-season plants.
 */
class AggSpring : public Aggregate
{
	public:
		/**
		 * @brief Creates a spring-filtered iterator for the given plant collection.
		 * @param plants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a SpringIterator for season-filtered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* plants);
};

#endif
