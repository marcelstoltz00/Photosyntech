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
 * plants suitable for autumn growing. Enables seasonal browsing and category-specific
 * customer shopping experiences.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * **Related Patterns:**
 * - Aggregate: Implements iterator factory interface
 * - Iterator: Creates AutumnIterator instances (declared as friend)
 * - Decorator: Works with Autumn decorator for filtering
 * - Facade: Enables seasonal browsing through system
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection and target season
 * - createIterator() creates AutumnIterator
 * - Returns iterator pre-configured for autumn filtering
 * - Used by seasonal browsing commands
 * - Part of seasonal iterator family (Spring, Summer, Winter variants)
 *
 * @see Aggregate (abstract factory interface)
 * @see AutumnIterator (concrete iterator created, has friend access)
 */
class AggAutumn : public Aggregate
{
	friend class AutumnIterator;

	private:
		/**
		 * @brief The target season for filtering.
		 */
		std::string targetSeason;

	public:
		/**
		 * @brief Constructor that initializes the aggregate with a plant collection and target season.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 * @param season The target season for filtering.
		 */
		AggAutumn(std::list<PlantComponent*>* plants, const std::string& season);

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
