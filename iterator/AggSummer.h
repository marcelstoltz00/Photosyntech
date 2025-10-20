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
 * Stores the plant collection and provides access to SummerIterator through friend relationship.
 *
 * **System Role:**
 * Factory for summer-season inventory iteration. Produces SummerIterator for browsing
 * plants suitable for summer growing. Part of seasonal iterator family.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * @see Aggregate (abstract factory)
 * @see SummerIterator (concrete iterator created, has friend access)
 */
class AggSummer : public Aggregate
{
	friend class SummerIterator;

	public:
		/**
		 * @brief Constructor that initializes the aggregate with a plant collection.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 */
		AggSummer(std::list<PlantComponent*>* plants);

		/**
		 * @brief Creates a summer-filtered iterator for this aggregate's plant collection.
		 * @return Pointer to a SummerIterator for season-filtered traversal.
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggSummer() {}
};

#endif
