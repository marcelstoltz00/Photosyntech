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
