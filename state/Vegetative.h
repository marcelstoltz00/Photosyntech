#ifndef __Vegetative_h__
#define __Vegetative_h__

#include "MaturityState.h"

class LivingPlant;

/**
 * @brief Concrete state representing the Vegetative stage of plant maturity.
 *
 * The active growth phase following the Seed state. Plants in this state
 * continue growing and developing, transitioning to Mature state when
 * they reach the appropriate age.
 */
class Vegetative : public MaturityState
{
	public:
		/**
		 * @brief Advances the plant's growth while in the Vegetative state.
		 *
		 * Applies vegetative-specific growth calculations and checks for
		 * transition to the Mature state based on the plant's age.
		 *
		 * @param aPlant Pointer to the LivingPlant that is growing.
		 */
		void grow(LivingPlant* aPlant);

		/**
		 * @brief Gets the unique identifier for the Vegetative state.
		 * @return Integer ID representing the Vegetative state.
		 */
		int getID();
};

#endif
