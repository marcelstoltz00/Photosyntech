#ifndef __Dead_h__
#define __Dead_h__

#include "MaturityState.h"

class LivingPlant;

/**
 * @brief Concrete state representing the Dead stage of plant maturity.
 *
 * The final state in a plant's lifecycle. Plants in this state no longer
 * grow and cannot transition to any other state. This represents the end
 * of the plant's productive life.
 */
class Dead : public MaturityState
{
	public:
		/**
		 * @brief No-op growth for dead plants.
		 *
		 * Dead plants do not grow or transition to other states.
		 *
		 * @param aPlant Pointer to the LivingPlant (unused in this state).
		 */
		void grow(LivingPlant* aPlant);

		/**
		 * @brief Gets the unique identifier for the Dead state.
		 * @return Integer ID representing the Dead state.
		 */
		int getID();
};

#endif
