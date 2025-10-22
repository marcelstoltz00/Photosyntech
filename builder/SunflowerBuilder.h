#ifndef SUNFLOWERBUILDER_H
#define SUNFLOWERBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Sunflower plants.
 *
 * Implements the Builder interface to construct Sunflower plants with specific attributes:
 * - Base Type: Herb
 * - Sun Strategy: HighSun
 * - Water Strategy: MidWater
 * - Decorators: Large Flowers, Large Leaves, Large Stem, No Thorns
 *
 * @see Builder
 * @see Herb
 */
class SunflowerBuilder : public Builder
{
private:
    LivingPlant *plant = nullptr;
    PlantAttributes *season = nullptr;

public:
    /**
     * @brief Constructor for SunflowerBuilder.
     */
    SunflowerBuilder();

    /**
     * @brief Creates a new Herb object as the base for the Sunflower.
     */
    void createObject() override;

    /**
     * @brief Assigns MidWater strategy to the Sunflower plant.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns HighSun strategy to the Sunflower plant.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Sunflower plant.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Sunflower plant.
     */
    void setUp() override;
    /**
     * @brief Adds decorators to the LivingPlant.
     */
    virtual void addDecorators() = 0;
    /**
     * @brief Returns the fully constructed Sunflower plant.
     * @return Pointer to the constructed Sunflower plant.
     */
   PlantComponent *getResult() override;

    /**
     * @brief Destructor for SunflowerBuilder.
     */
    ~SunflowerBuilder();
};

#endif // SUNFLOWERBUILDER_H