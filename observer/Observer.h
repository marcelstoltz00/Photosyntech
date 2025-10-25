#ifndef Observer_h
#define Observer_h

// Remove: #include "Subject.h" - it also caused circular dependency
// Remove: #include "../prototype/PlantComponent.h" - only forward declared it below

// Forward declarations instead
class PlantComponent;

/**
 * @brief Abstract observer interface in the Observer pattern.
 *
 * Defines the update interface for receiving notifications about plant status changes.
 * Concrete observers (like Staff) implement these methods to respond to plant care
 * notifications such as water needs, sunlight needs, and state changes.
 *
 * **System Role:**
 * This abstract class defines the notification interface that all observers must implement.
 * Plant groups (Subject implementations) call these methods to notify all registered
 * observers of care needs and lifecycle events. Enables loose coupling between plants
 * and monitoring systems.
 *
 * **Pattern Role:** Abstract Observer (defines notification callback interface)
 *
 * **Related Patterns:**
 * - Subject: Sends notifications to observers through these methods
 * - Staff: Concrete observer implementing this interface
 * - PlantGroup: Subject (notifies observers of plant group changes)
 * - State: State transitions trigger observer notifications
 * - Command: Observer notifications may trigger staff commands
 * - Mediator: Staff (observer) coordinates with customers
 * - Composite: Notifications from plant group (composite) affect all children
 *
 * **System Interactions:**
 * - Plant groups call getWaterUpdate() when plants need watering
 * - Plant groups call getSunUpdate() when plants need sunlight
 * - Plant groups call getStateUpdate() on lifecycle state transitions
 * - Observers maintain local state tracking plant conditions
 * - Multiple observers can monitor same plant group independently
 *
 * @see Subject (sends notifications)
 * @see PlantGroup (Subject implementation that notifies)
 * @see Staff (concrete Observer implementation)
 */
class Observer
{
public:
	/**
	 * @brief Receives notification that a plant needs water.
	 * @param plant Pointer to the PlantComponent that needs watering.
	 */
	virtual void getWaterUpdate(PlantComponent *plant) = 0;

	/**
	 * @brief Receives notification that a plant needs sunlight.
	 * @param plant Pointer to the PlantComponent that needs sun exposure.
	 */
	virtual void getSunUpdate(PlantComponent *plant) = 0;

	/**
	 * @brief Receives notification that a plant's state has changed.
	 * @param plant Pointer to the PlantComponent whose state was updated.
	 */
	virtual void getStateUpdate(PlantComponent *plant) = 0;

	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~Observer() {}
};

#endif
