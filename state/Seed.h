#ifndef __Seed_h__
#define __Seed_h__

#include "MaturityState.h"

class LivingPlant;

/**
 * @brief Concrete state representing the Seed stage of plant maturity.
 *
 * The initial state in a plant's lifecycle with specific growth characteristics.
 * Plants in this state have the highest growth rate and transition to Vegetative
 * state when they reach the appropriate age.
 */
class Seed : public MaturityState
{
	public:
		/**
		 * @brief Advances the plant's growth while in the Seed state.
		 *
		 * Applies seed-specific growth calculations and checks for transition
		 * to the Vegetative state based on the plant's age.
		 *
		 * @param aPlant Pointer to the LivingPlant that is growing.
		 */
		void grow(LivingPlant* aPlant);

		/**
		 * @brief Gets the unique identifier for the Seed state.
		 * @return Integer ID representing the Seed state.
		 */
		int getID();
};

#endif
