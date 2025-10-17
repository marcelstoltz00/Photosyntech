#ifndef __Observer_h__
#define __Observer_h__

class Subject;
class LivingPlant;

/**
 * @brief Abstract observer interface in the Observer pattern.
 *
 * Defines the update interface for receiving notifications about plant status changes.
 * Concrete observers (like Staff) implement these methods to respond to plant care
 * notifications such as water needs, sunlight needs, and state changes.
 */
class Observer
{
	public:
		/**
		 * @brief Receives notification that a plant needs water.
		 * @param aPlant Pointer to the LivingPlant that needs watering.
		 */
		virtual void getWaterUpdate(LivingPlant* aPlant) = 0;

		/**
		 * @brief Receives notification that a plant needs sunlight.
		 * @param aPlant Pointer to the LivingPlant that needs sun exposure.
		 */
		virtual void getSunUpdate(LivingPlant* aPlant) = 0;

		/**
		 * @brief Receives notification that a plant's state has changed.
		 * @param aPlant Pointer to the LivingPlant whose state was updated.
		 */
		virtual void getStateUpdate(LivingPlant* aPlant) = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Observer() {}
};

#endif
