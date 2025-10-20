#ifndef Builder_h
#define Builder_h

#include "Plant.h"

/**
 * @brief Abstract builder interface for constructing complex plant objects.
 *
 * Defines the interface for creating plant components (water strategy, sun strategy,
 * maturity state) in the Builder pattern. Separates the construction of complex plant
 * objects from their representation, allowing the same construction process to create
 * different plant species with varying configurations.
 *
 * **System Role:**
 * This abstract class defines the contract for all plant builders in the system.
 * Each concrete builder encapsulates the construction logic for a specific plant species,
 * enabling Director to orchestrate the same construction sequence for different plants.
 *
 * **Pattern Role:** Abstract Builder (defines construction step interface)
 *
 * **Related Patterns:**
 * - Director: Orchestrates the construction steps defined in this interface
 * - Concrete Builders: RoseBuilder, SunflowerBuilder, Plant3Builder implement this
 * - Strategy: Builder assigns water/sun strategy instances to plants
 * - State: Builder initializes plants in Seed maturity state
 * - Prototype: Builder creates templates that are cloned for inventory
 * - Singleton: Builder obtains shared strategy flyweights from singleton
 * - Composite: Built plants are added to plant groups in inventory
 *
 * **System Interactions:**
 * - Director calls builder methods in sequence to construct plants
 * - Each builder subclass implements species-specific construction
 * - Strategies obtained from singleton's flyweight factories
 * - Resulting plants ready for decoration or inventory addition
 *
 * @see Director (orchestrates construction)
 * @see Strategy (strategies assigned during construction)
 * @see Singleton (strategy acquisition)
 */
class Builder
{
	private:
		Plant* plant;

	public:
		/**
		 * @brief Creates a new plant object of the specific type.
		 */
		virtual void createObject() = 0;

		/**
		 * @brief Assigns the appropriate water strategy to the plant.
		 */
		virtual void assignWaterStrategy() = 0;

		/**
		 * @brief Assigns the appropriate sun strategy to the plant.
		 */
		virtual void assignSunStrategy() = 0;

		/**
		 * @brief Assigns the initial maturity state to the plant.
		 */
		virtual void assignMaturityState() = 0;

		/**
		 * @brief Returns the fully constructed plant object.
		 * @return Pointer to the constructed Plant object.
		 */
		virtual Plant* getResult() = 0;

		/**
		 * @brief Virtual destructor for the Builder class.
		 */
		virtual ~Builder() = default;
};

#endif
