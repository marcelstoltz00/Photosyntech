#ifndef __SpringIterator_h__
#define __SpringIterator_h__

#include "Iterator.h"

/**
 * @brief Concrete iterator for filtering spring-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Spring seasonal decorator, enabling season-specific inventory views.
 */
class SpringIterator : public Iterator
{
	public:
		/**
		 * @brief Positions the iterator at the first spring plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next spring plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more spring plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current spring plant.
		 * @return Pointer to the current spring LivingPlant.
		 */
		LivingPlant* currentItem();
};

#endif
