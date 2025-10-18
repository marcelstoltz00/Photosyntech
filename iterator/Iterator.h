#ifndef Iterator_h
#define Iterator_h

#include <list>
#include "../composite/PlantComponent.h"
#include "../prototype/LivingPlant.h"


/**
 * @brief Abstract iterator interface for traversing plant collections.
 *
 * Defines the interface for sequential access to plant collections with
 * optional filtering capabilities. Concrete iterators apply specific
 * filtering logic (e.g., by season) without exposing collection structure.
 */
class Iterator
{
	protected:
		std::list<PlantComponent*>* plants;

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
