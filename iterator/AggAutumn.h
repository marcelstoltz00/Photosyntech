#ifndef AggAutumn_h
#define AggAutumn_h

#include "Aggregate.h"
#include "AutumnIterator.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating autumn plant iterators.
 *
 * Creates AutumnIterator instances that filter and return only autumn-season plants.
 *
 * **System Role:**
 * Factory for autumn-season inventory iteration. Produces AutumnIterator for browsing
 * plants suitable for autumn growing. Part of seasonal iterator family.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * @see Aggregate (abstract factory)
 * @see AutumnIterator (concrete iterator created)
 */
class AggAutumn : public Aggregate
{
	public:
		/**
		 * @brief Creates an autumn-filtered iterator for the given plant collection.
		 * @param plants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to an AutumnIterator for season-filtered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* plants);
};

#endif
