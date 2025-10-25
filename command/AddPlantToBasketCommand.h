#ifndef AddPlantToBasketCommand_h
#define AddPlantToBasketCommand_h

#include "Command.h"

class Customer;
class PlantComponent;

/**
 * @brief Command for adding a plant to a customer's shopping basket.
 *
 * Encapsulates the operation of adding a plant to a customer's basket with undo support.
 * Creates the basket if needed and tracks whether it was newly created for proper undo.
 *
 * **System Role:**
 * Enables reversible basket modifications in the command history.
 * Manages customer shopping baskets as part of the purchase workflow.
 *
 * **Pattern Role:** Concrete Command (Direct Undo approach)
 *
 * **Related Patterns:**
 * - Command: Base interface for execution/undo
 * - Mediator: Customer is a mediator colleague
 * - Composite: Basket is a PlantGroup containing plants
 * - Facade: Invoked by NurseryFacade with history management
 *
 * **System Interactions:**
 * - NurseryFacade creates and executes AddPlantToBasketCommand
 * - Calls customer->addPlant() to add to basket
 * - Tracks whether basket was created (for proper undo)
 * - Undo removes plant and clears basket if it was created by this command
 *
 * @see Command (base interface)
 * @see Customer (mediator colleague)
 * @see PlantComponent (plant to add)
 * @see NurseryFacade (command invocation)
 */
class AddPlantToBasketCommand : public Command
{
private:
	/**
	 * @brief Reference to the customer whose basket receives the plant.
	 * Not owned by command; lifetime managed by system.
	 */
	Customer *customer;

	/**
	 * @brief Reference to the plant being added to the basket.
	 * Not owned by command; lifetime managed by inventory.
	 */
	PlantComponent *plant;

	/**
	 * @brief Flag indicating whether basket was null before this operation.
	 * Used to determine undo behavior (clear basket only if we created it).
	 */
	bool basketWasNull;

public:
	/**
	 * @brief Constructs an AddPlantToBasketCommand for the given customer and plant.
	 * @param customer Pointer to the Customer adding plants to basket.
	 * @param plant Pointer to the PlantComponent to add.
	 * @throws std::invalid_argument if customer or plant is null.
	 */
	explicit AddPlantToBasketCommand(Customer *customer, PlantComponent *plant);

	/**
	 * @brief Executes the add-to-basket operation.
	 *
	 * **Workflow:**
	 * 1. Validate customer and plant are not null
	 * 2. Check if customer's basket is null
	 * 3. Record basketWasNull flag
	 * 4. Call customer->addPlant(plant)
	 * 5. Basket is created by customer if it didn't exist
	 *
	 * @throws std::runtime_error if execution fails.
	 */
	void execute() override;

	/**
	 * @brief Undoes the add-to-basket operation.
	 *
	 * **Workflow:**
	 * 1. Validate customer and plant exist
	 * 2. Remove plant from basket via getBasket()->removeComponent(plant)
	 * 3. If basketWasNull was true (basket was created by execute):
	 *    - Call customer->clearBasket() to delete the basket
	 * 4. Otherwise, keep basket with remaining plants
	 *
	 * @throws std::runtime_error if undo fails (e.g., plant not in basket).
	 */
	void undo() override;

	/**
	 * @brief Virtual destructor for proper cleanup.
	 * No dynamic allocation in this command.
	 */
	virtual ~AddPlantToBasketCommand() = default;
};

#endif
