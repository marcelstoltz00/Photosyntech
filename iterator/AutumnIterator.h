#ifndef AutumnIterator_h
#define AutumnIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"

/**
 * @brief Concrete iterator for filtering autumn-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Autumn seasonal decorator, enabling season-specific inventory views.
 *
 * **System Role:**
 * Specialized iterator for autumn-season inventory browsing. Enables customers to
 * view plants suitable for autumn growing. Skips non-autumn plants during traversal
 * for focused seasonal shopping.
 *
 * **Pattern Role:** Concrete Iterator (autumn-specific filtering)
 *
 * **Related Patterns:**
 * - Iterator: Implements filtering traversal
 * - Aggregate: Created by AggAutumn factory
 * - Decorator: Identifies via Autumn decorator
 *
 * @see Iterator (abstract interface)
 * @see AggAutumn (creates this iterator)
 * @see Autumn (decorator identifying autumn plants)
 */
class AggAutumn;

class AutumnIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggAutumn aggregate managing the collection.
		 */
		AutumnIterator(AggAutumn* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AutumnIterator() {}

		/**
		 * @brief Positions the iterator at the first autumn plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next autumn plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more autumn plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current autumn plant.
		 * @return Pointer to the current autumn LivingPlant.
		 */
		LivingPlant* currentItem();

	private:
		std::list<PlantComponent*>::iterator current;
};

#endif
