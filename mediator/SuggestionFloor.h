#ifndef __SuggestionFloor_h__
#define __SuggestionFloor_h__

#include "Mediator.h"

/**
 * @brief Concrete mediator coordinating plant care suggestions.
 *
 * Manages communication between customers and staff on the suggestion floor,
 * routing plant care inquiries and coordinating expert advice delivery.
 */
class SuggestionFloor : public Mediator
{
	public:
		/**
		 * @brief Routes customer assistance requests to available advisory staff.
		 * @param aCustomer Pointer to the User requesting plant care suggestions.
		 */
		void getAssistance(User* aCustomer);

		/**
		 * @brief Coordinates staff assistance for suggestion operations.
		 */
		void assist();
};

#endif
