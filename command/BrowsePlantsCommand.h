#ifndef BrowsePlantsCommand_h
#define BrowsePlantsCommand_h

#include "Command.h"

/**
 * @brief Concrete command for browsing available plants in inventory.
 *
 * Encapsulates the operation of viewing and filtering plants in the inventory.
 * This is primarily a read operation with minimal state for undo.
 *
 * **System Role:**
 * Encapsulates inventory browsing and filtering operations. Delegates to Iterator
 * pattern for filtered collection traversal. Primarily read-only with no-op undo.
 * Enables consistent command structure for all user actions.
 *
 * **Pattern Role:** Concrete Command (implements browse-plants operation)
 *
 * **Related Patterns:**
 * - Command: Implements abstract command interface
 * - Facade: Invoked through facade for inventory browsing
 * - Iterator: Uses iterator factories for seasonal/category filtering
 * - Composite: Traverses PlantComponent hierarchies
 * - Singleton: Accesses inventory from singleton
 *
 * **System Interactions:**
 * - execute() retrieves inventory and applies optional filter criteria
 * - undo() is typically no-op (read operation doesn't modify state)
 * - Called through Facade by GUI/CLI for inventory viewing
 * - Supports filtering by season or other criteria via Iterator
 *
 * @see Command (abstract interface)
 * @see Iterator (provides filtered plant iteration)
 * @see Singleton (inventory access)
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
