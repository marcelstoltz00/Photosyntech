#ifndef PHOTOSYNTECH_SEASONITERATOR_H
#define PHOTOSYNTECH_SEASONITERATOR_H

#include "Iterator.h"
#include "../prototype/LivingPlant.h"
#include "../composite/PlantComponent.h"
#include "../composite/PlantGroup.h"
#include <stack>

/**
 * @brief Generic concrete iterator for filtering plants by season.
 *
 * Iterates through a plant collection returning only plants whose getSeason()
 * method matches the target season string. Handles nested hierarchies by
 * recursively descending into PlantGroups to find matching LivingPlants.
 *
 * **System Role:**
 * Generic iterator for browsing season-specific plants. Enables customers to
 * view and select plants appropriate for any season (Spring, Summer, Autumn, Winter).
 * Skips non-matching plants during traversal, providing focused seasonal inventory access.
 *
 * **Pattern Role:** Concrete Iterator (season-specific filtering with composite support)
 *
 * **Related Patterns:**
 * - Iterator: Implements filtering traversal interface
 * - Aggregate: Created by AggSeason aggregate factory
 * - Decorator: Filters plants based on their seasonal decorator chain (via getSeason())
 * - Composite: Handles nested PlantGroup hierarchies
 *
 * **System Interactions:**
 * - first() finds first plant matching target season
 * - next() advances to next matching plant
 * - isDone() checks iteration completion
 * - currentItem() returns current matching plant
 * - Filters by comparing plant->getSeason() to aggregate->targetSeason
 *
 * @see Iterator (abstract interface)
 * @see AggSeason (creates this iterator)
 * @see LivingPlant::getSeason() (method used for filtering)
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
		 * @brief Stack frame for iterative tree traversal.
		 * Stores position in a single level of the plant hierarchy.
		 */
		struct StackFrame {
			std::list<PlantComponent*>* plantList;
			std::list<PlantComponent*>::iterator current;
			std::list<PlantComponent*>::iterator end;
		};

		/**
		 * @brief Stack tracking current position in nested plant groups.
		 * Enables O(1) next() by avoiding re-traversal from root.
		 */
		std::stack<StackFrame> traversalStack;

		/**
		 * @brief Flag indicating if currently inside a PlantGroup composite.
		 */
		bool inComposite;

		/**
		 * @brief Advances to the next matching plant using iterative stack-based traversal.
		 * Filters by season while traversing. Replaces recursive findNextMatch.
		 */
		void advanceToNextPlant();
};

#endif //PHOTOSYNTECH_SEASONITERATOR_H
