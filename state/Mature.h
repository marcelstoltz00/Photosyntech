#ifndef Mature_h
#define Mature_h

#include "MaturityState.h"

/**
 * @brief Concrete state representing the Mature stage of plant maturity.
 *
 * The fully developed state where plants have reached their optimal growth.
 * Plants in this state have reduced growth rates and will eventually
 * transition to the Dead state as they age beyond their lifecycle.
 */
class Mature : public MaturityState
{
	public:
		/**
		 * @brief Advances the plant's growth while in the Mature state.
		 *
		 * Applies mature-specific growth calculations and checks for
		 * transition to the Dead state based on the plant's age.
		 *
		 * @param plant Pointer to the LivingPlant that is growing.
		 */
		void grow(LivingPlant* plant);

		/**
		 * @brief Gets the unique identifier for the Mature state.
		 * @return Integer ID representing the Mature state.
		 */
		int getID();
};

#endif
