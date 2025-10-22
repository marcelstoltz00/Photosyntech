#ifndef PlantAttributes_h
#define PlantAttributes_h

#include <string>
#include "../composite/PlantComponent.h"
//@Wilmar does this mess anything up in flyweight? It is what the diagram says ...
#include "../flyweight/Flyweight.h"
#include "../singleton/Singleton.h"

/**
 * @brief Abstract decorator for adding attributes to plants.
 *
 * Maintains a reference to a PlantComponent and defines an interface conforming
 * to Component. Concrete decorators add specific visual attributes and modify
 * plant characteristics like sunlight/water needs and price. Decorators can be
 * stacked to apply multiple customizations.
 *
 * **System Role:**
 * Base class for all plant customizations. Wraps PlantComponent while preserving
 * interface. Enables stacking decorators (pots + charms + seasonal features).
 * Central to plant customization and pricing flexibility.
 *
 * **Pattern Role:** Abstract Decorator (defines wrapping and modification interface)
 *
 * **Related Patterns:**
 * - PlantComponent: Component interface that decorators wrap
 * - Composite: Wraps components while preserving hierarchy
 * - Prototype: clone() preserves decorator layers
 * - Builder: Decorators applied after plant construction
 * - Flyweight: Decorator instances may be shared
 *
 * **System Interactions:**
 * - Wraps PlantComponent reference maintaining interface
 * - getInfo() adds decorator details to component info
 * - getPrice() modifies base price with decorator cost
 * - affectWater/Sunlight() modify care requirements
 * - addAttribute() chains decorators together
 *
 * - clone() creates deep copy including all decorators
 *
 * @see PlantComponent (wrapped component)
 * @see Concrete decorators: LargePot, Spring, etc.
 */
class PlantAttributes : public PlantComponent
{
protected:
	PlantComponent *nextComponent;

	// Name of the attribute
	Flyweight<std::string *> *name;

public:
	/**
	 * @brief Constructs a plant attribute decorator.
	 * @param name Information string for this attribute.
	 * @param price Price modification for this attribute.
	 * @param waterAffect Water affection modification.
	 * @param sunAffect Sun affection modification.
	 */
	PlantAttributes(std::string name, double price, int waterAffect, int sunAffect);

	/**
	 * @brief Copies a plant attribute decorator.

	 */
	PlantAttributes(const PlantAttributes &other);

	/**
	 * @brief Gets the sunlight affection value including decorator modifications.
	 * @return Integer representing total sunlight impact.
	 */

	/**
	 * @brief Gets the water affection value including decorator modifications.
	 * @return Integer representing total water impact.
	 */

	/**
	 * @brief Gets plant information including decorator details.
	 * @return String containing plant and decorator details.
	 */
	std::string getInfo() override;

	/**
	 * @brief Gets the price including decorator modifications.
	 * @return Total price in currency units.
	 */
	double getPrice() override;

	/**
	 * @brief Gets the sunlight affection value for this component.
	 * @return Integer representing sunlight impact.
	 */
	int affectSunlight() override;

	/**
	 * @brief Gets the water affection value for this component.
	 * @return Integer representing water impact.
	 */
	int affectWater() override;

	/**
	 * @brief Gets component name as a formatted string.
	 * @return String containing plant name.
	 */
	std::string getName() override;

	/**
	 * @brief Waters the plant component.
	 */
	void water() override;

	/**
	 * @brief Sets the plant component to be outside.(Calls Sun Strategy)
	 */
	void setOutside() override;

	/**
	 * @brief Subtracts waterAffect and sunAffect from waterLevel and sunExposure.
	 */
	void update() override;

	/**
	 * @brief Adds another attribute decorator to this plant.
	 * @param attribute Pointer to the PlantAttributes decorator to add.
	 */
	void addAttribute(PlantComponent *attribute) override;

	/**
	 * @brief Clones the decorated plant including all decorators.
	 * @return Pointer to a new PlantComponent that is a copy of this decorated plant.
	 */
	virtual PlantComponent* clone() override = 0;

	/**
	 * @brief Gets the component type (PLANT_COMPONENT for decorators).
	 *
	 * Enables efficient type identification without dynamic_cast.
	 *
	 * @return ComponentType::PLANT_COMPONENT
	 */
	ComponentType getType() const override {
		return ComponentType::PLANT_COMPONENT;
	}

	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~PlantAttributes()
	{
		if (nextComponent)
			delete nextComponent;
	}

	// /**
	//  * @brief Sets the decorator for builder purposes
	//  * @param other Pointer to the decorator.
	// */
	// void setDecorator(PlantComponent* other);
	PlantComponent *correctShape(PlantComponent *mainDecorator);
};

#endif
