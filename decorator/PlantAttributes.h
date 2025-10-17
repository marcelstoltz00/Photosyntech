#ifndef __PlantAttributes_h__
#define __PlantAttributes_h__

#include <string>
#include "../composite/PlantComponent.h"

/**
 * @brief Abstract decorator for adding attributes to plants.
 *
 * Maintains a reference to a PlantComponent and defines an interface conforming
 * to Component. Concrete decorators add specific visual attributes and modify
 * plant characteristics like sunlight/water needs and price. Decorators can be
 * stacked to apply multiple customizations.
 */
class PlantAttributes : public PlantComponent
{
	public:
		/**
		 * @brief Constructs a plant attribute decorator.
		 * @param aInfo Information string for this attribute.
		 * @param aPrice Price modification for this attribute.
		 * @param aWaterAffect Water affection modification.
		 * @param aSunAffect Sun affection modification.
		 */
		PlantAttributes(std::string aInfo, double aPrice, int aWaterAffect, int aSunAffect);

		/**
		 * @brief Gets the sunlight affection value including decorator modifications.
		 * @return Integer representing total sunlight impact.
		 */
		int affectSunlight();

		/**
		 * @brief Gets the water affection value including decorator modifications.
		 * @return Integer representing total water impact.
		 */
		int affectWater();

		/**
		 * @brief Gets plant information including decorator details.
		 * @return String containing plant and decorator details.
		 */
		std::string getInfo();

		/**
		 * @brief Gets the price including decorator modifications.
		 * @return Total price in currency units.
		 */
		double getPrice();

		/**
		 * @brief Adds another attribute decorator to this plant.
		 * @param aAttribute Pointer to the PlantAttributes decorator to add.
		 */
		void addAttribute(PlantAttributes* aAttribute);

		/**
		 * @brief Clones the decorated plant including all decorators.
		 * @return Pointer to a new PlantComponent that is a copy of this decorated plant.
		 */
		PlantComponent* clone();

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~PlantAttributes() {}
};

#endif
