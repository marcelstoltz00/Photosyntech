#ifndef WaterStrategy_h
#define WaterStrategy_h

/**
 * @brief Abstract strategy interface for plant watering algorithms.
 *
 * Defines the interface for different watering approaches in the Strategy pattern.
 * Concrete strategies implement specific water amount and frequency algorithms
 * for different plant types and care requirements.
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
