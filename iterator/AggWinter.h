#ifndef AggWinter_h
#define AggWinter_h

#include "Aggregate.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating winter plant iterators.
 *
 * Creates WinterIterator instances that filter and return only winter-season plants.
 *
 * **System Role:**
 * Factory for winter-season inventory iteration. Produces WinterIterator for browsing
 * plants suitable for winter growing. Part of seasonal iterator family.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * @see Aggregate (abstract factory)
 * @see WinterIterator (concrete iterator created)
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
