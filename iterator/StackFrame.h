#ifndef STACKFRAME_H
#define STACKFRAME_H

#include <list>
#include "../composite/PlantComponent.h"

/**
 * @brief Stack frame for bidirectional iterative tree traversal in iterator pattern.
 *
 * Stores the position in a single level of the plant hierarchy during
 * composite structure traversal. Used by PlantIterator and SeasonIterator
 * to maintain traversal state across nested PlantGroup hierarchies, supporting
 * both forward and backward navigation.
 *
 * **System Role:**
 * Enables O(1) amortized next() and back() operations by tracking position using
 * std::list iterators. Avoids re-traversal from root on each navigation call.
 * Supports bidirectional navigation through composite hierarchies.
 *
 * **Usage:**
 * - plantList: Pointer to the current level's plant collection
 * - current: std::list iterator pointing to current position (supports ++ and --)
 * - end: std::list iterator marking end of current level
 *
 * **Pattern Integration:**
 * - Used with std::stack for depth-first bidirectional traversal
 * - Supports both filtered (SeasonIterator) and unfiltered (PlantIterator) traversal
 * - Handles composite pattern navigation (PlantGroup hierarchies) in both directions
 * - std::list::iterator enables efficient forward and backward movement
 *
 * @see PlantIterator (uses for unfiltered bidirectional traversal)
 * @see SeasonIterator (uses for filtered bidirectional traversal)
 */
struct StackFrame {
	/**
	 * @brief Pointer to the plant list at this level of hierarchy.
	 */
	std::list<PlantComponent*>* plantList;

	/**
	 * @brief Current position within the list (std::list::iterator).
	 */
	std::list<PlantComponent*>::iterator current;

	/**
	 * @brief End position of the list (std::list::iterator).
	 */
	std::list<PlantComponent*>::iterator end;
};

#endif // STACKFRAME_H
