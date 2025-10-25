#ifndef NurseryFacade_h
#define NurseryFacade_h

#include "../singleton/Singleton.h"
#include "../mediator/Mediator.h"
#include "../command/Command.h"
#include "../iterator/Aggregate.h"
#include "../composite/PlantComponent.h"
#include "../mediator/Customer.h"
#include "../state/PlantMemento.h"
#include <stack>
#include <vector>
#include <string>

class Staff;
class LivingPlant;
class PlantAttributes;
class PlantGroup;
class Iterator;
class Inventory;

/**
 * @brief Unified facade interface for the nursery management system.
 *
 * Provides simplified, high-level methods for common operations by
 * coordinating multiple subsystems (plant creation via Builder/Director,
 * inventory management via Singleton, sales via Mediator, operations via Command,
 * and filtering via Iterator). Hides system complexity from GUI and external clients.
 *
 * **System Role:**
 * This class serves as the single integration point for the entire Photosyntech system.
 * It is the only interface that GUI, CLI, and external systems need to know about.
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
 * - External interfaces (GUI/CLI) call methods on facade only
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
		static const int MAX_HISTORY_SIZE = 100;

		Inventory* inventory;
		Mediator* salesFloor;
		Mediator* suggestionFloor;
		std::stack<Command*> commandHistory;
		std::stack<Command*> redoStack;

	public:
		/**
		 * @brief Constructs the NurseryFacade.
		 * Initializes all subsystem references and mediators.
		 */
		NurseryFacade();

		/**
		 * @brief Destructs the NurseryFacade.
		 * Cleans up all commands in history and redo stacks.
		 */
		virtual ~NurseryFacade();

		// ===========================================
		// COMMAND OPERATIONS (with history management)
		// ===========================================

		/**
		 * @brief Creates a new plant using the builder pattern (with undo support).
		 * @param species String identifying the plant species to create.
		 * @return Pointer to the newly created PlantComponent, or nullptr on failure.
		 */
		PlantComponent* createPlant(const char* species);

		/**
		 * @brief Adds a plant to a customer's shopping basket (with undo support).
		 * @param customer Pointer to the Customer to add plant to.
		 * @param plant Pointer to the PlantComponent to add.
		 */
		void addToBasket(Customer* customer, PlantComponent* plant);

		/**
		 * @brief Grows a plant through its lifecycle state (with undo support).
		 * @param plant Pointer to the LivingPlant to grow.
		 */
		void growPlant(LivingPlant* plant);

		/**
		 * @brief Purchases plants from a customer's basket (with undo support).
		 * @param customer Pointer to the Customer making the purchase.
		 */
		void purchasePlants(Customer* customer);

		/**
		 * @brief Gets plant suggestions for a customer (with undo support).
		 * @param customer Pointer to the Customer requesting suggestions.
		 */
		void getSuggestions(Customer* customer);

		// ===========================================
		// UNDO/REDO OPERATIONS
		// ===========================================

		/**
		 * @brief Undoes the most recent command.
		 * @return True if undo succeeded, false if history is empty.
		 */
		bool undo();

		/**
		 * @brief Redoes the most recently undone command.
		 * @return True if redo succeeded, false if redo stack is empty.
		 */
		bool redo();

		/**
		 * @brief Clears all command history and redo stacks.
		 * Used when resetting session or closing application.
		 */
		void clearHistory();

		// ===========================================
		// BASIC OPERATIONS (Direct Delegations)
		// ===========================================

		// Plant Information
		std::string getPlantInfo(PlantComponent* plant);
		double getPlantPrice(PlantComponent* plant);

		// Plant Care
		void waterPlant(PlantComponent* plant);
		void setPlantOutside(PlantComponent* plant);
		void updatePlant(PlantComponent* plant);

		// Plant Attributes
		void setWaterLevel(LivingPlant* plant, int level);
		void setSunExposure(LivingPlant* plant, int level);
		void setWaterStrategy(LivingPlant* plant, int strategyID);
		void setSunStrategy(LivingPlant* plant, int strategyID);
		void setMaturity(LivingPlant* plant, int stateID);
		void setSeason(LivingPlant* plant, const std::string& season);

		// Plant Decoration
		void addAttribute(PlantComponent* plant, PlantAttributes* attr);

		// Plant Cloning
		PlantComponent* clonePlant(PlantComponent* plant);

		// Inventory Operations
		void addToInventory(PlantComponent* plant);
		void removeFromInventory(PlantComponent* plant);

		// Iterator Creation
		Iterator* createAllPlantsIterator();
		Iterator* createSeasonIterator(const char* season);

		// Observer Management
		void attachStaffToGroup(PlantGroup* group, Staff* staff);
		void detachStaffFromGroup(PlantGroup* group, Staff* staff);

		// Staff/Customer Management
		void addStaff(Staff* staff);
		void addCustomer(Customer* customer);
		std::vector<Staff*>* getStaff();
		std::vector<Customer*>* getCustomers();

		// Group Notifications
		void notifyWaterNeeded(PlantGroup* group);
		void notifySunlightNeeded(PlantGroup* group);
		void notifyStateUpdated(PlantGroup* group);
};

#endif
