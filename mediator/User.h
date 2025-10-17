#ifndef __User_h__
#define __User_h__

#include <string>

class Mediator;

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
		std::string _name;
		Mediator* _salesFloor;
		Mediator* _suggestionFloor;

	public:
		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~User() {}
};

#endif
