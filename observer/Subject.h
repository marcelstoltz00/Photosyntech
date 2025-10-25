#ifndef Subject_h
#define Subject_h

// Remove: #include "Observer.h" - it causes circular dependency

// Forward declared instead
class Observer;
class PlantGroup;

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
	 * @param careTaker Pointer to the Observer to attach.
	 */
	virtual void attach(Observer *careTaker) = 0;

	/**
	 * @brief Detaches an observer from receiving notifications.
	 * @param careTaker Pointer to the Observer to detach.
	 */
	virtual void detach(Observer *careTaker) = 0;

	/**
	 * @brief Notifies all observers that plants need sunlight.
	 */
	virtual void sunlightNeeded(PlantComponent* updatedPlant) = 0;

	/**
	 * @brief Notifies all observers that a plant's state has been updated.
	 */
	virtual void stateUpdated(PlantComponent* updatedPlant) = 0;

	/**
	 * @brief Notifies all observers that plants need water.
	 */
	virtual void waterNeeded(PlantComponent* updatedPlant) = 0;

	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~Subject() {}
};

#endif
