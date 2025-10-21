#ifndef AggSpring_h
#define AggSpring_h

#include "Aggregate.h"
#include "SpringIterator.h"
#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Concrete aggregate for creating spring plant iterators.
 *
 * Creates SpringIterator instances that filter and return only spring-season plants.
 * Stores the plant collection and provides access to SpringIterator through friend relationship.
 *
 * **System Role:**
 * Factory for spring-season inventory iteration. Produces SpringIterator for browsing
 * plants suitable for spring growing. Enables seasonal browsing and category-specific
 * customer shopping experiences.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * **Related Patterns:**
 * - Aggregate: Implements iterator factory interface
 * - Iterator: Creates SpringIterator instances (declared as friend)
 * - Decorator: Works with Spring decorator for filtering
 * - Facade: Enables seasonal browsing through system
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection
 * - createIterator() creates SpringIterator
 * - Returns iterator pre-configured for spring filtering
 * - Used by seasonal browsing commands
 * - Part of seasonal iterator family (Summer, Autumn, Winter variants)
 *
 * @see Aggregate (abstract factory)
 * @see SpringIterator (concrete iterator created, has friend access)
 */
class AggSpring : public Aggregate
{
	friend class SpringIterator;

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
		AggSpring(std::list<PlantComponent*>* plants, const std::string& season);

		/**
		 * @brief Creates a spring-filtered iterator for this aggregate's plant collection.
		 * @return Pointer to a SpringIterator for season-filtered traversal.
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggSpring() {}
};

#endif
