#ifndef GetSuggestionCommand_h
#define GetSuggestionCommand_h

#include "Command.h"

class Customer;
class SuggestionFloor;

/**
 * @brief Command for requesting plant suggestions from sales staff.
 *
 * Encapsulates a read-only query operation that routes customer requests
 * through the SuggestionFloor mediator to generate plant recommendations.
 * No state changes occur, making undo a no-op.
 *
 * **System Role:**
 * Enables reversible (but stateless) suggestion queries through the command history.
 * Coordinates mediator-based recommendation generation.
 *
 * **Pattern Role:** Concrete Command (Direct Undo approach - read-only)
 *
 * **Related Patterns:**
 * - Command: Base interface for execution/undo
 * - Mediator: Coordinates through SuggestionFloor
 * - Facade: Invoked by NurseryFacade with history management
 *
 * **System Interactions:**
 * - NurseryFacade creates GetSuggestionCommand with customer and mediator
 * - Routes request through SuggestionFloor->assist()
 * - Mediator coordinates staff-customer interaction
 * - Suggestions generated based on customer needs
 * - Undo is no-op (read-only, no state changes)
 *
 * @see Command (base interface)
 * @see SuggestionFloor (mediator for suggestion coordination)
 * @see NurseryFacade (command invocation)
 */
class GetSuggestionCommand : public Command
{
private:
	/**
	 * @brief Reference to the customer requesting suggestions.
	 * Not owned by command; lifetime managed by system.
	 */
	Customer *customer;

	/**
	 * @brief Reference to the suggestion floor mediator.
	 * Not owned by command; lifetime managed by facade.
	 */
	SuggestionFloor *suggestionFloor;

public:
	/**
	 * @brief Constructs a GetSuggestionCommand for the given customer.
	 * @param customer Pointer to the Customer requesting suggestions.
	 * @param suggestionFloor Pointer to the SuggestionFloor mediator.
	 * @throws std::invalid_argument if customer or suggestionFloor is null.
	 */
	explicit GetSuggestionCommand(Customer *customer, SuggestionFloor *suggestionFloor);

	/**
	 * @brief Executes the get-suggestions operation.
	 *
	 * **Workflow:**
	 * 1. Validate customer != nullptr
	 * 2. Route request through suggestionFloor->assist()
	 * 3. Mediator coordinates with available staff
	 * 4. Generate recommendations based on customer needs
	 * 5. Store suggestions for display
	 *
	 * This is a read-only operation with no side effects on plant state or inventory.
	 *
	 * @throws std::runtime_error if execution fails (e.g., null customer/mediator).
	 */
	void execute() override;

	/**
	 * @brief Undoes the get-suggestions operation.
	 *
	 * **No-op implementation:**
	 * This is a read-only operation. No state changes occur during execute(),
	 * so undo() performs no action. The suggestion history remains for display.
	 *
	 * This method exists for interface compliance but performs no operations.
	 */
	void undo() override;

	/**
	 * @brief Virtual destructor for proper cleanup.
	 * No dynamic allocation in this command.
	 */
	virtual ~GetSuggestionCommand() = default;
};

#endif
