#ifndef PlantIterator_h
#define PlantIterator_h

#include "Iterator.h"
#include "StackFrame.h"
#include "../prototype/LivingPlant.h"
#include "../composite/PlantComponent.h"
#include "../composite/PlantGroup.h"
#include <stack>

/**
 * @brief Concrete bidirectional iterator for unfiltered plant traversal.
 *
 * Iterates through all plants in a collection without applying any filters.
 * Handles nested hierarchies by descending into PlantGroups to find all
 * LivingPlants. Provides bidirectional sequential access to the entire plant
 * inventory, supporting both forward (next()) and backward (back()) navigation.
 *
 * **System Role:**
 * Default iterator providing complete inventory traversal. Used by browse commands
 * when no filtering is requested. Enables systematic bidirectional access to all
 * plants regardless of season, type, or other attributes. Foundation for other
 * filtered iterators.
 *
 * **Pattern Role:** Concrete Iterator (implements bidirectional traversal with composite support)
 *
 * **Related Patterns:**
 * - Iterator: Implements abstract bidirectional traversal interface
 * - Aggregate: Created by AggPlant aggregate factory
 * - Composite: Handles nested PlantGroup hierarchies in both directions
 * - Command: BrowsePlantsCommand uses for full inventory display
 *
 * **System Interactions:**
 * - first() initializes internal position to list start
 * - next() advances to subsequent plant
 * - back() moves to previous plant
 * - isDone() checks if iteration complete
 * - currentItem() returns current plant reference
 * - No filtering applied, returns all plants
 * - Supports bidirectional navigation through composite hierarchies
 * - Used when customers browse entire inventory
 *
 * **Implementation Details:**
 * - Uses std::stack<StackFrame> for iterative tree traversal
 * - Maintains O(1) amortized complexity for next() and back()
 * - Handles empty groups and composite boundaries gracefully
 *
 * @see Iterator (abstract interface)
 * @see AggPlant (creates this iterator)
 * @see StackFrame (traversal state structure)
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
		 * @brief Moves the iterator back to the previous plant.
		 */
		void back();

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
		/**
		 * @brief Cached pointer to the current plant, or nullptr if not found.
		 */
		LivingPlant* currentPlant;

		/**
		 * @brief Stack tracking current position in nested plant groups.
		 * Enables O(1) next() by avoiding re-traversal from root.
		 * Uses shared StackFrame struct for iterative tree traversal.
		 */
		std::stack<StackFrame> traversalStack;

		/**
		 * @brief Flag indicating if currently inside a PlantGroup composite.
		 */
		bool inComposite;

		/**
		 * @brief Flag indicating if we moved past the end (true) vs before beginning (false).
		 * Used to determine behavior when stack is empty and currentPlant is nullptr.
		 */
		bool pastEnd;

		/**
		 * @brief Advances to the next plant using iterative stack-based traversal.
		 * Replaces recursive findNextMatch with O(1) amortized complexity.
		 */
		void advanceToNextPlant();

		/**
		 * @brief Moves back to the previous plant using iterative stack-based traversal.
		 * Handles composite hierarchy traversal in reverse direction.
		 */
		void moveToPreviousPlant();

		/**
		 * @brief Positions iterator at the last plant (for back() from end position).
		 */
		void findLastPlant();
};

#endif
