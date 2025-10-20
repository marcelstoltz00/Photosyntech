#ifndef MidWater_h
#define MidWater_h

#include "WaterStrategy.h"

/**
 * @brief Concrete strategy for moderate watering.
 *
 * Implements a watering strategy with medium water amounts and regular
 * watering schedules, suitable for most common houseplants.
 *
 * **System Role:**
 * Most versatile watering strategy for general-purpose plants (Roses, Shrubs).
 * Applied via Builder during construction. Default strategy for many species.
 * Shared via flyweight factory across all moderate-water plants.
 *
 * **Pattern Role:** Concrete Strategy (implements moderate-water algorithm)
 *
 * **Related Patterns:**
 * - WaterStrategy: Implements abstract interface
 * - LivingPlant: Context using this strategy
 * - Builder: Assigns to general-purpose plant types
 * - Singleton: Cached by flyweight factory
 *
 * **System Interactions:**
 * - Builder assigns to mid-care plant species
 * - water() applies balanced water amount directly to plant object
 * - getID() returns consistent identifier for caching
 * - Most commonly shared strategy across plant types
 *
 * @see WaterStrategy (abstract interface)
 * @see LivingPlant (context)
 */
class MidWater : public WaterStrategy
{
    public:
        /**
         * @brief Applies moderate watering to the plant.
         * @param plant Pointer to the plant to be watered.
         * @return Integer representing the medium water amount applied.
         */
        int water(LivingPlant* plant);

        /**
         * @brief Gets the unique identifier for the MidWater strategy.
         * @return Integer ID representing the MidWater strategy.
         */
   static      int getID();
};

#endif
