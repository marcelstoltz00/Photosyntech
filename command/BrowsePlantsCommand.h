#ifndef __BrowsePlantsCommand_h__
#define __BrowsePlantsCommand_h__

#include "Command.h"

class Singleton;

/**
 * @brief Concrete command for browsing available plants in inventory.
 *
 * Encapsulates the operation of viewing and filtering plants in the inventory.
 * This is primarily a read operation with minimal state for undo.
 */
class BrowsePlantsCommand : public Command
{
	public:
		/**
		 * @brief Executes the browse operation to display available plants.
		 */
		void execute();

		/**
		 * @brief Undoes the browse operation (typically a no-op for read operations).
		 */
		void undo();
};

#endif
