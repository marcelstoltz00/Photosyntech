#ifndef SalesFloor_h
#define SalesFloor_h

#include "Mediator.h"

/**
 * @brief Concrete mediator coordinating sales transactions.
 *
 * Manages communication between customers and staff on the sales floor,
 * routing purchase requests and coordinating transaction processing.
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
