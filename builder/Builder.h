#ifndef Builder_h
#define Builder_h

#include "composite/PlantComponent.h"
#include "prototype/LivingPlant.h"

/**
 * @brief Abstract builder interface for constructing complex PlantComponent objects.
 *
 * Defines the interface for creating PlantComponent components (water strategy, sun strategy,
 * maturity state) in the Builder pattern. Separates the construction of complex PlantComponent
 * objects from their representation, allowing the same construction process to create
 * different PlantComponent species with varying configurations.
 *
 * **System Role:**
 * This abstract class defines the contract for all PlantComponent builders in the system.
 * Each concrete builder encapsulates the construction logic for a specific PlantComponent species,
 * enabling Director to orchestrate the same construction sequence for different PlantComponents.
 *
 * **Pattern Role:** Abstract Builder (defines construction step interface)
 *
 * **Related Patterns:**
 * - Director: Orchestrates the construction steps defined in this interface
 * - Concrete Builders: RoseBuilder, SunflowerBuilder, PlantComponent3Builder implement this
 * - Strategy: Builder assigns water/sun strategy instances to PlantComponents
 * - State: Builder initializes PlantComponents in Seed maturity state
 * - Prototype: Builder creates templates that are cloned for inventory
 * - Singleton: Builder obtains shared strategy flyweights from singleton
 * - Composite: Built PlantComponents are added to PlantComponent groups in inventory
 *
 * **System Interactions:**
 * - Director calls builder methods in sequence to construct PlantComponents
 * - Each builder subclass implements species-specific construction
 * - Strategies obtained from singleton's flyweight factories
 * - Resulting PlantComponents ready for decoration or inventory addition
 *
 * @see Director (orchestrates construction)
 * @see Strategy (strategies assigned during construction)
 * @see Singleton (strategy acquisition)
 */
class Builder
{
private:
	LivingPlant *plant = nullptr;
	PlantAttributes*season= nullptr;

public:
	/**
	 * @brief Creates a new PlantComponent object of the specific type.
	 */
	virtual void createObject() = 0;

	/**
	 * @brief Assigns the appropriate water strategy to the PlantComponent.
	 */
	virtual void assignWaterStrategy() = 0;

	/**
	 * @brief Assigns the appropriate sun strategy to the PlantComponent.
	 */
	virtual void assignSunStrategy() = 0;

	/**
	 * @brief Assigns the initial maturity state to the PlantComponent.
	 */
	virtual void assignMaturityState() = 0;

	/**
	 * @brief Adds decorators to the PlantComponent.
	 */
	virtual void addDecorators() = 0;

	/**
	 * @brief Sets up the initial health, water, and sun levels for the living plant.
	 */
	virtual void setUp() = 0;

	/**
	 * @brief Returns the fully constructed PlantComponent object.
	 * @return Pointer to the constructed PlantComponent object.
	 */
	virtual PlantComponent *getResult() = 0;

	/**
	 * @brief Virtual destructor for the Builder class.
	 */
	virtual ~Builder() = default;
};

#endif
