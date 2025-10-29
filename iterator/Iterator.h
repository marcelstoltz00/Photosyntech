#ifndef Iterator_h
#define Iterator_h

#include <list>
#include "../composite/PlantComponent.h"
#include "../prototype/LivingPlant.h"


/**
 * @brief Abstract iterator interface for bidirectional traversal of plant collections.
 *
 * Defines the interface for sequential and bidirectional access to plant collections
 * with optional filtering capabilities. Concrete iterators apply specific filtering
 * logic (e.g., by season) without exposing collection structure. Supports forward
 * and backward traversal via next() and back() methods.
 *
 * **System Role:**
 * Defines contract for all collection traversal algorithms. Enables filtering,
 * bidirectional navigation, and sequential access to plant inventory without
 * exposing internal structure. Key to inventory browsing operations and filtering
 * by season/criteria.
 *
 * **Pattern Role:** Abstract Iterator (defines bidirectional traversal interface)
 *
 * **Related Patterns:**
 * - Aggregate: Creates concrete iterators
 * - Composite: Traverses plant hierarchies via PlantComponent interface
 * - Facade: Provides convenient iterator creation methods
 * - Command: BrowsePlantsCommand uses iterators for filtering
 *
 * **System Interactions:**
 * - Aggregate creates concrete iterator instances
 * - first() initializes iteration at beginning
 * - next() advances to next filtered element
 * - back() moves to previous filtered element
 * - isDone() determines iteration completion
 * - currentItem() returns current plant
 * - Concrete iterators implement filtering logic
 * - Supports bidirectional navigation for flexible browsing
 *
 * @see Aggregate (creates iterators)
 * @see Concrete iterators: PlantIterator, SeasonIterator
 */
class Aggregate;

class Iterator
{
	protected:
		Aggregate* aggregate;

	public:
		/**
		 * @brief Positions the iterator at the first element.
		 */
		virtual void first() = 0;

		/**
		 * @brief Advances the iterator to the next element.
		 */
		virtual void next() = 0;

		/**
		 * @brief Moves the iterator back to the previous element.
		 */
		virtual void back() = 0;

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more elements to iterate, false otherwise.
		 */
		virtual bool isDone() = 0;

		/**
		 * @brief Returns the current plant element.
		 * @return Pointer to the current LivingPlant in the iteration.
		 */
		virtual LivingPlant* currentItem() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Iterator() {}
};

#endif
