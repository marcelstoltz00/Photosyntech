#ifndef WinterIterator_h
#define WinterIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"

/**
 * @brief Concrete iterator for filtering winter-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Winter seasonal decorator, enabling season-specific inventory views.
 *
 * **System Role:**
 * Specialized iterator for winter-season inventory browsing. Enables customers to
 * view plants suitable for winter growing. Skips non-winter plants during traversal
 * for focused seasonal shopping.
 *
 * **Pattern Role:** Concrete Iterator (winter-specific filtering)
 *
 * **Related Patterns:**
 * - Iterator: Implements filtering traversal
 * - Aggregate: Created by AggWinter factory
 * - Decorator: Identifies via Winter decorator
 *
 * @see Iterator (abstract interface)
 * @see AggWinter (creates this iterator)
 * @see Winter (decorator identifying winter plants)
 */
class AggWinter;

class WinterIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggWinter aggregate managing the collection.
		 */
		WinterIterator(AggWinter* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~WinterIterator() {}

		/**
		 * @brief Positions the iterator at the first winter plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next winter plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more winter plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current winter plant.
		 * @return Pointer to the current winter LivingPlant.
		 */
		LivingPlant* currentItem();

	private:
		std::list<PlantComponent*>::iterator current;
};

#endif
