#ifndef __Customer_h__
#define __Customer_h__

#include "User.h"

class PlantGroup;
class PlantComponent;

/**
 * @brief Concrete colleague representing a customer in the mediator pattern.
 *
 * Interacts with staff through mediators (sales floor, suggestion floor)
 * instead of direct coupling. Maintains a shopping basket and can request
 * suggestions or make purchases through coordinated interactions.
 */
class Customer : public User
{
	private:
		PlantGroup* _basket;

	public:
		/**
		 * @brief Requests plant care suggestions from staff via the mediator.
		 */
		void askForSuggestion();

		/**
		 * @brief Initiates plant purchase transaction via the sales floor mediator.
		 */
		void purchasePlants();

		/**
		 * @brief Adds a plant to the customer's shopping basket.
		 * @param aPlant Pointer to the PlantComponent to add.
		 */
		void addPlant(PlantComponent* aPlant);

		/**
		 * @brief Performs a customer operation.
		 */
		void operation();
};

#endif
