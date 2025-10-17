#ifndef __AutumnIterator_h__
#define __AutumnIterator_h__

#include "Iterator.h"

/**
 * @brief Concrete iterator for filtering autumn-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Autumn seasonal decorator, enabling season-specific inventory views.
 */
class AutumnIterator : public Iterator
{
	public:
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
};

#endif
