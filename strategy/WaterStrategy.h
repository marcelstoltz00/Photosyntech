#ifndef WaterStrategy_h
#define WaterStrategy_h

/**
 * @brief Abstract strategy interface for plant watering algorithms.
 *
 * Defines the interface for different watering approaches in the Strategy pattern.
 * Concrete strategies implement specific water amount and frequency algorithms
 * for different plant types and care requirements.
 *
 * **System Role:**
 * Defines contract for all watering algorithms. LivingPlant maintains reference
 * to concrete strategy and delegates watering via water() method. Strategies
 * obtained from singleton's flyweight factory for memory optimization.
 *
 * **Pattern Role:** Abstract Strategy (defines watering algorithm interface)
 *
 * **Related Patterns:**
 * - LivingPlant: Context using water strategy
 * - Concrete Strategies: LowWater, MidWater, HighWater, AlternatingWater
 * - Flyweight: Shared via singleton factories
 * - Builder: Assigns appropriate strategy during construction
 * - Command: WaterPlantCommand executes strategy
 * - Composite: Strategy applied uniformly to plant groups
 *
 * **System Interactions:**
 * - Builder assigns water strategy during plant creation
 * - LivingPlant delegates water() calls to strategy
 * - water() returns water amount applied
 * - getID() used for flyweight factory identification
 * - Singleton manages strategy instance caching
 *
 * @see Concrete strategies: LowWater, MidWater, HighWater, AlternatingWater
 * @see LivingPlant (context)
 * @see Singleton (manages flyweight factories)
 */
class WaterStrategy
{
	protected:
		int waterAmount;

	public:
		/**
		 * @brief Executes the watering algorithm.
		 * @return Integer representing the amount of water applied.
		 */
		virtual int water() = 0;

		/**
		 * @brief Gets the unique identifier for this water strategy type.
		 * @return Integer ID representing the strategy.
		 */
		virtual int getID() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~WaterStrategy() {}
};

#endif
