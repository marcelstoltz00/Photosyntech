#ifndef Mature_h
#define Mature_h

#include "MaturityState.h"
#include "../prototype/LivingPlant.h"

class LivingPlant; // Forward declaration

/**
 * @brief Represents the Mature state of a plant
 * 
 * Age range: 30-119 days
 * Health range: 30-100
 * Water range: 30-100
 * Sun exposure range: 40-100
 * Baseline water usage: 8 units/day
 * Health gain when conditions met: +1 unit/day
 */
class Mature : public MaturityState {
public:
    /**
     * @brief Handles daily growth in Mature state
     *
     * Process:
     * 1. Increment age by 1 day
     * 2. Apply water usage (8 units * season multiplier)
     * 3. If water ≥ 30 and sun ≥ 40, increase health by 1
     * 4. Check transition to Dead if:
     *    - age ≥ 120 OR health ≤ 0
     *    - On transition: health = 0, water = 0, sun = 0
     *
     * @param plant The plant to update
     */
    void grow(LivingPlant* plant) ;

    /**
     * @brief Returns the type of this maturity state.
     * @return MaturityStateType::MATURE
     */
    MaturityStateType getStateType() const override {
        return MaturityStateType::MATURE;
    }

    /**
     * @brief Returns the identifier for the Mature state
     *
     * @return Integer identifier for the state
     */
    static const int getID() { return 2; }
};
#endif /* Mature_h */
