#ifndef SalesFloor_h
#define SalesFloor_h

#include "Mediator.h"

/**
 * @brief Concrete mediator coordinating sales transactions.
 *
 * Manages communication between customers and staff on the sales floor,
 * routing purchase requests and coordinating transaction processing.
 *
 * **System Role:**
 * Primary transaction coordinator for plant sales. Routes purchase requests
 * from customers to available sales staff. Executes purchase commands and
 * manages transaction state. Critical revenue flow control point.
 *
 * **Pattern Role:** Concrete Mediator (implements sales coordination)
 *
 * **Related Patterns:**
 * - Mediator: Implements abstract coordination interface
 * - Command: Executes PurchasePlantCommand for transactions
 * - Observer: Staff may notify on transaction completion
 * - Composite: Routes involving plant groups
 * - Singleton: Accesses inventory for stock management
 *
 * **System Interactions:**
 * - getAssistance(customer) routes purchase request to staff
 * - assist() executes purchase coordination logic
 * - Maintains staff and customer lists for routing
 * - Processes payment and inventory modifications
 * - Returns purchased plants to customer
 *
 * @see Mediator (abstract interface)
 * @see User (customers requesting purchases)
 * @see Staff (sales staff processing transactions)
 */
class SalesFloor : public Mediator
{
	public:
		/**
		 * @brief Routes customer assistance requests to available sales staff.
		 * @param customer Pointer to the User requesting sales assistance.
		 */
		void getAssistance(User* customer);

		/**
		 * @brief Coordinates staff assistance for sales operations.
		 */
		void assist();
};

#endif
