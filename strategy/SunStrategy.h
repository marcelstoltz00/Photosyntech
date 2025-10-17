#ifndef __SunStrategy_h__
#define __SunStrategy_h__

class Plant;
class LivingPlant;

/**
 * @brief Abstract strategy interface for plant sunlight exposure algorithms.
 *
 * Defines the interface for different sunlight exposure approaches in the Strategy pattern.
 * Concrete strategies implement specific intensity and duration algorithms
 * for different plant types and environmental needs.
 */
class SunStrategy
{
	protected:
		int _hoursNeeded;
		int _intensity;

	public:
		/**
		 * @brief Applies sunlight exposure to the plant.
		 * @return Integer representing the amount of sunlight applied.
		 */
		virtual int addSun() = 0;

		/**
		 * @brief Gets the unique identifier for this sun strategy type.
		 * @return Integer ID representing the strategy.
		 */
		virtual int getID() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~SunStrategy() {}
};

#endif
