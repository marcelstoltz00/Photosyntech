#ifndef PlantGroup_h
#define PlantGroup_h

#include <string>
#include <list>
#include "PlantComponent.h"
#include "../observer/Subject.h"
#include "../decorator/PlantAttributes.h"

/**
 * @brief Represents a group of plants in the Composite pattern.
 *
 * Acts as the Composite role, managing a collection of PlantComponent objects
 * (both individual plants and other groups). Implements operations to traverse
 * and manipulate entire plant collections uniformly. Also acts as a Subject
 * in the Observer pattern, notifying staff of plant care needs.
 */
class PlantGroup : public PlantComponent, public Subject
{
private:
	std::list<PlantComponent *> plants;
	// This is the list of observers
	std::list<Observer *> observers;

	/**
	 * @brief Notifies observers that plants in this group need water.
	 */
	void waterNeeded(PlantComponent *updatedPlant) override;

	/**
	 * @brief Notifies observers that plants in this group need sunlight.
	 */
	void sunlightNeeded(PlantComponent *updatedPlant) override;

	/**
	 * @brief Notifies observers that a plant's state has been updated.
	 */
	void stateUpdated(PlantComponent *updatedPlant) override;

public:
	/**
	 * @brief Constructs a PlantGroup with 0 as attributes.
	 */
	PlantGroup();

	/**
	 * @brief Copy constructor for deep copying the group hierarchy.
	 * @param other The PlantGroup object to copy.
	 */
	PlantGroup(const PlantGroup &other);

	/**
	 * @brief Virtual destructor for proper cleanup.
	 */
	virtual ~PlantGroup();

	/**
	 * @brief Sets all plants in this group to be outside.
	 */
	void setOutside() override;

	/**
	 * @brief Waters all plants in this group.
	 */
	void water() override;

	/**
	 * @brief Gets information about all plants in this group.
	 * @return String containing details of all plants in the group.
	 */
	std::string getInfo() override;

	/**
	 * @brief Clones the plant group and all its contained plants.
	 * @return Pointer to a new PlantGroup that is a copy of this one.
	 */
	PlantComponent *clone() override;

	/**
	 * @brief Attaches an observer to receive notifications from this group.
	 * @param watcher Pointer to the Observer to attach.
	 */
	void attach(Observer *watcher) override;

	/**
	 * @brief Detaches an observer from this group.
	 * @param watcher Pointer to the Observer to detach.
	 */
	void detach(Observer *watcher) override;

	/**
	 * @brief Subtracts waterAffect and sunAffect from waterLevel and sunExposure.
	 */
	void update() override;

	/**
	 * @brief Gets the total water affection value for all plants in the group.
	 * @return Integer representing cumulative water impact.
	 */
	int affectWater() override;

	/**
	 * @brief Gets the total sunlight affection value for all plants in the group.
	 * @return Integer representing cumulative sunlight impact.
	 */
	int affectSunlight() override;

	/**
	 * @brief Gets group name as a formatted string.
	 * @return String containing group name.
	 */
	std::string getName() override;

	/**
	 * @brief Gets the total price of all plants in this group.
	 * @return Total price in currency units.
	 */
	double getPrice() override;

	/**
	 * @brief Adds an attribute decorator to all plants in this group.
	 * @param component Pointer to the PlantAttributes decorator to add.
	 */
	void addAttribute(PlantComponent *component) override;

	/**
	 * @brief Gets the component type (PLANT_GROUP).
	 *
	 * Enables efficient type identification without dynamic_cast.
	 *
	 * @return ComponentType::PLANT_GROUP
	 */
	ComponentType getType() const override;

	/**
	 * @brief Gets direct access to the internal plants list.
	 *
	 * Enables iterators to recursively traverse plant hierarchies without
	 * needing friend access to private members.
	 *
	 * @return Pointer to the list of PlantComponent pointers.
	 */
	std::list<PlantComponent *> *getPlants();
	void addComponent(PlantComponent *component);
	virtual PlantComponent *correctShape(PlantComponent *);

	void checkWater();
	void checkSunlight();
	void checkState();
	virtual int getWaterValue();
	virtual int getSunlightValue();

	virtual void tick();
};

#endif
