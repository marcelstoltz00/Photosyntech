#ifndef AggWinter_h
#define AggWinter_h

#include "Aggregate.h"
#include "WinterIterator.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating winter plant iterators.
 *
 * Creates WinterIterator instances that filter and return only winter-season plants.
 * Stores the plant collection and provides access to WinterIterator through friend relationship.
 *
 * **System Role:**
 * Factory for winter-season inventory iteration. Produces WinterIterator for browsing
 * plants suitable for winter growing. Enables seasonal browsing and category-specific
 * customer shopping experiences.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * **Related Patterns:**
 * - Aggregate: Implements iterator factory interface
 * - Iterator: Creates WinterIterator instances (declared as friend)
 * - Decorator: Works with Winter decorator for filtering
 * - Facade: Enables seasonal browsing through system
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection and target season
 * - createIterator() creates WinterIterator
 * - Returns iterator pre-configured for winter filtering
 * - Used by seasonal browsing commands
 * - Part of seasonal iterator family (Spring, Summer, Autumn variants)
 *
 * @see Aggregate (abstract factory interface)
 * @see WinterIterator (concrete iterator created, has friend access)
 */
class AggWinter : public Aggregate
{
	friend class WinterIterator;

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
		AggWinter(std::list<PlantComponent*>* plants, const std::string& season);

		/**
		 * @brief Creates a winter-filtered iterator for this aggregate's plant collection.
		 * @return Pointer to a WinterIterator for season-filtered traversal.
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggWinter() {}
};

#endif
