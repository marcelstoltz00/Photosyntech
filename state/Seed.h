#ifndef Seed_h
#define Seed_h

#include "MaturityState.h"

class LivingPlant; 

/**
 * @brief Represents the Seed state of a plant
 * 
 * Age range: 0-6 days
 * Health range: 30-100
 * Water range: 40-100
 * Sun exposure range: 20-100
 * Baseline water usage: 6 units/day
 * Health gain when conditions met: +4 units/day
 */

class Seed : public MaturityState {
public:
    /**
     * @brief Handles daily growth in Seed state
     *
     * Process:
     * 1. Increment age by 1 day
     * 2. Apply water usage (6 units * season multiplier)
     * 3. If water ≥ 40 and sun ≥ 20, increase health by 4
     * 4. Check transition to Vegetative if:
     *    - age ≥ 7 AND health ≥ 50 AND water ≥ 50 AND sun ≥ 30
     *    - On transition: water = 25, health = max(health,50), sun = 50
     *
     * @param plant The plant to update
     */
    void grow(LivingPlant* plant);

    /**
     * @brief Returns the type of this maturity state.
     * @return MaturityStateType::SEED
     */
    MaturityStateType getStateType() const override {
        return MaturityStateType::SEED;
    }

    /**
     * @brief Returns the identifier for the Seed state
     *
     * @return Integer identifier for the state
     */
    static const int getID() { return 0; }
};
#endif /* Seed_h */
