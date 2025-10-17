#ifndef __LivingPlant_h__
#define __LivingPlant_h__

#include <string>
#include "../composite/PlantComponent.h"
#include "../flyweight/Flyweight.h"
#include "../state/MaturityState.h"
#include "../strategy/WaterStrategy.h"
#include "../strategy/SunStrategy.h"

class PlantAttributes;

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
		Flyweight<std::string> _name;

		/**
		 * Age of the plant in months.
		 */
		int _age;
		int _health;
		int _waterLevel;
		int _sunExposure;

		/**
		 * Growing season for the plant.
		 */
		Flyweight<std::string> _season;

		Flyweight<MaturityState>* _maturityState;
		Flyweight<WaterStrategy>* _waterStrategy;
		Flyweight<SunStrategy>* _sunStrategy;

	public:
		/**
		 * @brief Constructs a living plant with basic attributes.
		 * @param aInfo Information string describing the plant.
		 * @param aPrice Base price of the plant.
		 * @param aWaterAffect Water affection value.
		 * @param aSunAffect Sun affection value.
		 */
		LivingPlant(std::string aInfo, double aPrice, int aWaterAffect, int aSunAffect);

		/**
		 * @brief Sets the water strategy for this plant.
		 * @param aStrategy Integer ID of the water strategy to use.
		 */
		void setWaterStrategy(int aStrategy);

		/**
		 * @brief Sets the sun strategy for this plant.
		 * @param aStrategy Integer ID of the sun strategy to use.
		 */
		void setSunStrategy(int aStrategy);

		/**
		 * @brief Sets the maturity state for this plant.
		 * @param aState Integer ID of the maturity state.
		 */
		void setMaturity(int aState);

		/**
		 * @brief Adds a decorator attribute to this plant.
		 * @param aAttribute Pointer to the PlantAttributes decorator to add.
		 */
		void addAttribute(PlantAttributes* aAttribute);

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
