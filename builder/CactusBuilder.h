#ifndef CACTUSBUILDER_H
#define CACTUSBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Cactus plants.
 *
 * Implements the Builder interface to construct Cactus plants with specific attributes:
 * - Base Type: Succulent
 * - Sun Strategy: HighSun
 * - Water Strategy: LowWater
 * - Decorators: Small Flowers, No Leaves, Large Stem, Thorns
 *
 * @see Builder
 * @see Succulent
 */
class CactusBuilder : public Builder
{
private:
    LivingPlant *plant = nullptr;
    PlantAttributes *season = nullptr;

public:
    /**
     * @brief Constructor for CactusBuilder.
     */
    CactusBuilder();

    /**
     * @brief Creates a new Succulent object as the base for the Cactus.
     */
    void createObject() override;

    /**
     * @brief Assigns LowWater strategy to the Cactus plant.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns HighSun strategy to the Cactus plant.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Cactus plant.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Cactus plant.
     */
    void setUp() override;
    /**
     * @brief Adds decorators to thePlantComponent.
     */
    virtual void addDecorators() = 0;
    /**
     * @brief Returns the fully constructed Cactus plant.
     * @return Pointer to the constructed Cactus plant.
     */
    PlantComponent *getResult() override;

    /**
     * @brief Destructor for CactusBuilder.
     */
    ~CactusBuilder();
};

#endif // CACTUSBUILDER_H