#ifndef CHERRYBLOSSOMBUILDER_H
#define CHERRYBLOSSOMBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Cherry Blossom trees.
 *
 * Implements the Builder interface to construct Cherry Blossom trees with specific attributes:
 * - Base Type: Tree
 * - Sun Strategy: MidSun
 * - Water Strategy: MidWater
 * - Decorators: Large Flowers, Small Leaves, Large Stem, No Thorns
 *
 * @see Builder
 * @see Tree
 */
class CherryBlossomBuilder : public Builder
{
private:
    LivingPlant *plant;

public:
    /**
     * @brief Constructor for CherryBlossomBuilder.
     */
    CherryBlossomBuilder();

    /**
     * @brief Creates a new Tree object as the base for the Cherry Blossom.
     */
    void createObject() override;

    /**
     * @brief Assigns MidWater strategy to the Cherry Blossom tree.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns MidSun strategy to the Cherry Blossom tree.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Cherry Blossom tree.
     */
    void assignMaturityState() override;

    /**
     * @brief Sets up the initial health, water, and sun levels for the Cherry Blossom tree.
     */
    void setUp();

    /**
     * @brief Adds decorators to the LivingPlant.
     */
    virtual void addDecorators() = 0;
    /**
     * @brief Returns the fully constructed Cherry Blossom tree.
     * @return Pointer to the constructed Cherry Blossom tree.
     */
    LivingPlant *getResult() override;

    /**
     * @brief Destructor for CherryBlossomBuilder.
     */
    ~CherryBlossomBuilder();
};

#endif // CHERRYBLOSSOMBUILDER_H