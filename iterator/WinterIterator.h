#ifndef WinterIterator_h
#define WinterIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"

/**
 * @brief Concrete iterator for filtering winter-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Winter seasonal decorator, enabling season-specific inventory views.
 */
class WinterIterator : public Iterator
{
	public:
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
};

#endif
