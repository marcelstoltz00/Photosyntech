#ifndef Vegetative_h
#define Vegetative_h

#include "MaturityState.h"


class LivingPlant; // Forward declaration

/**
 * @brief Represents the Vegetative state of a plant
 * 
 * Age range: 7-29 days
 * Health range: 40-100
 * Water range: 25-100
 * Sun exposure range: 40-100
 * Baseline water usage: 10 units/day
 * Health gain when conditions met: +3 units/day
 */
class Vegetative : public MaturityState {
public:
    /**
     * @brief Handles daily growth in Vegetative state
     *
     * Process:
     * 1. Increment age by 1 day
     * 2. Apply water usage (10 units * season multiplier)
     * 3. If water ≥ 30 and sun ≥ 40, increase health by 3
     * 4. Check transition to Mature if:
     *    - age ≥ 30 AND health ≥ 60 AND water ≥ 40 AND sun ≥ 50
     *    - On transition: water = 40, health = max(health,60), sun = 60
     *
     * @param plant The plant to update
     */
    void grow(LivingPlant* plant) ;

    /**
     * @brief Returns the type of this maturity state.
     * @return MaturityStateType::VEGETATIVE
     */
    MaturityStateType getStateType() const override {
        return MaturityStateType::VEGETATIVE;
    }

    /**
     * @brief Returns the identifier for the Vegetative state
     *
     * @return Integer identifier for the state
     */
    static const int getID() { return 1; }
};
#endif /* Vegetative_h */
