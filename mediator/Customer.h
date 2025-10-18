#ifndef Customer_h
#define Customer_h

#include "User.h"
#include "../composite/PlantGroup.h"
#include "../composite/PlantComponent.h"


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
		PlantGroup* basket;

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
		 * @param plant Pointer to the PlantComponent to add.
		 */
		void addPlant(PlantComponent* plant);

		/**
		 * @brief Performs a customer operation.
		 */
		void operation();
};

#endif
