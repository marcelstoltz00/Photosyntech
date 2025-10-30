#ifndef Customer_h
#define Customer_h

#include "User.h"
#include "../composite/PlantGroup.h"  // Include PlantGroup definition


/**
 * @brief Concrete colleague representing a customer in the mediator pattern.
 *
 * Interacts with staff through mediators (sales floor, suggestion floor)
 * instead of direct coupling. Maintains a shopping basket and can request
 * suggestions or make purchases through coordinated interactions.
 *
 * **System Role:**
 * Concrete mediated participant representing customers. Maintains shopping basket.
 * Interacts with staff exclusively through mediators (SalesFloor, SuggestionFloor).
 * Primary actor in purchase and advisory interactions.
 *
 * **Pattern Role:** Concrete Colleague (customer participant)
 *
 * **Related Patterns:**
 * - User: Base class providing mediator access
 * - Mediator: Routes customer requests through floors
 * - Composite: Basket contains PlantComponent hierarchy
 * - Observer: May receive recommendations based on monitoring
 *
 * **System Interactions:**
 * - askForSuggestion(): Routes through SuggestionFloor
 * - purchasePlants(): Coordinates sale through SalesFloor
 * - addPlant(): Manages shopping basket contents
 * - operation(): Executes customer-specific actions
 *
 * @see User (base colleague class)
 * @see Mediator (coordination infrastructure)
 * @see SalesFloor, SuggestionFloor (mediators)
 */
class PlantComponent;  // Forward declaration to prevent circular dependency
class Customer : public User
{
	private:
		PlantGroup* basket;

	public:
		Customer();
		Customer(std::string name);
    	virtual ~Customer();
		/**
		 * @brief Requests plant care suggestions from staff via the mediator.
		 */
		string askForSuggestion();

		/**
		 * @brief Initiates plant purchase transaction via the sales floor mediator.
		 */
		string purchasePlants();

		/**
		 * @brief Adds a plant to the customer's shopping basket.
		 * @param plant Pointer to the PlantComponent to add.
		 */
		void addPlant(PlantComponent* plant);


		PlantGroup* getBasket() const;
   		void clearBasket();
		
};

#endif
