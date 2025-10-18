#ifndef Mediator_h
#define Mediator_h

#include <vector>
#include "User.h"
#include "Staff.h"

/**
 * @brief Abstract mediator interface for coordinating colleague interactions.
 *
 * Defines the interface for communicating between staff and customers.
 * Concrete mediators (SalesFloor, SuggestionFloor) implement coordination logic
 * and maintain references to colleagues, routing requests appropriately.
 *
 * **System Role:**
 * Defines contract for staff-customer coordination. Different mediators handle
 * different interaction types (sales vs. suggestions). Central hub for all
 * staff-customer transactions and communication routing.
 *
 * **Pattern Role:** Abstract Mediator (coordination interface)
 *
 * **Related Patterns:**
 * - Colleague: Staff and Customer implement colleague interface
 * - Observer: Staff may use observer pattern for notifications
 * - Command: May trigger command execution for transactions
 * - Facade: Coordinates mediator setup and interactions
 *
 * **System Interactions:**
 * - getAssistance(customer) routes customer requests to staff
 * - assist() executes coordination logic
 * - Maintains customerList and staffList for coordination
 * - Concrete mediators implement transaction-specific logic
 * - Decouples staff and customers through mediation
 *
 * @see Concrete mediators: SalesFloor, SuggestionFloor
 * @see User (colleagues in mediation)
 * @see Staff (concrete colleague)
 */
class Mediator
{
	protected:
		std::vector<User*> customerList;
		std::vector<Staff*> staffList;

	public:
		/**
		 * @brief Routes a customer's assistance request to available staff.
		 * @param customer Pointer to the User requesting assistance.
		 */
		virtual void getAssistance(User* customer) = 0;

		/**
		 * @brief Coordinates staff assistance operations.
		 */
		virtual void assist() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Mediator() {}
};

#endif
