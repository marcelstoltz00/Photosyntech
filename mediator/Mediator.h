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
