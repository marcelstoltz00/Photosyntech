#ifndef PurchasePlantsCommand_h
#define PurchasePlantsCommand_h

#include "Command.h"
#include <list>

class Customer;
class SalesFloor;
class BasketMemento;
class PlantComponent;

/**
 * @brief Command for executing plant purchase transactions with undo support.
 *
 * Encapsulates a complete purchase transaction: validating the basket,
 * coordinating with the sales floor mediator, transferring plants from
 * inventory to customer, and enabling undo via memento restoration.
 *
 * **System Role:**
 * Manages complete purchase workflows in the command history.
 * Coordinates mediator-based sales operations and inventory transfers
 * with full transaction reversibility.
 *
 * **Pattern Role:** Concrete Command (Memento-based for complex state)
 *
 * **Related Patterns:**
 * - Command: Base interface for execution/undo
 * - Memento: Captures basket state before transaction
 * - Mediator: Coordinates through SalesFloor
 * - Composite: Plants managed as part of inventory groups
 * - Facade: Invoked by NurseryFacade with history management
 *
 * **System Interactions:**
 * - NurseryFacade creates PurchasePlantsCommand with customer and mediator
 * - Validates customer has non-empty basket
 * - Creates memento of basket contents (for undo)
 * - Coordinates sale through SalesFloor->assist()
 * - Transfers plants from inventory to customer
 * - Clears basket after purchase
 * - Undo restores basket contents and returns plants to inventory
 *
 * @see Command (base interface)
 * @see BasketMemento (transaction state capture)
 * @see SalesFloor (mediator for sales coordination)
 * @see NurseryFacade (command invocation)
 */
class PurchasePlantsCommand : public Command
{
private:
	/**
	 * @brief Reference to the customer making the purchase.
	 * Not owned by command; lifetime managed by system.
	 */
	Customer *customer;

	/**
	 * @brief Reference to the sales floor mediator.
	 * Not owned by command; lifetime managed by facade.
	 */
	SalesFloor *salesFloor;

	/**
	 * @brief Snapshot of basket contents before purchase.
	 * Owned by command; deleted in destructor.
	 */
	BasketMemento *memento;

	/**
	 * @brief List of plant pointers transferred from inventory during purchase.
	 * Used to know which plants to restore on undo.
	 */
	std::list<PlantComponent *> purchasedPlants;

	/**
	 * @brief Flag indicating whether transaction was completed successfully.
	 * Used to validate undo operation.
	 */
	bool transactionComplete;

public:
	/**
	 * @brief Constructs a PurchasePlantsCommand for the given customer and mediator.
	 * @param customer Pointer to the Customer making the purchase.
	 * @param salesFloor Pointer to the SalesFloor mediator.
	 * @throws std::invalid_argument if customer or salesFloor is null.
	 */
	explicit PurchasePlantsCommand(Customer *customer, SalesFloor *salesFloor);

	/**
	 * @brief Executes the plant purchase transaction.
	 *
	 * **Workflow:**
	 * 1. Validate customer != nullptr
	 * 2. Get customer basket via customer->getBasket()
	 * 3. Validate basket != nullptr and not empty
	 * 4. Create memento of basket contents (for undo)
	 * 5. Route purchase through salesFloor->assist()
	 * 6. For each plant in basket:
	 *    - Remove from global inventory
	 *    - Add to purchased plants list
	 * 7. Clear customer basket
	 * 8. Mark transaction complete
	 *
	 * @throws std::runtime_error if execution fails (e.g., empty basket, null mediator).
	 */
	void execute() override;

	/**
	 * @brief Undoes the plant purchase transaction.
	 *
	 * **Workflow:**
	 * 1. Validate transaction was completed
	 * 2. Restore basket from memento via memento->restoreBasket(customer)
	 * 3. For each purchased plant:
	 *    - Re-add to global inventory
	 * 4. Clear purchased plants list
	 * 5. Mark transaction reversed
	 *
	 * @throws std::runtime_error if undo fails.
	 */
	void undo() override;

	/**
	 * @brief Virtual destructor for proper cleanup.
	 * Deletes owned memento if present.
	 */
	virtual ~PurchasePlantsCommand();
};

#endif
