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
