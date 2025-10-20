#ifndef Seed_h
#define Seed_h

#include "MaturityState.h"

/**
 * @brief Concrete state representing the Seed stage of plant maturity.
 *
 * The initial state in a plant's lifecycle with specific growth characteristics.
 * Plants in this state have the highest growth rate and transition to Vegetative
 * state when they reach the appropriate age.
 *
 * **System Role:**
 * Initial lifecycle state for all new plants. Encapsulates seed-specific growth
 * with high growth rate and rapid development. grow() checks for Vegetative transition.
 *
 * **Pattern Role:** Concrete State (implements seed lifecycle behavior)
 *
 * **Related Patterns:**
 * - MaturityState: Implements abstract state interface
 * - LivingPlant: Uses this state initially
 * - Observer: Transition to Vegetative triggers notifications
 *
 * **System Interactions:**
 * - Builder initializes plants in Seed state
 * - grow() applies high growth rate and checks transition
 * - When age exceeds maxAge, transitions to Vegetative
 * - Observers notified on transition to Vegetative
 *
 * @see MaturityState (base class)
 * @see Vegetative (next state after transition)
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
		 * @param plant Pointer to the LivingPlant that is growing.
		 */
		void grow(LivingPlant* plant);

		/**
		 * @brief Gets the unique identifier for the Seed state.
		 * @return Integer ID representing the Seed state.
		 */
		int getID();
};

#endif
