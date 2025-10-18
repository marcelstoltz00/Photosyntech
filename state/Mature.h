#ifndef Mature_h
#define Mature_h

#include "MaturityState.h"

/**
 * @brief Concrete state representing the Mature stage of plant maturity.
 *
 * The fully developed state where plants have reached their optimal growth.
 * Plants in this state have reduced growth rates and will eventually
 * transition to the Dead state as they age beyond their lifecycle.
 *
 * **System Role:**
 * Peak plant value and characteristics. Encapsulates mature-specific behavior
 * with reduced growth rate. grow() checks for Dead transition. Mature plants command
 * premium pricing due to full development and flowering/fruiting capability.
 *
 * **Pattern Role:** Concrete State (implements mature lifecycle behavior)
 *
 * **Related Patterns:**
 * - MaturityState: Implements abstract state interface
 * - LivingPlant: Context for mature phase
 * - Decorator: Mature state increases decorated properties value
 * - Observer: Transition to Dead triggers urgent notifications
 *
 * **System Interactions:**
 * - Plants transition to Mature from Vegetative
 * - grow() applies reduced growth rate (stabilization)
 * - Maximum pricing value reached in Mature state
 * - When age exceeds maxAge, transitions to Dead
 * - Dead transition triggers replacement notifications to staff
 *
 * @see MaturityState (base class)
 * @see Vegetative (previous state)
 * @see Dead (next state after transition)
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
