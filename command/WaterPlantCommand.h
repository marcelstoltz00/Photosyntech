#ifndef __WaterPlantCommand_h__
#define __WaterPlantCommand_h__

#include "Command.h"

class LivingPlant;

/**
 * @brief Concrete command for watering a plant.
 *
 * Encapsulates the operation of applying water to a specific plant,
 * storing necessary state to undo the operation if needed.
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
