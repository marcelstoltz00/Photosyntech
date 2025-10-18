#ifndef Command_h
#define Command_h

/**
 * @brief Abstract command interface in the Command pattern.
 *
 * Declares the interface for executing and undoing nursery operations.
 * Concrete commands encapsulate specific actions (adding inventory, browsing,
 * watering, purchasing) with parameters and state for execution and undo.
 *
 * **System Role:**
 * This abstract class defines the contract for all operation commands in Photosyntech.
 * All user actions are encapsulated as command objects, enabling:
 * - Separation of action invocation from execution
 * - Undo/redo functionality through command history
 * - Operation logging and auditability
 * - Deferred or queued execution
 *
 * **Pattern Role:** Abstract Command (defines execution interface)
 *
 * **Related Patterns:**
 * - Concrete Commands: AddToInventoryCommand, WaterPlantCommand, PurchasePlantCommand, etc.
 * - Facade: NurseryFacade invokes commands and maintains history
 * - Singleton: Commands modify inventory through singleton
 * - Composite: Commands operate on plant components and groups
 * - Observer: Command execution may trigger observer notifications
 *
 * **System Interactions:**
 * - GUI/CLI translates user actions to command objects
 * - Facade stores commands in history for undo/redo
 * - Concrete command subclasses implement specific business logic
 * - Undo functionality stores pre-execution state
 *
 * @see Concrete command implementations
 * @see Facade (command history management)
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
