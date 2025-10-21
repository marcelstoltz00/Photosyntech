#ifndef Builder_h
#define Builder_h

#include "prototype/LivingPlant.h"

/**
 * @brief Abstract builder interface for constructing complex LivingPlant objects.
 *
 * Defines the interface for creating LivingPlant components (water strategy, sun strategy,
 * maturity state) in the Builder pattern. Separates the construction of complex LivingPlant
 * objects from their representation, allowing the same construction process to create
 * different LivingPlant species with varying configurations.
 *
 * **System Role:**
 * This abstract class defines the contract for all LivingPlant builders in the system.
 * Each concrete builder encapsulates the construction logic for a specific LivingPlant species,
 * enabling Director to orchestrate the same construction sequence for different LivingPlants.
 *
 * **Pattern Role:** Abstract Builder (defines construction step interface)
 *
 * **Related Patterns:**
 * - Director: Orchestrates the construction steps defined in this interface
 * - Concrete Builders: RoseBuilder, SunflowerBuilder, LivingPlant3Builder implement this
 * - Strategy: Builder assigns water/sun strategy instances to LivingPlants
 * - State: Builder initializes LivingPlants in Seed maturity state
 * - Prototype: Builder creates templates that are cloned for inventory
 * - Singleton: Builder obtains shared strategy flyweights from singleton
 * - Composite: Built LivingPlants are added to LivingPlant groups in inventory
 *
 * **System Interactions:**
 * - Director calls builder methods in sequence to construct LivingPlants
 * - Each builder subclass implements species-specific construction
 * - Strategies obtained from singleton's flyweight factories
 * - Resulting LivingPlants ready for decoration or inventory addition
 *
 * @see Director (orchestrates construction)
 * @see Strategy (strategies assigned during construction)
 * @see Singleton (strategy acquisition)
 */
class Builder
{
	private:
		LivingPlant* Plant = nullptr;

	public:
		/**
		 * @brief Creates a new LivingPlant object of the specific type.
		 */
		virtual void createObject() = 0;

		/**
		 * @brief Assigns the appropriate water strategy to the LivingPlant.
		 */
		virtual void assignWaterStrategy() = 0;

		/**
		 * @brief Assigns the appropriate sun strategy to the LivingPlant.
		 */
		virtual void assignSunStrategy() = 0;

		/**
		 * @brief Assigns the initial maturity state to the LivingPlant.
		 */
		virtual void assignMaturityState() = 0;

		/**
		 * @brief Adds decorators to the LivingPlant.
		 */
		virtual void addDecorators() = 0;

		/**
		 * @brief Returns the fully constructed LivingPlant object.
		 * @return Pointer to the constructed LivingPlant object.
		 */
		virtual LivingPlant* getResult() = 0;

		/**
		 * @brief Virtual destructor for the Builder class.
		 */
		virtual ~Builder() = default;
};

#endif
