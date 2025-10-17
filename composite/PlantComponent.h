#ifndef __PlantComponent_h__
#define __PlantComponent_h__

#include <string>

class PlantGroup;
class PlantAttributes;

/**
 * @brief Abstract base class representing a plant component in the Composite pattern.
 *
 * Declares the common interface for both individual plants and plant groups.
 * This is the Component role in the Composite pattern, enabling uniform treatment
 * of individual objects and compositions. All concrete plant types inherit from this class.
 */
class PlantComponent
{
	private:
		PlantComponent* _attributes;
		double _price;
		int _affectWaterValue;
		int _affectSunValue;

	public:
		/**
		 * @brief Clones the plant component (Prototype pattern).
		 * @return Pointer to a new plant object that is a copy of this one.
		 */
		virtual PlantComponent* clone() = 0;

		/**
		 * @brief Virtual destructor for proper cleanup of derived classes.
		 */
		virtual ~PlantComponent() {}

		/**
		 * @brief Waters the plant component.
		 */
		void water();

		/**
		 * @brief Sets the plant component to be outside.
		 */
		void setOutside();

		/**
		 * @brief Gets plant information as a string.
		 * @return String containing plant details.
		 */
		virtual std::string getInfo() = 0;

		/**
		 * @brief Gets the sunlight affection value for this component.
		 * @return Integer representing sunlight impact.
		 */
		virtual int affectSunlight() = 0;

		/**
		 * @brief Gets the water affection value for this component.
		 * @return Integer representing water impact.
		 */
		virtual int affectWater() = 0;

		/**
		 * @brief Gets the price of this plant component.
		 * @return Price in currency units.
		 */
		virtual double getPrice() = 0;

		/**
		 * @brief Adds an attribute decorator to this plant component.
		 * @param aAttribute Pointer to the PlantAttributes decorator to add.
		 */
		virtual void addAttribute(PlantAttributes* aAttribute) = 0;
};

#endif
