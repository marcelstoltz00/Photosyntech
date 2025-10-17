#ifndef __AddToInventoryCommand_h__
#define __AddToInventoryCommand_h__

#include "Command.h"

class PlantComponent;
class Singleton;

/**
 * @brief Concrete command for adding plants to the inventory.
 *
 * Encapsulates the operation of adding new plant instances to the global
 * inventory, storing references to added plants for potential undo.
 */
class AddToInventoryCommand : public Command
{
	public:
		/**
		 * @brief Executes the operation to add plants to inventory.
		 */
		void execute();

		/**
		 * @brief Undoes the add operation by removing the plants from inventory.
		 */
		void undo();
};

#endif
