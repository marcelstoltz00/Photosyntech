#ifndef __PurchasePlantCommand_h__
#define __PurchasePlantCommand_h__

#include "Command.h"

class PlantComponent;
class Singleton;

/**
 * @brief Concrete command for purchasing a plant.
 *
 * Encapsulates the transaction logic for purchasing plants, including
 * removing from inventory and processing payment. Stores transaction
 * details for potential undo operations.
 */
class PurchasePlantCommand : public Command
{
	public:
		/**
		 * @brief Executes the purchase transaction.
		 */
		void execute();

		/**
		 * @brief Undoes the purchase transaction.
		 */
		void undo();
};

#endif
