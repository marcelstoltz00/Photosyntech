#ifndef PlantIterator_h
#define PlantIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"

/**
 * @brief Concrete iterator for unfiltered plant traversal.
 *
 * Iterates through all plants in a collection without applying any filters.
 * Provides sequential access to the entire plant inventory.
 *
 * **System Role:**
 * Default iterator providing complete inventory traversal. Used by browse commands
 * when no filtering is requested. Enables systematic access to all plants regardless
 * of season, type, or other attributes. Foundation for other filtered iterators.
 *
 * **Pattern Role:** Concrete Iterator (implements complete traversal)
 *
 * **Related Patterns:**
 * - Iterator: Implements abstract traversal interface
 * - Aggregate: Created by AggPlant aggregate factory
 * - Composite: Traverses PlantComponent hierarchies
 * - Command: BrowsePlantsCommand uses for full inventory display
 *
 * **System Interactions:**
 * - first() initializes internal position to list start
 * - next() advances to subsequent plant
 * - isDone() checks if iteration complete
 * - currentItem() returns current plant reference
 * - No filtering applied, returns all plants
 * - Used when customers browse entire inventory
 *
 * @see Iterator (abstract interface)
 * @see AggPlant (creates this iterator)
 */
class AggPlant;

class PlantIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggPlant aggregate managing the collection.
		 */
		PlantIterator(AggPlant* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~PlantIterator() {}

		/**
		 * @brief Positions the iterator at the first plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current plant.
		 * @return Pointer to the current LivingPlant.
		 */
		LivingPlant* currentItem();

	private:
		std::list<PlantComponent*>::iterator current;
};

#endif
