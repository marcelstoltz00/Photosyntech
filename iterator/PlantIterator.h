#ifndef PlantIterator_h
#define PlantIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"

/**
 * @brief Concrete iterator for unfiltered plant traversal.
 *
 * Iterates through all plants in a collection without applying any filters.
 * Provides sequential access to the entire plant inventory.
 */
class PlantIterator : public Iterator
{
	public:
		/**
		 * @brief Positions the iterator at the first plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current plant.
		 * @return Pointer to the current LivingPlant.
		 */
		LivingPlant* currentItem();
};

#endif
