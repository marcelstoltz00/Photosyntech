#ifndef __Subject_h__
#define __Subject_h__

class Observer;

/**
 * @brief Abstract subject interface in the Observer pattern.
 *
 * Maintains a list of observers and provides methods to attach/detach them.
 * Notifies all registered observers of plant care needs and state changes.
 * Concrete subjects (like PlantGroup) implement notification logic.
 */
class Subject
{
	public:
		/**
		 * @brief Attaches an observer to receive notifications.
		 * @param aCareTaker Pointer to the Observer to attach.
		 */
		virtual void attach(Observer* aCareTaker) = 0;

		/**
		 * @brief Detaches an observer from receiving notifications.
		 * @param aCareTaker Pointer to the Observer to detach.
		 */
		virtual void detach(Observer* aCareTaker) = 0;

		/**
		 * @brief Notifies all observers that plants need sunlight.
		 */
		virtual void sunlightNeeded() = 0;

		/**
		 * @brief Notifies all observers that a plant's state has been updated.
		 */
		virtual void stateUpdated() = 0;

		/**
		 * @brief Notifies all observers that plants need water.
		 */
		virtual void waterNeeded() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~Subject() {}
};

#endif
