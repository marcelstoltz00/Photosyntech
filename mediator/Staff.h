#ifndef Staff_h
#define Staff_h

#include "User.h"
#include "../observer/Observer.h"
#include "../composite/PlantGroup.h"
#include "../prototype/LivingPlant.h"


/**
 * @brief Concrete colleague representing staff in the mediator and observer patterns.
 *
 * Staff members interact with customers through mediators and observe plant groups
 * for care notifications. Implements both User (for mediated communication) and
 * Observer (for receiving plant health updates) interfaces.
 */
class Staff : public User, public Observer
{
	public:
		/**
		 * @brief Assists customers with plant care suggestions via the suggestion floor mediator.
		 */
		void assistSuggestion();

		/**
		 * @brief Assists customers with purchase transactions via the sales floor mediator.
		 * @param plants Pointer to the PlantGroup being purchased.
		 */
		void assistPurchases(PlantGroup* plants);

		/**
		 * @brief Receives notification that a plant needs water.
		 * @param plant Pointer to the LivingPlant requiring water.
		 */
		void getWaterUpdate(LivingPlant* plant);

		/**
		 * @brief Receives notification that a plant needs sunlight.
		 * @param plant Pointer to the LivingPlant requiring sun exposure.
		 */
		void getSunUpdate(LivingPlant* plant);

		/**
		 * @brief Receives notification that a plant's state has been updated.
		 * @param plant Pointer to the LivingPlant with updated state.
		 */
		void getStateUpdate(LivingPlant* plant);
};

#endif
