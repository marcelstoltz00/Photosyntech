#ifndef PHOTOSYNTECH_AGGPLANTNAME_H
#define PHOTOSYNTECH_AGGPLANTNAME_H

#include "Aggregate.h"
#include "PlantNameIterator.h"
#include <list>
#include <string>
#include "../composite/PlantComponent.h"
#include "../flyweight/Flyweight.h"

/**
 * @brief Generic concrete aggregate for creating name-filtered bidirectional plant iterators.
 *
 * Creates PlantNameIterator instances that filter and return only plants matching
 * the specified target plant name, supporting both forward and backward navigation.
 * Stores the plant collection and provides access to PlantNameIterator through
 * friend relationship.
 *
 * **System Role:**
 * Factory for name-specific inventory iteration. Produces bidirectional PlantNameIterator
 * for browsing plants by exact name match (e.g., searching for "Rose" or "Succulent").
 * Enables specific plant type searching with full navigation control and targeted customer
 * shopping experiences.
 *
 * **Pattern Role:** Concrete Aggregate (bidirectional name-filtered iterator factory)
 *
 * **Related Patterns:**
 * - Aggregate: Implements bidirectional iterator factory interface
 * - Iterator: Creates bidirectional PlantNameIterator instances (declared as friend)
 * - Flyweight: Uses Flyweight name pointers for O(1) filtering comparisons via getNameFlyweight()
 * - Facade: Enables plant name searching through system
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection and target name
 * - createIterator() creates bidirectional PlantNameIterator
 * - Returns iterator pre-configured for name filtering with next()/back()
 * - Used by plant search/browsing commands
 * - Converts name strings to Flyweight pointers for O(1) comparison
 *
 * @see Aggregate (abstract factory)
 * @see PlantNameIterator (concrete bidirectional iterator created, has friend access)
 */
class AggPlantName : public Aggregate
{
	friend class PlantNameIterator;

	private:
		/**
		 * @brief The target name for filtering as a Flyweight pointer.
		 * Shared across all instances filtering the same name for memory efficiency.
		 */
		Flyweight<std::string*>* targetName;

	public:
		/**
		 * @brief Constructor that initializes the aggregate with a plant collection and target name string.
		 * Converts the name string to a Flyweight internally.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 * @param name The target plant name string for filtering (e.g., "Rose", "Succulent", "Oak").
		 */
		AggPlantName(std::list<PlantComponent*>* plants, const std::string& name);

		/**
		 * @brief Constructor that initializes the aggregate with a plant collection and Flyweight name.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 * @param name Flyweight pointer to the target name for filtering.
		 */
		AggPlantName(std::list<PlantComponent*>* plants, Flyweight<std::string*>* name);

		/**
		 * @brief Creates a name-filtered bidirectional iterator for this aggregate's plant collection.
		 * @return Pointer to a PlantNameIterator for name-filtered bidirectional traversal (supports next() and back()).
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggPlantName() {}
};

#endif //PHOTOSYNTECH_AGGPLANTNAME_H
