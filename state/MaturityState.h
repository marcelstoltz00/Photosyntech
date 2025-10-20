#ifndef MaturityState_h
#define MaturityState_h

#include "../prototype/LivingPlant.h"

/**
 * @brief Abstract base class for plant maturity states in the State pattern.
 *
 * Defines the interface for encapsulating behavior associated with a particular
 * maturity stage. Each concrete state defines its own growth rate and age boundaries,
 * allowing plants to change behavior based on their current maturity level.
 * States include: Seed, Vegetative, Mature, and Dead.
 *
 * **System Role:**
 * This abstract class defines the contract for all plant lifecycle states.
 * LivingPlant delegates lifecycle behavior to current state via grow() method.
 * Each state encapsulates growth rates, age boundaries, and transition logic.
 * State transitions trigger observer notifications for staff monitoring.
 *
 * **Pattern Role:** Abstract State (defines behavior interface for each state)
 *
 * **Related Patterns:**
 * - LivingPlant: Context that delegates to current state
 * - Observer: State transitions trigger notifications
 * - Flyweight: State instances are shared across plants
 * - Composite: State affects all plants in groups uniformly
 * - Decorator: State affects decorated properties (e.g., mature plant pricing)
 *
 * **System Interactions:**
 * - LivingPlant calls grow(plant) on current state
 * - State checks age, applies growth, triggers transitions
 * - State transitions notify observers (e.g., maturity milestone reached)
 * - Each state maintains min/max age and growth rate
 * - grow() method responsible for state transition logic
 *
 * @see LivingPlant (context using state pattern)
 * @see Concrete states: Seed, Vegetative, Mature, Dead
 */
class MaturityState
{
	protected:
		double growthRate;
		int minAge;
		int maxAge;

	public:
		/**
		 * @brief Advances the plant's growth based on this maturity state.
		 *
		 * Applies growth calculations and may trigger a state transition
		 * if the plant's age exceeds the state's age boundaries.
		 *
		 * @param plant Pointer to the LivingPlant that is growing.
		 */
		virtual void grow(LivingPlant* plant) = 0;

		/**
		 * @brief Gets the unique identifier for this state type.
		 * @return Integer representing the state ID.
		 */
		virtual int getID() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~MaturityState() {}
};

#endif
