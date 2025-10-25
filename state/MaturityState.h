
#ifndef MaturityState_h
#define MaturityState_h

#include "../prototype/LivingPlant.h"

class LivingPlant; // Forward declaration

/**
 * @brief Enum for identifying maturity state types at runtime.
 *
 * Provides O(1) type identification without RTTI/dynamic_cast overhead.
 * Follows the same pattern as ComponentType enum in PlantComponent.
 * Used by iterators, mementos, and other components needing state identification.
 */
enum class MaturityStateType {
	SEED = 0,       ///< Seed state (age 0-6)
	VEGETATIVE = 1, ///< Vegetative state (age 7-14)
	MATURE = 2,     ///< Mature state (age 15+)
	DEAD = 3        ///< Dead state (end of lifecycle)
};

/**
 * @brief Abstract base class for plant maturity states
 *
 * Defines the interface for all concrete maturity states.
 * Each state implements specific behavior for plant growth and transitions
 * according to defined parameters.
 *
 * **Pattern Role:** State (defines interface for plant lifecycle states)
 *
 * **Related Patterns:**
 * - Concrete States: Seed, Vegetative, Mature, Dead
 * - LivingPlant: Context that delegates to maturity state
 * - Strategy: Similar pattern for water/sun care
 * - Flyweight: State instances are shared (flyweight objects)
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
	 * @brief Returns the type of this maturity state (for O(1) type identification).
	 *
	 * Provides efficient runtime type identification without RTTI overhead.
	 * Used by mementos, iterators, and other components needing type checks.
	 *
	 * @return MaturityStateType enum value identifying this state's type
	 */
	virtual MaturityStateType getStateType() const = 0;

	/**
	 * @brief Virtual destructor
	 */
	virtual ~MaturityState() = default;

	/**
	 * @brief Returns the identifier for this state type
	 *
	 * @return Integer identifier for the state
	 */
	static const int getID();
};
#endif /* MaturityState_h */