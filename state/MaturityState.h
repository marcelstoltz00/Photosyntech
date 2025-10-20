
#ifndef MaturityState_h
#define MaturityState_h

#include "../prototype/LivingPlant.h"

class LivingPlant; // Forward declaration

/**
 * @brief Abstract base class for plant maturity states
 *
 * Defines the interface for all concrete maturity states.
 * Each state implements specific behavior for plant growth and transitions
 * according to defined parameters.
 */
class MaturityState
{
public:
	enum class Season
	{
		SPRING,
		SUMMER,
		AUTUMN,
		WINTER
	};
	/**
	 * @brief Handles the daily growth of the plant
	 *
	 * Increments age, applies water usage based on season,
	 * updates health if conditions are met, and checks for state transitions.
	 *
	 * @param plant The plant instance to update
	 */
	virtual void grow(LivingPlant *plant) = 0;

	/**
	 * @brief Virtual destructor
	 */
	virtual ~MaturityState() = default;

	/**
	 * @brief Returns the identifier for this state type
	 *
	 * @return Integer identifier for the state
	 */
	static const int getID() { return -1; }
};
#endif /* MaturityState_h */