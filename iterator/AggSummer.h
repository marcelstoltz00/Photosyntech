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
 * plants suitable for summer growing. Enables seasonal browsing and category-specific
 * customer shopping experiences.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * **Related Patterns:**
 * - Aggregate: Implements iterator factory interface
 * - Iterator: Creates SummerIterator instances (declared as friend)
 * - Decorator: Works with Summer decorator for filtering
 * - Facade: Enables seasonal browsing through system
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection and target season
 * - createIterator() creates SummerIterator
 * - Returns iterator pre-configured for summer filtering
 * - Used by seasonal browsing commands
 * - Part of seasonal iterator family (Spring, Autumn, Winter variants)
 *
 * @see Aggregate (abstract factory interface)
 * @see SummerIterator (concrete iterator created, has friend access)
 */
class AggSummer : public Aggregate
{
	friend class SummerIterator;

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
		AggSummer(std::list<PlantComponent*>* plants, const std::string& season);

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
