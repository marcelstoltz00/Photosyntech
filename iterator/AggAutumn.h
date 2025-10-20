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
 * Stores the plant collection and provides access to AutumnIterator through friend relationship.
 *
 * **System Role:**
 * Factory for autumn-season inventory iteration. Produces AutumnIterator for browsing
 * plants suitable for autumn growing. Part of seasonal iterator family.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * @see Aggregate (abstract factory)
 * @see AutumnIterator (concrete iterator created, has friend access)
 */
class AggAutumn : public Aggregate
{
	friend class AutumnIterator;

	public:
		/**
		 * @brief Constructor that initializes the aggregate with a plant collection.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 */
		AggAutumn(std::list<PlantComponent*>* plants);

		/**
		 * @brief Creates an autumn-filtered iterator for this aggregate's plant collection.
		 * @return Pointer to an AutumnIterator for season-filtered traversal.
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggAutumn() {}
};

#endif
