#ifndef LivingPlant_h
#define LivingPlant_h

#include <string>
#include "../composite/PlantComponent.h"
#include "../flyweight/Flyweight.h"
#include "../state/MaturityState.h"
#include "../strategy/WaterStrategy.h"
#include "../strategy/SunStrategy.h"
#include "../decorator/PlantAttributes.h"

/**
 * @brief Base class for all living plant objects in the Prototype pattern.
 *
 * Represents an individual plant (leaf node in the Composite pattern) with specific
 * characteristics like age, health, water level, and sun exposure. Manages strategies
 * for watering and sunlight, as well as maturity state. Serves as the Context for
 * State and Strategy patterns. Uses Flyweight pattern for shared immutable data.
 *
 * **System Role:**
 * This abstract base class is the context and storage for all plant lifecycle data.
 * It implements PlantComponent (Composite leaf) and enables deep cloning via the
 * clone() method for Prototype pattern. Holds references to Strategy (water/sun)
 * and State (maturity) flyweights for behavior delegation. Core entity in system.
 *
 * **Pattern Role:** Abstract Prototype (defines cloning interface)
 *
 * **Related Patterns:**
 * - PlantComponent: Leaf implementation of composite interface
 * - State Pattern: Delegates to MaturityState flyweights
 * - Strategy Pattern: Delegates to WaterStrategy and SunStrategy flyweights
 * - Flyweight Pattern: References to shared strategy and state objects
 * - Builder Pattern: Created by concrete builders during plant construction
 * - Decorator Pattern: Can be wrapped with PlantAttributes decorators
 * - Composite Pattern: Leaf node in plant hierarchy
 * - Observer Pattern: Subject notifications trigger on state changes
 *
 * **System Interactions:**
 * - Builder creates LivingPlant subclass instances
 * - Assigns water/sun strategies via setWaterStrategy(), setSunStrategy()
 * - Assigns maturity state via setMaturity()
 * - clone() creates deep copies for inventory mass production
 * - Decorators wrap instances without changing interface
 * - Strategies executed on water(), state processed by affectWater/Sunlight
 *
 * @see PlantComponent (Composite leaf interface)
 * @see State pattern (MaturityState context)
 * @see Strategy pattern (WaterStrategy, SunStrategy context)
 * @see Flyweight pattern (shared strategy/state references)
 * @see Decorator pattern (attributes wrap LivingPlant)
 */
class LivingPlant : public PlantComponent
{
	protected:
		/**
		 * Name of the plant.
		 */
		Flyweight<std::string> name;

		/**
		 * Age of the plant in months.
		 */
		int age;
		int health;
		int waterLevel;
		int sunExposure;

		/**
		 * Growing season for the plant.
		 */
		Flyweight<std::string> season;

		Flyweight<MaturityState>* maturityState;
		Flyweight<WaterStrategy>* waterStrategy;
		Flyweight<SunStrategy>* sunStrategy;

	public:
		/**
		 * @brief Constructs a living plant with basic attributes.
		 * @param info Information string describing the plant.
		 * @param price Base price of the plant.
		 * @param waterAffect Water affection value.
		 * @param sunAffect Sun affection value.
		 */
		LivingPlant(std::string info, double price, int waterAffect, int sunAffect);

		/**
		 * @brief Sets the water strategy for this plant.
		 * @param strategy Integer ID of the water strategy to use.
		 */
		void setWaterStrategy(int strategy);

		/**
		 * @brief Sets the sun strategy for this plant.
		 * @param strategy Integer ID of the sun strategy to use.
		 */
		void setSunStrategy(int strategy);

		/**
		 * @brief Sets the maturity state for this plant.
		 * @param state Integer ID of the maturity state.
		 */
		void setMaturity(int state);

		/**
		 * @brief Adds a decorator attribute to this plant.
		 * @param attribute Pointer to the PlantAttributes decorator to add.
		 */
		void addAttribute(PlantAttributes* attribute);

		/**
		 * @brief Gets the age of the plant in months.
		 * @return Age in months.
		 */
		int getAge();

		/**
		 * @brief Gets plant information as a formatted string.
		 * @return String containing plant details.
		 */
		std::string getInfo();

		/**
		 * @brief Gets the sunlight affection value.
		 * @return Integer representing sunlight impact.
		 */
		int affectSunlight();

		/**
		 * @brief Gets the water affection value.
		 * @return Integer representing water impact.
		 */
		int affectWater();

		/**
		 * @brief Gets the price of this plant.
		 * @return Price in currency units.
		 */
		double getPrice();

		/**
		 * @brief Clones the plant creating a deep copy (Prototype pattern).
		 * @return Pointer to a new plant object that is a copy of this one.
		 */
		PlantComponent* clone();

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~LivingPlant() {}
};

#endif
