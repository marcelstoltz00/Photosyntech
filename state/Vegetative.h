#ifndef Vegetative_h
#define Vegetative_h

#include "MaturityState.h"

/**
 * @brief Concrete state representing the Vegetative stage of plant maturity.
 *
 * The active growth phase following the Seed state. Plants in this state
 * continue growing and developing, transitioning to Mature state when
 * they reach the appropriate age.
 *
 * **System Role:**
 * Active growth phase with moderate growth rate. Encapsulates vegetative-specific
 * development. grow() checks for Mature transition. Most plants spend extended time here.
 *
 * **Pattern Role:** Concrete State (implements vegetative lifecycle behavior)
 *
 * **Related Patterns:**
 * - MaturityState: Implements abstract state interface
 * - LivingPlant: Context for vegetative phase
 * - Observer: Transition to Mature triggers notifications
 *
 * **System Interactions:**
 * - Plants transition to Vegetative from Seed
 * - grow() applies moderate growth rate
 * - When age exceeds maxAge, transitions to Mature
 * - Mature transition signals flowering/fruiting readiness
 * - Observers notified on maturity achievement
 *
 * @see MaturityState (base class)
 * @see Seed (previous state)
 * @see Mature (next state after transition)
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
		 * @param plant Pointer to the LivingPlant that is growing.
		 */
		void grow(LivingPlant* plant);

		/**
		 * @brief Gets the unique identifier for the Vegetative state.
		 * @return Integer ID representing the Vegetative state.
		 */
		int getID();
};

#endif
