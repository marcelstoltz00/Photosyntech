#ifndef PlantMemento_h
#define PlantMemento_h

#include <string>

class LivingPlant;
class GrowPlantCommand;

/**
 * @brief Memento class capturing immutable snapshot of LivingPlant state.
 *
 * Stores a snapshot of a plant's state at a specific point in time for later restoration.
 * Used by GrowPlantCommand to enable undo functionality. Maintains encapsulation by only
 * allowing LivingPlant to create and restore from memento (friend access).
 *
 * **System Role:**
 * Enables undo functionality for plant growth and state changes by capturing essential
 * plant attributes (age, health, water level, sun exposure, maturity state) in an
 * immutable snapshot. Commands use mementos to implement reversible operations.
 *
 * **Pattern Role:** Memento (encapsulates state snapshot)
 *
 * **Related Patterns:**
 * - LivingPlant: Originator that creates and restores from memento
 * - GrowPlantCommand: Caretaker that stores memento for undo
 * - Command: Uses memento to implement undo operations
 *
 * **System Interactions:**
 * - GrowPlantCommand creates PlantMemento before executing growth
 * - PlantMemento stores plant's current state attributes
 * - GrowPlantCommand calls restoreState() during undo
 * - Memento is immutable after creation (no state modifications)
 *
 * @see LivingPlant (originator)
 * @see GrowPlantCommand (caretaker)
 */
class PlantMemento
{
	friend class LivingPlant;
	friend class GrowPlantCommand;

private:
	/**
	 * @brief Captured plant state attributes.
	 */
	int age;
	double health;
	int waterLevel;
	int sunExposure;
	int maturityStateID;
	std::string name;
	double basePrice;

	/**
	 * @brief Private constructor for friend-only creation.
	 * @param plant Pointer to the LivingPlant to capture state from.
	 */
	PlantMemento(LivingPlant *plant);

public:
	/**
	 * @brief Virtual destructor for proper cleanup.
	 */
	virtual ~PlantMemento();

	/**
	 * @brief Restores captured state to a plant.
	 * @param plant Pointer to the LivingPlant to restore state to.
	 */
	void restoreState(LivingPlant *plant);

	// Accessors for debugging/testing only
	int getAge() const;
	double getHealth() const;
	int getWaterLevel() const;
	int getSunExposure() const;
	int getMaturityStateID() const;
	std::string getName() const;
	double getBasePrice() const;
};

#endif
