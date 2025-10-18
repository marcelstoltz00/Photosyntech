#ifndef Dead_h
#define Dead_h

#include "MaturityState.h"

/**
 * @brief Concrete state representing the Dead stage of plant maturity.
 *
 * The final state in a plant's lifecycle. Plants in this state no longer
 * grow and cannot transition to any other state. This represents the end
 * of the plant's productive life.
 *
 * **System Role:**
 * Terminal lifecycle state. grow() is no-op. Signals need for inventory replacement.
 * Dead plants retained in inventory temporarily until manual removal/restocking.
 * Triggers staff notifications for inventory replenishment.
 *
 * **Pattern Role:** Concrete State (implements dead/terminal behavior)
 *
 * **Related Patterns:**
 * - MaturityState: Implements abstract state interface
 * - LivingPlant: Final state for lifecycle context
 * - Observer: Dead state triggers urgent replacement notifications
 * - Command: Staff initiates removal via command
 *
 * **System Interactions:**
 * - Plants transition to Dead from Mature beyond maxAge
 * - grow() is no-op (no further growth or transitions)
 * - Observer notifications alert staff of dead plants
 * - Staff removes dead plants via command operations
 * - Inventory cleared of dead plants for restocking
 *
 * @see MaturityState (base class)
 * @see Mature (previous state)
 */
class Dead : public MaturityState
{
	public:
		/**
		 * @brief No-op growth for dead plants.
		 *
		 * Dead plants do not grow or transition to other states.
		 *
		 * @param plant Pointer to the LivingPlant (unused in this state).
		 */
		void grow(LivingPlant* plant);

		/**
		 * @brief Gets the unique identifier for the Dead state.
		 * @return Integer ID representing the Dead state.
		 */
		int getID();
};

#endif
