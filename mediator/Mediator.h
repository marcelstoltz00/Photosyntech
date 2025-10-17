#ifndef __Mediator_h__
#define __Mediator_h__

#include <vector>

class User;
class Staff;

/**
 * @brief Abstract mediator interface for coordinating colleague interactions.
 *
 * Defines the interface for communicating between staff and customers.
 * Concrete mediators (SalesFloor, SuggestionFloor) implement coordination logic
 * and maintain references to colleagues, routing requests appropriately.
 */
class Mediator
{
	protected:
		std::vector<User*> _customerList;
		std::vector<Staff*> _staffList;

	public:
		/**
		 * @brief Routes a customer's assistance request to available staff.
		 * @param aCustomer Pointer to the User requesting assistance.
		 */
		virtual void getAssistance(User* aCustomer) = 0;

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
