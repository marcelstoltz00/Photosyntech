#ifndef WaterPlantCommand_h
#define WaterPlantCommand_h

#include "Command.h"

/**
 * @brief Concrete command for watering a plant.
 *
 * Encapsulates the operation of applying water to a specific plant,
 * storing necessary state to undo the operation if needed.
 *
 * **System Role:**
 * Encapsulates plant care operation (watering). Delegates to plant's
 * WaterStrategy for algorithm execution. Stores pre-watering state for undo.
 * Fundamental operation for staff care routines.
 *
 * **Pattern Role:** Concrete Command (implements water-plant operation)
 *
 * **Related Patterns:**
 * - Command: Implements abstract command interface
 * - Facade: Invoked through facade for watering operations
 * - Strategy: Executes plant's assigned WaterStrategy
 * - Composite: Can operate on individual plants or plant groups
 * - Observer: Watering may trigger observer notifications
 * - Singleton: Accesses plants from singleton inventory
 *
 * **System Interactions:**
 * - execute() applies water via plant's WaterStrategy
 * - Stores pre-water plant state for undo capability
 * - undo() restores plant to pre-watering state
 * - Called through Facade by staff or automated routines
 * - Triggers plant state notifications to observers
 *
 * @see Command (abstract interface)
 * @see Strategy (plant's WaterStrategy execution)
 * @see PlantComponent (operates on plants)
 */
class WaterPlantCommand : public Command
{
	public:
		/**
		 * @brief Executes the watering operation on the plant.
		 */
		void execute();

		/**
		 * @brief Undoes the watering operation.
		 */
		void undo();
};

#endif
