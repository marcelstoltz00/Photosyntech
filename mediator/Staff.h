#ifndef __Staff_h__
#define __Staff_h__

#include "User.h"
#include "../observer/Observer.h"

class PlantGroup;
class LivingPlant;

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
		 * @param aPlants Pointer to the PlantGroup being purchased.
		 */
		void assistPurchases(PlantGroup* aPlants);

		/**
		 * @brief Receives notification that a plant needs water.
		 * @param aPlant Pointer to the LivingPlant requiring water.
		 */
		void getWaterUpdate(LivingPlant* aPlant);

		/**
		 * @brief Receives notification that a plant needs sunlight.
		 * @param aPlant Pointer to the LivingPlant requiring sun exposure.
		 */
		void getSunUpdate(LivingPlant* aPlant);

		/**
		 * @brief Receives notification that a plant's state has changed.
		 * @param aPlant Pointer to the LivingPlant with updated state.
		 */
		void getStateUpdate(LivingPlant* aPlant);
};

#endif
