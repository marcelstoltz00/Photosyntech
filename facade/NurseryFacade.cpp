#include "NurseryFacade.h"
#include "../command/CreatePlantCommand.h"
#include "../command/AddPlantToBasketCommand.h"
#include "../command/GrowPlantCommand.h"
#include "../command/PurchasePlantsCommand.h"
#include "../command/GetSuggestionCommand.h"
#include "../mediator/SalesFloor.h"
#include "../mediator/SuggestionFloor.h"
#include "../composite/PlantGroup.h"
#include "../composite/PlantComponent.h"
#include "../decorator/PlantAttributes.h"
#include "../iterator/Aggregate.h"
#include "../iterator/Iterator.h"
#include "../iterator/AggPlant.h"
#include "../iterator/AggSeason.h"
#include "../mediator/Staff.h"
#include "../flyweight/Flyweight.h"
#include <iostream>
#include <stdexcept>

// ===========================================
// CONSTRUCTOR & DESTRUCTOR
// ===========================================

NurseryFacade::NurseryFacade()
{
	try
	{
		// Initialize subsystem references
		inventory = Inventory::getInstance();

		// Create mediators for customer-staff coordination
		salesFloor = new SalesFloor();
		suggestionFloor = new SuggestionFloor();

		if (inventory == nullptr || salesFloor == nullptr || suggestionFloor == nullptr)
		{
			throw std::runtime_error("NurseryFacade: Failed to initialize subsystems");
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "NurseryFacade constructor failed: " << e.what() << std::endl;
		throw;
	}
}

NurseryFacade::~NurseryFacade()
{
	// Clean up all commands in history
	while (!commandHistory.empty())
	{
		Command* cmd = commandHistory.top();
		commandHistory.pop();
		if (cmd != nullptr)
		{
			delete cmd;
		}
	}

	// Clean up all commands in redo stack
	while (!redoStack.empty())
	{
		Command* cmd = redoStack.top();
		redoStack.pop();
		if (cmd != nullptr)
		{
			delete cmd;
		}
	}

	// Clean up mediators
	if (salesFloor != nullptr)
	{
		delete salesFloor;
		salesFloor = nullptr;
	}

	if (suggestionFloor != nullptr)
	{
		delete suggestionFloor;
		suggestionFloor = nullptr;
	}

	// Note: Do not delete inventory - it's a singleton managed globally
	inventory = nullptr;
}

// ===========================================
// COMMAND OPERATIONS (with history management)
// ===========================================

PlantComponent* NurseryFacade::createPlant(const char* species)
{
	try
	{
		// Create and execute command
		CreatePlantCommand* cmd = new CreatePlantCommand(species);
		cmd->execute();

		// Get the created plant before pushing to history
		PlantComponent* createdPlant = cmd->getCreatedPlant();

		// Push to command history (check size limit first)
		if (commandHistory.size() >= MAX_HISTORY_SIZE)
		{
			// History is full - in a more robust implementation,
			// we would use a deque to remove oldest elements
			// For now, we just allow the stack to grow
		}

		commandHistory.push(cmd);

		// Clear redo stack (standard undo/redo behavior)
		while (!redoStack.empty())
		{
			Command* redoCmd = redoStack.top();
			redoStack.pop();
			delete redoCmd;
		}

		return createdPlant;
	}
	catch (const std::exception& e)
	{
		std::cerr << "createPlant failed: " << e.what() << std::endl;
		return nullptr;
	}
}

void NurseryFacade::addToBasket(Customer* customer, PlantComponent* plant)
{
	try
	{
		if (customer == nullptr)
		{
			throw std::invalid_argument("addToBasket: customer cannot be null");
		}
		if (plant == nullptr)
		{
			throw std::invalid_argument("addToBasket: plant cannot be null");
		}

		// Create and execute command
		AddPlantToBasketCommand* cmd = new AddPlantToBasketCommand(customer, plant);
		cmd->execute();

		// Push to command history
		commandHistory.push(cmd);

		// Clear redo stack
		while (!redoStack.empty())
		{
			Command* redoCmd = redoStack.top();
			redoStack.pop();
			delete redoCmd;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "addToBasket failed: " << e.what() << std::endl;
	}
}

void NurseryFacade::growPlant(LivingPlant* plant)
{
	try
	{
		if (plant == nullptr)
		{
			throw std::invalid_argument("growPlant: plant cannot be null");
		}

		// Create and execute command
		GrowPlantCommand* cmd = new GrowPlantCommand(plant);
		cmd->execute();

		// Push to command history
		commandHistory.push(cmd);

		// Clear redo stack
		while (!redoStack.empty())
		{
			Command* redoCmd = redoStack.top();
			redoStack.pop();
			delete redoCmd;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "growPlant failed: " << e.what() << std::endl;
	}
}

void NurseryFacade::purchasePlants(Customer* customer)
{
	try
	{
		if (customer == nullptr)
		{
			throw std::invalid_argument("purchasePlants: customer cannot be null");
		}

		// Create and execute command
		PurchasePlantsCommand* cmd = new PurchasePlantsCommand(customer, dynamic_cast<SalesFloor*>(salesFloor));
		cmd->execute();

		// Push to command history
		commandHistory.push(cmd);

		// Clear redo stack
		while (!redoStack.empty())
		{
			Command* redoCmd = redoStack.top();
			redoStack.pop();
			delete redoCmd;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "purchasePlants failed: " << e.what() << std::endl;
	}
}

void NurseryFacade::getSuggestions(Customer* customer)
{
	try
	{
		if (customer == nullptr)
		{
			throw std::invalid_argument("getSuggestions: customer cannot be null");
		}

		// Create and execute command
		GetSuggestionCommand* cmd = new GetSuggestionCommand(customer, dynamic_cast<SuggestionFloor*>(suggestionFloor));
		cmd->execute();

		// Push to command history
		commandHistory.push(cmd);

		// Clear redo stack
		while (!redoStack.empty())
		{
			Command* redoCmd = redoStack.top();
			redoStack.pop();
			delete redoCmd;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "getSuggestions failed: " << e.what() << std::endl;
	}
}

// ===========================================
// UNDO/REDO OPERATIONS
// ===========================================

bool NurseryFacade::undo()
{
	try
	{
		// Check if history is empty
		if (commandHistory.empty())
		{
			return false;
		}

		// Pop command from history
		Command* cmd = commandHistory.top();
		commandHistory.pop();

		// Execute undo
		cmd->undo();

		// Push to redo stack
		redoStack.push(cmd);

		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << "undo failed: " << e.what() << std::endl;
		return false;
	}
}

bool NurseryFacade::redo()
{
	try
	{
		// Check if redo stack is empty
		if (redoStack.empty())
		{
			return false;
		}

		// Pop command from redo stack
		Command* cmd = redoStack.top();
		redoStack.pop();

		// Execute command
		cmd->execute();

		// Push to history
		commandHistory.push(cmd);

		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << "redo failed: " << e.what() << std::endl;
		return false;
	}
}

void NurseryFacade::clearHistory()
{
	// Delete all commands in history
	while (!commandHistory.empty())
	{
		Command* cmd = commandHistory.top();
		commandHistory.pop();
		if (cmd != nullptr)
		{
			delete cmd;
		}
	}

	// Delete all commands in redo stack
	while (!redoStack.empty())
	{
		Command* cmd = redoStack.top();
		redoStack.pop();
		if (cmd != nullptr)
		{
			delete cmd;
		}
	}
}

// ===========================================
// BASIC OPERATIONS (Direct Delegations)
// ===========================================

// Plant Information
std::string NurseryFacade::getPlantInfo(PlantComponent* plant)
{
	if (plant == nullptr)
	{
		return "Error: plant is null";
	}
	return plant->getInfo();
}

double NurseryFacade::getPlantPrice(PlantComponent* plant)
{
	if (plant == nullptr)
	{
		return 0.0;
	}
	return plant->getPrice();
}

// Plant Care
void NurseryFacade::waterPlant(PlantComponent* plant)
{
	if (plant != nullptr)
	{
		plant->water();
	}
}

void NurseryFacade::setPlantOutside(PlantComponent* plant)
{
	if (plant != nullptr)
	{
		plant->setOutside();
	}
}

void NurseryFacade::updatePlant(PlantComponent* plant)
{
	if (plant != nullptr)
	{
		plant->update();
	}
}

// Plant Attributes
void NurseryFacade::setWaterLevel(LivingPlant* plant, int level)
{
	if (plant != nullptr)
	{
		plant->setWaterLevel(level);
	}
}

void NurseryFacade::setSunExposure(LivingPlant* plant, int level)
{
	if (plant != nullptr)
	{
		plant->setSunExposure(level);
	}
}

void NurseryFacade::setWaterStrategy(LivingPlant* plant, int strategyID)
{
	if (plant != nullptr)
	{
		plant->setWaterStrategy(strategyID);
	}
}

void NurseryFacade::setSunStrategy(LivingPlant* plant, int strategyID)
{
	if (plant != nullptr)
	{
		plant->setSunStrategy(strategyID);
	}
}

void NurseryFacade::setMaturity(LivingPlant* plant, int stateID)
{
	if (plant != nullptr)
	{
		plant->setMaturity(stateID);
	}
}

void NurseryFacade::setSeason(LivingPlant* plant, const std::string& season)
{
	if (plant != nullptr && inventory != nullptr)
	{
		Flyweight<std::string*>* seasonFly = inventory->getString(season);
		if (seasonFly != nullptr)
		{
			plant->setSeason(seasonFly);
		}
	}
}

// Plant Decoration
void NurseryFacade::addAttribute(PlantComponent* plant, PlantAttributes* attr)
{
	if (plant != nullptr && attr != nullptr)
	{
		plant->addAttribute(attr);
	}
}

// Plant Cloning
PlantComponent* NurseryFacade::clonePlant(PlantComponent* plant)
{
	if (plant == nullptr)
	{
		return nullptr;
	}
	return plant->clone();
}

// Inventory Operations
void NurseryFacade::addToInventory(PlantComponent* plant)
{
	if (plant != nullptr && inventory != nullptr)
	{
		PlantGroup* inv = inventory->getInventory();
		if (inv != nullptr)
		{
			inv->addComponent(plant);
		}
	}
}

void NurseryFacade::removeFromInventory(PlantComponent* plant)
{
	if (plant != nullptr && inventory != nullptr)
	{
		PlantGroup* inv = inventory->getInventory();
		if (inv != nullptr)
		{
			inv->removeComponent(plant);
		}
	}
}

// Iterator Creation
Iterator* NurseryFacade::createAllPlantsIterator()
{
	if (inventory == nullptr)
	{
		return nullptr;
	}

	PlantGroup* inv = inventory->getInventory();
	if (inv == nullptr)
	{
		return nullptr;
	}

	std::list<PlantComponent*>* plants = inv->getPlants();
	if (plants == nullptr)
	{
		return nullptr;
	}

	// Create AggPlant aggregate with plant list and return iterator
	AggPlant* aggregate = new AggPlant(plants);
	return aggregate->createIterator();
}

Iterator* NurseryFacade::createSeasonIterator(const char* season)
{
	if (inventory == nullptr || season == nullptr)
	{
		return nullptr;
	}

	PlantGroup* inv = inventory->getInventory();
	if (inv == nullptr)
	{
		return nullptr;
	}

	std::list<PlantComponent*>* plants = inv->getPlants();
	if (plants == nullptr)
	{
		return nullptr;
	}

	// Create AggSeason aggregate with season filter
	std::string seasonStr(season);
	AggSeason* aggregate = new AggSeason(plants, seasonStr);
	return aggregate->createIterator();
}

// Observer Management
void NurseryFacade::attachStaffToGroup(PlantGroup* group, Staff* staff)
{
	if (group != nullptr && staff != nullptr)
	{
		group->attach(staff);
	}
}

void NurseryFacade::detachStaffFromGroup(PlantGroup* group, Staff* staff)
{
	if (group != nullptr && staff != nullptr)
	{
		group->detach(staff);
	}
}

// Staff/Customer Management
void NurseryFacade::addStaff(Staff* staff)
{
	if (staff != nullptr && inventory != nullptr)
	{
		inventory->addStaff(staff);
	}
}

void NurseryFacade::addCustomer(Customer* customer)
{
	if (customer != nullptr && inventory != nullptr)
	{
		inventory->addCustomer(customer);
	}
}

std::vector<Staff*>* NurseryFacade::getStaff()
{
	if (inventory != nullptr)
	{
		return inventory->getStaff();
	}
	return nullptr;
}

std::vector<Customer*>* NurseryFacade::getCustomers()
{
	if (inventory != nullptr)
	{
		return inventory->getCustomers();
	}
	return nullptr;
}

// Group Notifications
void NurseryFacade::notifyWaterNeeded(PlantGroup* group)
{
	if (group != nullptr)
	{
		group->waterNeeded();
	}
}

void NurseryFacade::notifySunlightNeeded(PlantGroup* group)
{
	if (group != nullptr)
	{
		group->sunlightNeeded();
	}
}

void NurseryFacade::notifyStateUpdated(PlantGroup* group)
{
	if (group != nullptr)
	{
		group->stateUpdated();
	}
}
