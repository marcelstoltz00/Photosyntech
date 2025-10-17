#ifndef __Command_h__
#define __Command_h__

/**
 * @brief Abstract command interface in the Command pattern.
 *
 * Declares the interface for executing and undoing nursery operations.
 * Concrete commands encapsulate specific actions (adding inventory, browsing,
 * watering, purchasing) with parameters and state for execution and undo.
 */
class Command
{
	public:
		/**
		 * @brief Executes the encapsulated command.
		 */
		virtual void execute() = 0;

		/**
		 * @brief Undoes the previously executed command.
		 */
		virtual void undo() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Command() {}
};

#endif
