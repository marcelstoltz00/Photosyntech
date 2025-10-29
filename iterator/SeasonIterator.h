#ifndef PHOTOSYNTECH_SEASONITERATOR_H
#define PHOTOSYNTECH_SEASONITERATOR_H

#include "Iterator.h"
#include "StackFrame.h"
#include "../prototype/LivingPlant.h"
#include "../composite/PlantComponent.h"
#include "../composite/PlantGroup.h"
#include <stack>

/**
 * @brief Generic bidirectional concrete iterator for filtering plants by season.
 *
 * Iterates through a plant collection returning only plants whose getSeason()
 * method matches the target season string. Handles nested hierarchies by
 * descending into PlantGroups to find matching LivingPlants. Supports bidirectional
 * traversal, maintaining season filtering in both forward (next()) and backward (back())
 * directions.
 *
 * **System Role:**
 * Generic iterator for browsing season-specific plants bidirectionally. Enables
 * customers to view and select plants appropriate for any season (Spring, Summer,
 * Autumn, Winter). Skips non-matching plants during traversal in both directions,
 * providing focused seasonal inventory access with flexible navigation.
 *
 * **Pattern Role:** Concrete Iterator (bidirectional season-specific filtering with composite support)
 *
 * **Related Patterns:**
 * - Iterator: Implements bidirectional filtering traversal interface
 * - Aggregate: Created by AggSeason aggregate factory
 * - Decorator: Filters plants based on their seasonal decorator chain (via getSeason())
 * - Composite: Handles nested PlantGroup hierarchies in both directions
 * - Flyweight: Leverages shared season string pointers for O(1) comparison
 *
 * **System Interactions:**
 * - first() finds first plant matching target season
 * - next() advances to next matching plant, skipping non-matches
 * - back() moves to previous matching plant, skipping non-matches
 * - isDone() checks iteration completion
 * - currentItem() returns current matching plant
 * - Filters using direct Flyweight pointer comparison (plant->getSeason() == aggregate->targetSeason)
 * - Leverages Flyweight pattern: same season strings share same pointer for O(1) comparison
 * - Supports bidirectional navigation through filtered results
 *
 * **Implementation Details:**
 * - Uses std::stack<StackFrame> for iterative tree traversal
 * - Maintains O(1) amortized complexity for next() and back() operations
 * - Filtering applied consistently in both traversal directions
 * - Handles empty groups and composite boundaries gracefully
 *
 * @see Iterator (abstract interface)
 * @see AggSeason (creates this iterator)
 * @see LivingPlant::getSeason() (method used for filtering)
 * @see StackFrame (traversal state structure)
 */
class AggSeason;

class SeasonIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggSeason aggregate managing the collection and target season.
		 */
		SeasonIterator(AggSeason* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~SeasonIterator() {}

		/**
		 * @brief Positions the iterator at the first plant matching the target season.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next plant matching the target season.
		 */
		void next();

		/**
		 * @brief Moves the iterator back to the previous plant matching the target season.
		 */
		void back();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more matching plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current matching plant.
		 * @return Pointer to the current matching LivingPlant.
		 */
		LivingPlant* currentItem();

	private:
		/**
		 * @brief Cached pointer to the current matching plant, or nullptr if not found.
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
		 * @brief Advances to the next matching plant using iterative stack-based traversal.
		 * Filters by season while traversing. Replaces recursive findNextMatch.
		 */
		void advanceToNextPlant();

		/**
		 * @brief Moves back to the previous matching plant using iterative stack-based traversal.
		 * Filters by season while traversing backwards.
		 */
		void moveToPreviousPlant();

		/**
		 * @brief Positions iterator at the last matching plant (for back() from end position).
		 */
		void findLastPlant();
};

#endif //PHOTOSYNTECH_SEASONITERATOR_H
