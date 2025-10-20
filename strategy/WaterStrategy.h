#ifndef WaterStrategy_h
#define WaterStrategy_h

class LivingPlant; // Forward declaration

/**
 * @brief Abstract strategy interface for plant watering algorithms.
 *
 * Defines the interface for different watering approaches in the Strategy pattern.
 * Concrete strategies implement specific water amount and frequency algorithms
 * for different plant types and care requirements. Each strategy directly
 * modifies the plant's water level.
 *
 * **System Role:**
 * Defines contract for all watering algorithms. LivingPlant maintains reference
 * to concrete strategy and delegates watering via water() method. Strategies
 * directly modify plant state by accessing the LivingPlant's water properties.
 * Strategies obtained from singleton's flyweight factory for memory optimization.
 *
 * **Pattern Role:** Abstract Strategy (defines watering algorithm interface)
 *
 * **Related Patterns:**
 * - LivingPlant: Context using water strategy and receiving modifications
 * - Concrete Strategies: LowWater, MidWater, HighWater, AlternatingWater
 * - Flyweight: Shared via singleton factories
 * - Builder: Assigns appropriate strategy during construction
 * - Command: WaterPlantCommand executes strategy
 * - Composite: Strategy applied uniformly to plant groups
 *
 * **System Interactions:**
 * - Builder assigns water strategy during plant creation
 * - LivingPlant delegates water() calls to strategy, passing itself
 * - Strategy directly modifies plant's waterLevel attribute
 * - water() returns water amount applied for tracking/display
 * - Singleton manages strategy instance caching
 *
 * @see Concrete strategies: LowWater, MidWater, HighWater, AlternatingWater
 * @see LivingPlant (context and recipient of water modifications)
 * @see Singleton (manages flyweight factories)
 */
class WaterStrategy
{
protected:
    int waterAmount;

public:
    /**
     * @brief Executes the watering algorithm on the specified plant.
     * @param plant Pointer to the plant to be watered.
     * @return Integer representing the amount of water applied.
     */
    virtual int water(LivingPlant *plant) = 0;

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~WaterStrategy() {}

    static int getID()
    {
        return -1; // Abstract strategy has no ID
    }
};

#endif
