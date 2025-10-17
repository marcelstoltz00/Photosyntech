#ifndef __Builder_h__
#define __Builder_h__

class Plant;
class Director;

/**
 * @brief Abstract builder interface for constructing complex plant objects.
 *
 * Defines the interface for creating plant components (water strategy, sun strategy,
 * maturity state) in the Builder pattern. Separates the construction of complex plant
 * objects from their representation, allowing the same construction process to create
 * different plant species with varying configurations.
 */
class Builder
{
	private:
		Plant* _plant;

	public:
		/**
		 * @brief Creates a new plant object of the specific type.
		 */
		void createObject();

		/**
		 * @brief Assigns the appropriate water strategy to the plant.
		 */
		void assignWaterStrategy();

		/**
		 * @brief Assigns the appropriate sun strategy to the plant.
		 */
		void assignSunStrategy();

		/**
		 * @brief Assigns the initial maturity state to the plant.
		 */
		void assignMaturityState();

		/**
		 * @brief Returns the fully constructed plant object.
		 * @return Pointer to the constructed Plant object.
		 */
		Plant* getResult();
};

#endif
