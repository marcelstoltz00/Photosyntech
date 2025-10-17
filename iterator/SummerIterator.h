#ifndef __SummerIterator_h__
#define __SummerIterator_h__

#include "Iterator.h"

/**
 * @brief Concrete iterator for filtering summer-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Summer seasonal decorator, enabling season-specific inventory views.
 */
class SummerIterator : public Iterator
{
	public:
		/**
		 * @brief Positions the iterator at the first summer plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next summer plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more summer plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current summer plant.
		 * @return Pointer to the current summer LivingPlant.
		 */
		LivingPlant* currentItem();
};

#endif
