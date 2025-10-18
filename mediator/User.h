#ifndef User_h
#define User_h

#include <string>
#include "Mediator.h"

/**
 * @brief Abstract base class for users in the Mediator pattern.
 *
 * Acts as a colleague that communicates with other colleagues through
 * the mediator. Maintains references to sales and suggestion floor mediators
 * for coordinated interactions. Subclasses include Customer and Staff.
 *
 * **System Role:**
 * Base class for all mediated participants in the system. Provides interface
 * for colleagues to access mediators (sales and suggestion floors) without
 * directly communicating with each other. Enables loosely coupled staff-customer
 * interactions through mediation.
 *
 * **Pattern Role:** Abstract Colleague (mediated participant interface)
 *
 * **Related Patterns:**
 * - Mediator: References sales and suggestion floor mediators
 * - Staff: Concrete colleague implementing user interface
 * - Customer: Concrete colleague implementing user interface
 *
 * **System Interactions:**
 * - Maintains references to both mediator types
 * - Provides access to mediated communication channels
 * - Subclasses implement specific participant behavior
 *
 * @see Mediator (coordination infrastructure)
 * @see Staff (concrete colleague)
 * @see Customer (concrete colleague)
 */
class User
{
	protected:
		std::string name;
		Mediator* salesFloor;
		Mediator* suggestionFloor;

	public:
		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~User() {}
};

#endif
