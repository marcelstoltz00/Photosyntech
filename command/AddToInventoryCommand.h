#ifndef AddToInventoryCommand_h
#define AddToInventoryCommand_h

#include "Command.h"

/**
 * @brief Concrete command for adding plants to the inventory.
 *
 * Encapsulates the operation of adding new plant instances to the global
 * inventory, storing references to added plants for potential undo.
 *
 * **System Role:**
 * Encapsulates the inventory expansion operation. When executed, adds new plants
 * to the singleton-managed inventory. Stores plant references to enable reversal
 * via undo operation. Core operation for stock management.
 *
 * **Pattern Role:** Concrete Command (implements add-to-inventory operation)
 *
 * **Related Patterns:**
 * - Command: Implements abstract command interface
 * - Facade: Invoked through facade for inventory management
 * - Singleton: Adds to singleton-managed inventory
 * - Composite: Adds PlantComponent to PlantGroup hierarchy
 * - Observer: Addition may trigger inventory notifications
 *
 * **System Interactions:**
 * - execute() adds plants to inventory PlantGroup
 * - undo() removes added plants, restoring previous inventory state
 * - Called through Facade by GUI/CLI during inventory setup
 * - Stored in command history for undo/redo functionality
 *
 * @see Command (abstract interface)
 * @see Singleton (inventory access)
 * @see PlantGroup (destination for additions)
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
