#ifndef Dead_h
#define Dead_h

#include "MaturityState.h"
#include "../prototype/LivingPlant.h"

class LivingPlant; // Forward declaration

/**
 * @brief Represents the Dead state of a plant (terminal state)
 * 
 * Age range: ≥ 120 days or when health reaches 0
 * Health: 0
 * Water: 0
 * Sun exposure: 0
 * Baseline water usage: 0
 */
class Dead : public MaturityState {
public:
    /**
     * @brief Handles daily growth in Dead state
     * 
     * No changes occur in this terminal state.
     * All plant attributes remain at 0.
     * 
     * @param plant The plant instance
     */
    void grow(LivingPlant* plant);
       /**
     * @brief Returns the image path for the Seed state
     *
     * @param plant Pointer to the LivingPlant
     * @return Image file path as a string
     */
    std::string getImagePath(LivingPlant *plant);
    
    /**
     * @brief Returns the identifier for the Dead state
     * 
     * @return Integer identifier for the state
     */
    static const int getID() { return 3; }
};
#endif /* Dead_h */
