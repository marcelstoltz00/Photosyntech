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
