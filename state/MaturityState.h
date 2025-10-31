
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
     * @brief Returns the image path for the Seed state
     *
     * @param plant Pointer to the LivingPlant
     * @return Image file path as a string
     */
    virtual std::string getImagePath(LivingPlant *plant) = 0;

	/**
	 * @brief Returns the identifier for this state type
	 *
	 * @return Integer identifier for the state
	 */
	static const int getID();

	virtual const string getName(){return "Base State";};
};
#endif /* MaturityState_h */