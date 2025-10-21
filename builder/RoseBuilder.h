#ifndef ROSEBUILDER_H
#define ROSEBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Rose plants.
 *
 * Implements the Builder interface to construct Rose plants with specific attributes:
 * - Base Type: Shrub
 * - Sun Strategy: MidSun
 * - Water Strategy: MidWater
 * - Decorators: Large Flowers, Small Leaves, Medium Stem, Thorns
 *
 * @see Builder
 * @see Shrub
 */
class RoseBuilder : public Builder
{
private:
    LivingPlant *plant;

public:
    /**
     * @brief Constructor for RoseBuilder.
     */
    RoseBuilder();

    /**
     * @brief Creates a new Shrub object as the base for the Rose.
     */
    void createObject() override;

    /**
     * @brief Assigns MidWater strategy to the Rose plant.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns MidSun strategy to the Rose plant.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Rose plant.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Rose plant.
     */
    void setUp()override;

    /**
     * @brief Adds decorators to the LivingPlant.
     */
    virtual void addDecorators() = 0;
    /**
     * @brief Returns the fully constructed Rose plant.
     * @return Pointer to the constructed Rose plant.
     */
    LivingPlant *getResult() override;

    /**
     * @brief Destructor for RoseBuilder.
     */
    ~RoseBuilder();
};

#endif // ROSEBUILDER_H