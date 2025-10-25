#ifndef GrowPlantCommand_h
#define GrowPlantCommand_h

#include "Command.h"

class LivingPlant;
class PlantMemento;

/**
 * @brief Command for executing plant growth with undo support.
 *
 * Encapsulates the plant growth operation using the State pattern.
 * Captures plant state before growth and enables undo via memento restoration.
 * Notifies observers when growth completes.
 *
 * **System Role:**
 * Enables reversible plant growth operations in the command history.
 * Coordinates state transitions through the maturity state lifecycle
 * and observer notifications.
 *
 * **Pattern Role:** Concrete Command (encapsulates growth operation)
 *
 * **Related Patterns:**
 * - Command: Base interface for execution/undo
 * - Memento: Captures pre-growth state for undo
 * - State: Delegates growth behavior to MaturityState
 * - Observer: Notifies watchers of state changes
 * - Facade: Invoked by NurseryFacade with history management
 *
 * **System Interactions:**
 * - NurseryFacade creates and executes GrowPlantCommand
 * - Captures plant state via PlantMemento before growth
 * - Calls MaturityState::grow() to execute growth logic
 * - Notifies plant group observers of state changes
 * - Undo restores all attributes from memento
 *
 * @see Command (base interface)
 * @see PlantMemento (state capture)
 * @see MaturityState (growth behavior)
 * @see NurseryFacade (command invocation)
 */
class GrowPlantCommand : public Command
{
private:
	/**
	 * @brief Reference to the plant being grown.
	 * Not owned by command; lifetime managed by inventory.
	 */
	LivingPlant *plant;

	/**
	 * @brief Snapshot of plant state before growth.
	 * Owned by command; deleted in destructor.
	 */
	PlantMemento *memento;

public:
	/**
	 * @brief Constructs a GrowPlantCommand for the given plant.
	 * @param plant Pointer to the LivingPlant to grow.
	 * @throws std::invalid_argument if plant is null.
	 */
	explicit GrowPlantCommand(LivingPlant *plant);

	/**
	 * @brief Executes the plant growth operation.
	 *
	 * **Workflow:**
	 * 1. Validate plant is not null
	 * 2. Create memento of current plant state
	 * 3. Get current maturity state from Inventory singleton
	 * 4. Call state->grow(plant) to execute growth
	 * 5. State may transition (Seed→Vegetative→Mature→Dead)
	 * 6. Notify observers via plant group's stateUpdated()
	 *
	 * @throws std::runtime_error if growth fails or observers cannot be notified.
	 */
	void execute() override;

	/**
	 * @brief Undoes the plant growth operation.
	 *
	 * **Workflow:**
	 * 1. Restore plant state from memento:
	 *    - age, health, waterLevel, sunExposure, maturityStateID
	 * 2. Notify observers of state restoration
	 * 3. Memento is deleted after restoration
	 *
	 * @throws std::runtime_error if restoration fails.
	 */
	void undo() override;

	/**
	 * @brief Virtual destructor for proper cleanup.
	 * Deletes owned memento if present.
	 */
	virtual ~GrowPlantCommand();
};

#endif
