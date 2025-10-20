#ifndef PurchasePlantCommand_h
#define PurchasePlantCommand_h

#include "Command.h"

/**
 * @brief Concrete command for purchasing a plant.
 *
 * Encapsulates the transaction logic for purchasing plants, including
 * removing from inventory and processing payment. Stores transaction
 * details for potential undo operations.
 *
 * **System Role:**
 * Encapsulates complete purchase transaction workflow. Coordinates removal from
 * inventory, transaction processing, and customer basket management through
 * Mediator pattern. Critical operation for sales functionality.
 *
 * **Pattern Role:** Concrete Command (implements purchase-plant operation)
 *
 * **Related Patterns:**
 * - Command: Implements abstract command interface
 * - Facade: Invoked through facade for purchase processing
 * - Mediator: Uses SalesFloor mediator for transaction coordination
 * - Singleton: Modifies inventory via singleton
 * - Composite: Removes PlantComponent from inventory hierarchy
 * - Observer: Purchase may trigger inventory notifications
 *
 * **System Interactions:**
 * - execute() coordinates sale through SalesFloor mediator
 * - Removes plant from inventory PlantGroup
 * - Processes transaction through mediator
 * - undo() restores plant to inventory and reverts transaction
 * - Called through Facade by GUI for customer purchases
 *
 * @see Command (abstract interface)
 * @see Mediator (SalesFloor coordinates transaction)
 * @see Singleton (inventory modification)
 * @see PlantGroup (inventory removal)
 */
class PurchasePlantCommand : public Command
{
	public:
		/**
		 * @brief Executes the purchase transaction.
		 */
		void execute();

		/**
		 * @brief Undoes the purchase transaction.
		 */
		void undo();
};

#endif
