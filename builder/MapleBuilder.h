#ifndef MAPLEBUILDER_H
#define MAPLEBUILDER_H

#include "Builder.h"

/**
 * @brief Concrete builder for Maple trees.
 *
 * Implements the Builder interface to construct Maple trees with specific attributes:
 * - Base Type: Tree
 * - Sun Strategy: MidSun
 * - Water Strategy: MidWater
 * - Decorators: No Flowers, Large Leaves, Large Stem, No Thorns
 *
 * @see Builder
 * @see Tree
 */
class MapleBuilder : public Builder
{
private:
    LivingPlant *plant;

public:
    /**
     * @brief Constructor for MapleBuilder.
     */
    MapleBuilder();

    /**
     * @brief Creates a new Tree object as the base for the Maple.
     */
    void createObject() override;

    /**
     * @brief Assigns MidWater strategy to the Maple tree.
     */
    void assignWaterStrategy() override;

    /**
     * @brief Assigns MidSun strategy to the Maple tree.
     */
    void assignSunStrategy() override;

    /**
     * @brief Assigns initial Seed state to the Maple tree.
     */
    void assignMaturityState() override;
    /**
     * @brief Adds decorators to the LivingPlant.
     */
    virtual void addDecorators() = 0;
    /**
     * @brief Returns the fully constructed Maple tree.
     * @return Pointer to the constructed Maple tree.
     */
    LivingPlant *getResult() override;

    /**
     * @brief Destructor for MapleBuilder.
     */
    ~MapleBuilder();
};

#endif // MAPLEBUILDER_H