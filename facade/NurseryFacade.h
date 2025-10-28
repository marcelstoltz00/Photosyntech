#ifndef NurseryFacade_h
#define NurseryFacade_h

#include "../builder/Director.h"
#include "../singleton/Singleton.h"
#include "../mediator/Mediator.h"
#include "../command/Command.h"
#include "../iterator/Aggregate.h"
#include "../composite/PlantComponent.h"


/**
 * @brief Unified facade interface for the nursery management system.
 *
 * Provides simplified, high-level methods for common operations by
 * coordinating multiple subsystems (plant creation via Builder/Director,
 * inventory management via Singleton, sales via Mediator, operations via Command,
 * and filtering via Iterator). Hides system complexity from TUI and external clients.
 *
 * **System Role:**
 * This class serves as the single integration point for the entire Photosyntech system.
 * It is the only interface that TUI, CLI, and external systems need to know about.
 * All system operations are coordinated through this facade:
 * - Plant creation and inventory management
 * - Sales transactions and customer interactions
 * - Plant care operations and monitoring
 * - Collection filtering and browsing
 *
 * **Pattern Role:** Facade (simplifies complex subsystem interactions, hides implementation)
 *
 * **Related Patterns:**
 * - Builder/Director: Delegates plant creation requests
 * - Singleton: Accesses centralized inventory and resources
 * - Mediator: Routes customer/staff interactions through floor mediators
 * - Command: Encapsulates operations with undo/redo capability
 * - Iterator: Provides filtered plant collection access
 * - Composite: Works with plant hierarchies for bulk operations
 * - Observer: Coordinates staff monitoring setup
 * - Decorator: Manages plant customization
 * - Prototype: Handles plant cloning for inventory
 * - Flyweight: Ensures strategy resource reuse
 * - State: Manages plant lifecycle transitions
 * - Strategy: Executes plant care algorithms
 *
 * **System Interactions:**
 * - External interfaces (TUI/CLI) call methods on facade only
 * - Facade delegates to appropriate subsystem implementations
 * - Commands queued through facade for operation history
 * - All resource access goes through singleton instance
 * - Staff-customer interactions coordinated via mediators
 * - Plant filtering delegated to iterator factories
 *
 * @see Singleton (resource hub accessed by facade)
 * @see Builder (plant creation via director)
 * @see Mediator (sales and suggestion floor coordination)
 * @see Command (operation encapsulation)
 * @see Iterator (plant filtering and browsing)
 */
class NurseryFacade
{
	private:
		Director* director;
		Singleton* inventory;
		Mediator* salesFloor;
		Mediator* suggestionFloor;

	public:
		/**
		 * @brief Creates a new plant using the builder pattern.
		 * @param species String identifying the plant species to create.
		 * @return Pointer to the newly created PlantComponent.
		 */
		PlantComponent* createPlant(const char* species);

		/**
		 * @brief Adds a plant to the global inventory.
		 * @param plant Pointer to the PlantComponent to add.
		 */
		void addToInventory(PlantComponent* plant);

		/**
		 * @brief Browses available plants, optionally filtered by criteria.
		 * @param filter Optional filter string (e.g., season name).
		 */
		void browsePlants(const char* filter);

		/**
		 * @brief Initiates a plant purchase transaction.
		 * @param plant Pointer to the PlantComponent being purchased.
		 */
		void purchasePlant(PlantComponent* plant);

		/**
		 * @brief Waters a specific plant.
		 * @param plant Pointer to the PlantComponent to water.
		 */
		void waterPlant(PlantComponent* plant);

		/**
		 * @brief Requests plant care suggestions from staff.
		 */
		void getSuggestions();
};

#endif
