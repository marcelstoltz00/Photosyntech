#ifndef LAVENDERBUILDER_H
#define LAVENDERBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Lavender plants.
 *
 * Implements the Builder interface to construct Lavender plants with specific attributes:
 * - Base Type: Herb
 * - Sun Strategy: HighSun
 * - Water Strategy: LowWater
 * - Decorators: Small Flowers, Small Leaves, Medium Stem, No Thorns
 *
 * @see Builder
 * @see Herb
 */
class LavenderBuilder : public Builder
{
private:
    LivingPlant *plant;

public:
    /**
     * @brief Constructor for LavenderBuilder.
     */
    LavenderBuilder();

    /**
     * @brief Creates a new Herb object as the base for the Lavender.
     */
    void createObject() override;

    /**
     * @brief Assigns LowWater strategy to the Lavender plant.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns HighSun strategy to the Lavender plant.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Lavender plant.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Lavender plant.
     */
    void setUp();
    /**
     * @brief Adds decorators to the LivingPlant.
     */
    virtual void addDecorators() = 0;
    /**
     * @brief Returns the fully constructed Lavender plant.
     * @return Pointer to the constructed Lavender plant.
     */
    LivingPlant *getResult() override;

    /**
     * @brief Destructor for LavenderBuilder.
     */
    ~LavenderBuilder();
};

#endif // LAVENDERBUILDER_H