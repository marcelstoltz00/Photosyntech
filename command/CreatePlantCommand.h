#ifndef CreatePlantCommand_h
#define CreatePlantCommand_h

#include "Command.h"
#include <string>

class PlantComponent;
class Director;
class Builder;

/**
 * @brief Command for creating a plant using the Builder pattern.
 *
 * Encapsulates the plant creation process using Builder and Director patterns.
 * Maps species names to appropriate builders, orchestrates construction, and manages
 * inventory addition with undo support.
 *
 * **System Role:**
 * Enables reversible plant creation through the command history.
 * Coordinates builder selection, plant construction, and inventory management.
 *
 * **Pattern Role:** Concrete Command (Direct Undo approach)
 *
 * **Related Patterns:**
 * - Command: Base interface for execution/undo
 * - Builder: Creates plant templates for each species
 * - Director: Orchestrates construction sequence
 * - Singleton: Accesses global inventory
 * - Composite: Created plant added to inventory group
 * - Facade: Invoked by NurseryFacade with history management
 *
 * **System Interactions:**
 * - NurseryFacade creates CreatePlantCommand with species name
 * - Maps species to appropriate builder implementation
 * - Director orchestrates the construction process
 * - Plant added to global inventory
 * - Undo removes plant from inventory and deletes it
 *
 * @see Command (base interface)
 * @see Builder (species-specific construction)
 * @see Director (construction orchestration)
 * @see NurseryFacade (command invocation)
 */
class CreatePlantCommand : public Command
{
private:
	/**
	 * @brief The species name (e.g., "Rose", "Cactus", etc.)
	 * Used to map to appropriate builder.
	 */
	std::string species;

	/**
	 * @brief Reference to the created plant.
	 * Not owned by command; lifetime managed by inventory after creation.
	 */
	PlantComponent *createdPlant;

	/**
	 * @brief Helper method to create appropriate builder from species name.
	 * @param speciesName The species name string.
	 * @return Pointer to newly created Builder.
	 * @throws std::invalid_argument if species is unknown.
	 */
	static Builder *createBuilder(const std::string &speciesName);

public:
	/**
	 * @brief Constructs a CreatePlantCommand for the given species.
	 * @param species Const char* species name (e.g., "Rose", "Cactus").
	 * @throws std::invalid_argument if species is unknown or unsupported.
	 */
	explicit CreatePlantCommand(const char *species);

	/**
	 * @brief Executes the plant creation operation.
	 *
	 * **Workflow:**
	 * 1. Determine builder type from species string
	 * 2. Instantiate appropriate builder
	 * 3. Create Director with builder
	 * 4. Call director->construct()
	 * 5. Retrieve plant via director->getPlant()
	 * 6. Add plant to Inventory::getInstance()->getInventory()
	 * 7. Store plant pointer for undo
	 *
	 * Supported species:
	 * - Rose, Cactus, SunflowerBuilder, Pine, Maple, JadePlant, Lavender, CherryBlossom
	 *
	 * @throws std::invalid_argument if species is unknown
	 * @throws std::runtime_error if plant creation fails
	 */
	void execute() override;

	/**
	 * @brief Undoes the plant creation operation.
	 *
	 * **Workflow:**
	 * 1. Validate createdPlant is not null
	 * 2. Remove plant from inventory using removeComponent()
	 * 3. Delete plant decorators via getDecorator()
	 * 4. Delete plant object
	 * 5. Set createdPlant to nullptr
	 *
	 * @throws std::runtime_error if undo fails.
	 */
	void undo() override;

	/**
	 * @brief Gets the created plant reference.
	 * @return Pointer to the created PlantComponent, or nullptr if creation failed.
	 */
	PlantComponent* getCreatedPlant() const;

	/**
	 * @brief Virtual destructor for proper cleanup.
	 * No dynamic allocation in this command.
	 */
	virtual ~CreatePlantCommand() = default;
};

#endif
