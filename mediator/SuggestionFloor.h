#ifndef SuggestionFloor_h
#define SuggestionFloor_h

#include "Mediator.h"

/**
 * @brief Concrete mediator coordinating plant care suggestions.
 *
 * Manages communication between customers and staff on the suggestion floor,
 * routing plant care inquiries and coordinating expert advice delivery.
 *
 * **System Role:**
 * Advisory coordination floor. Routes customer plant care questions to expert staff.
 * Provides recommendations for plant selection, care, and problem-solving. Enhances
 * customer experience through personalized guidance. Complementary to SalesFloor.
 *
 * **Pattern Role:** Concrete Mediator (implements suggestion coordination)
 *
 * **Related Patterns:**
 * - Mediator: Implements abstract coordination interface
 * - Observer: Staff may provide recommendations based on monitoring
 * - Command: May trigger informational commands for recommendations
 * - Composite: Recommendations involve plant groups/types
 * - Singleton: Accesses inventory for recommendation data
 *
 * **System Interactions:**
 * - getAssistance(customer) routes care inquiry to staff
 * - assist() executes suggestion coordination logic
 * - Maintains staff and customer lists for routing
 * - Provides plant care expertise and recommendations
 * - Helps customers select appropriate plants
 * - Advises on plant maintenance and problem resolution
 *
 * @see Mediator (abstract interface)
 * @see SalesFloor (transaction coordinator)
 * @see Staff (provides expert recommendations)
 */
class SuggestionFloor : public Mediator
{
	public:
	SuggestionFloor();
		/**
		 * @brief Routes customer assistance requests to available advisory staff.
		 * @param customer Pointer to the User requesting plant care suggestions.
		 */
		string getAssistance(User* customer);

		/**
		 * @brief Coordinates staff assistance for suggestion operations.
		 */
		void assist();
};

#endif
