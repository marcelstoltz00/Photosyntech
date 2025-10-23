#ifndef JADEPLANTBUILDER_H
#define JADEPLANTBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Jade plants.
 *
 * Implements the Builder interface to construct Jade plants with specific attributes:
 * - Base Type: Succulent
 * - Sun Strategy: MidSun
 * - Water Strategy: LowWater
 * - Decorators: Small Flowers, Small Leaves, Medium Stem, No Thorns
 *
 * @see Builder
 * @see Succulent
 */
class JadePlantBuilder : public Builder
{
private:
	LivingPlant *plant = nullptr;


public:
    /**
     * @brief Constructor for JadePlantBuilder.
     */
    JadePlantBuilder();

    /**
     * @brief Creates a new Succulent object as the base for the Jade plant.
     */
    void createObject() override;

    /**
     * @brief Assigns LowWater strategy to the Jade plant.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns MidSun strategy to the Jade plant.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Jade plant.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Jade plant.
     */
    void setUp() override;

    /**
     * @brief Adds decorators to the LivingPlant.
     */
    void addDecorators() override;
    /**
     * @brief Returns the fully constructed Jade plant.
     * @return Pointer to the constructed Jade plant.
     */
    PlantComponent *getResult() override;

    /**
     * @brief Destructor for JadePlantBuilder.
     */
    ~JadePlantBuilder();
};

#endif // JADEPLANTBUILDER_H