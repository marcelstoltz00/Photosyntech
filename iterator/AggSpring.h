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
 * - Iterator: Creates SpringIterator instances
 * - Decorator: Works with Spring decorator for filtering
 * - Facade: Enables seasonal browsing through system
 *
 * **System Interactions:**
 * - createIterator(plants) creates SpringIterator
 * - Returns iterator pre-configured for spring filtering
 * - Used by seasonal browsing commands
 * - Part of seasonal iterator family (Summer, Autumn, Winter variants)
 *
 * @see Aggregate (abstract factory)
 * @see SpringIterator (concrete iterator created)
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

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggSpring() {}
};

#endif
