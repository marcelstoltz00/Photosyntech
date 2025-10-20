#ifndef SunStrategy_h
#define SunStrategy_h

/**
 * @brief Abstract strategy interface for plant sunlight exposure algorithms.
 *
 * Defines the interface for different sunlight exposure approaches in the Strategy pattern.
 * Concrete strategies implement specific intensity and duration algorithms
 * for different plant types and environmental needs.
 *
 * **System Role:**
 * Defines contract for all sunlight algorithms. LivingPlant maintains reference
 * to concrete strategy and delegates sun exposure via addSun() method. Strategies
 * obtained from singleton's flyweight factory for memory optimization.
 *
 * **Pattern Role:** Abstract Strategy (defines sunlight algorithm interface)
 *
 * **Related Patterns:**
 * - LivingPlant: Context using sun strategy
 * - Concrete Strategies: LowSun, MidSun, HighSun
 * - Flyweight: Shared via singleton factories
 * - Builder: Assigns appropriate strategy during construction
 * - Command: Staff care commands execute strategy
 * - Composite: Strategy applied uniformly to plant groups
 *
 * **System Interactions:**
 * - Builder assigns sun strategy during plant creation
 * - LivingPlant delegates sun exposure to strategy
 * - addSun() returns sun exposure amount applied
 * - getID() used for flyweight factory identification
 * - Singleton manages strategy instance caching
 *
 * @see Concrete strategies: LowSun, MidSun, HighSun
 * @see LivingPlant (context)
 * @see Singleton (manages flyweight factories)
 * @see LivingPlant (context)
 * @see Singleton (manages flyweight factories)
 */

class LivingPlant; // forward declaration

class SunStrategy
{
	protected:
		int hoursNeeded;
		int intensity;

	public:
		/**
		 * @brief Applies sunlight exposure to the plant.
		 * @param plant Pointer to the LivingPlant receiving sunlight.
		 * @return Integer representing the amount of sunlight applied.
		 */
		virtual int addSun(LivingPlant* plant) = 0;

		/**
		 * @brief Gets the unique identifier for this sun strategy type.
		 * @return Integer ID representing the strategy.
		 */
    static int getID()
    {
        return -1; // Abstract strategy has no ID
    }

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~SunStrategy() {}
};

#endif
