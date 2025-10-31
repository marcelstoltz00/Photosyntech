#ifndef Staff_h
#define Staff_h

#include "User.h"
#include "../observer/Observer.h"
#include "../composite/PlantGroup.h"
#include "../prototype/LivingPlant.h"

#include<string>
/**
 * @brief Concrete colleague representing staff in the mediator and observer patterns.
 *
 * Staff members interact with customers through mediators and observe plant groups
 * for care notifications. Implements both User (for mediated communication) and
 * Observer (for receiving plant health updates) interfaces.
 *
 * **System Role:**
 * Core operational actor in the system. Participates in two key roles:
 * 1. Mediator colleague: Handles customer transactions via sales/suggestion floors
 * 2. Observer: Monitors plant health and responds to care notifications
 * Central to both customer service and plant care functions.
 *
 * **Pattern Role:** Concrete Colleague (implements mediated participant)
 *
 * **Related Patterns:**
 * - Mediator: Participates in sales and suggestion floor coordination
 * - Observer: Monitors plant groups and responds to notifications
 * - Command: Executes care commands (watering, care routines)
 * - User: Base class providing mediated communication interface
 *
 * **System Interactions:**
 * - assistSuggestion() coordinates with SuggestionFloor for recommendations
 * - assistPurchases() coordinates with SalesFloor for transactions
 * - getWaterUpdate/getSunUpdate/getStateUpdate: Receives plant monitoring notifications
 * - Executes care commands in response to plant needs
 * - Provides customer service and inventory management
 *
 * @see Mediator (coordination infrastructure)
 * @see Observer (plant monitoring interface)
 * @see User (mediated communication base)
 */
class Staff : public User, public Observer
{
	public:
		Staff();
		Staff(std::string name);
		/**
		 * @brief Assists customers with plant care suggestions via the suggestion floor mediator.
		 */
		string assistSuggestion();

		/**
		 * @brief Assists customers with purchase transactions via the sales floor mediator.
		 * @param plants Pointer to the PlantGroup being purchased.
		 */
		string assistPurchases(PlantGroup* plants);

		/**
		 * @brief Receives notification that a plant needs water.
		 * @param plant Pointer to the LivingPlant requiring water.
		 */
		void getWaterUpdate(PlantComponent* plant);

		/**
		 * @brief Receives notification that a plant needs sunlight.
		 * @param plant Pointer to the LivingPlant requiring sun exposure.
		 */
		void getSunUpdate(PlantComponent* plant);

		/**
		 * @brief Receives notification that a plant's state has been updated.
		 * @param plant Pointer to the LivingPlant with updated state.
		 */
		void getStateUpdate(PlantComponent* plant);

		virtual string getNameObserver() {return this->getName();};
};

#endif
