#ifndef AggSummer_h
#define AggSummer_h

#include "Aggregate.h"
#include "SummerIterator.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating summer plant iterators.
 *
 * Creates SummerIterator instances that filter and return only summer-season plants.
 *
 * **System Role:**
 * Factory for summer-season inventory iteration. Produces SummerIterator for browsing
 * plants suitable for summer growing. Part of seasonal iterator family.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * @see Aggregate (abstract factory)
 * @see SummerIterator (concrete iterator created)
 */
class AggSummer : public Aggregate
{
	public:
		/**
		 * @brief Creates a summer-filtered iterator for the given plant collection.
		 * @param plants Pointer to the list of PlantComponents to iterate over.
		 * @return Pointer to a SummerIterator for season-filtered traversal.
		 */
		Iterator* createIterator(std::list<PlantComponent*>* plants);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggSummer() {}
};

#endif
