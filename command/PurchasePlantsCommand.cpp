#include "PurchasePlantsCommand.h"
#include "../mediator/Customer.h"
#include "../mediator/SalesFloor.h"
#include "../mediator/BasketMemento.h"
#include "../composite/PlantGroup.h"
#include "../singleton/Singleton.h"
#include <stdexcept>

PurchasePlantsCommand::PurchasePlantsCommand(Customer *customer, SalesFloor *salesFloor)
	: customer(customer), salesFloor(salesFloor), memento(nullptr), transactionComplete(false)
{
	if (customer == nullptr)
	{
		throw std::invalid_argument("PurchasePlantsCommand: customer cannot be null");
	}
	if (salesFloor == nullptr)
	{
		throw std::invalid_argument("PurchasePlantsCommand: salesFloor cannot be null");
	}
}

void PurchasePlantsCommand::execute()
{
	if (customer == nullptr)
	{
		throw std::runtime_error("PurchasePlantsCommand::execute(): customer is null");
	}
	if (salesFloor == nullptr)
	{
		throw std::runtime_error("PurchasePlantsCommand::execute(): salesFloor is null");
	}

	// Get customer's basket
	PlantGroup *basket = customer->getBasket();
	if (basket == nullptr)
	{
		throw std::runtime_error("PurchasePlantsCommand::execute(): customer has no basket");
	}

	// Validate basket is not empty
	std::list<PlantComponent *> *basketPlants = basket->getPlants();
	if (basketPlants == nullptr || basketPlants->empty())
	{
		throw std::runtime_error("PurchasePlantsCommand::execute(): basket is empty");
	}

	// Create memento of basket contents before transaction
	try
	{
		memento = new BasketMemento(customer);
	}
	catch (const std::exception &e)
	{
		throw std::runtime_error(std::string("PurchasePlantsCommand::execute(): failed to create memento: ") + e.what());
	}

	// Route purchase through sales floor mediator
	try
	{
		salesFloor->assist();
	}
	catch (const std::exception &e)
	{
		delete memento;
		memento = nullptr;
		throw std::runtime_error(std::string("PurchasePlantsCommand::execute(): mediator failed: ") + e.what());
	}

	// Transfer plants from inventory to purchased list
	// Make a copy of the basket plant list since we'll be modifying it
	std::list<PlantComponent *> plantsToTransfer = *basketPlants;

	PlantGroup *inventory = Inventory::getInstance()->getInventory();
	if (inventory == nullptr)
	{
		delete memento;
		memento = nullptr;
		throw std::runtime_error("PurchasePlantsCommand::execute(): inventory is null");
	}

	// Remove each plant from inventory and add to purchased list
	for (PlantComponent *plant : plantsToTransfer)
	{
		inventory->removeComponent(plant);
		purchasedPlants.push_back(plant);
	}

	// Clear customer's basket after purchase
	customer->clearBasket();

	// Mark transaction as complete
	transactionComplete = true;
}

void PurchasePlantsCommand::undo()
{
	if (customer == nullptr)
	{
		throw std::runtime_error("PurchasePlantsCommand::undo(): customer is null");
	}

	if (!transactionComplete)
	{
		throw std::runtime_error("PurchasePlantsCommand::undo(): transaction was not completed (execute was not called?)");
	}

	if (memento == nullptr)
	{
		throw std::runtime_error("PurchasePlantsCommand::undo(): no memento available");
	}

	// Restore basket from memento
	try
	{
		memento->restoreBasket(customer);
	}
	catch (const std::exception &e)
	{
		throw std::runtime_error(std::string("PurchasePlantsCommand::undo(): failed to restore basket: ") + e.what());
	}

	// Return purchased plants to inventory
	PlantGroup *inventory = Inventory::getInstance()->getInventory();
	if (inventory == nullptr)
	{
		throw std::runtime_error("PurchasePlantsCommand::undo(): inventory is null");
	}

	for (PlantComponent *plant : purchasedPlants)
	{
		inventory->addComponent(plant);
	}

	// Clear the purchased plants list
	purchasedPlants.clear();

	// Mark transaction as reversed
	transactionComplete = false;

	// Clean up memento after undo completes
	delete memento;
	memento = nullptr;
}

PurchasePlantsCommand::~PurchasePlantsCommand()
{
	// Clean up memento if it still exists
	if (memento != nullptr)
	{
		delete memento;
		memento = nullptr;
	}
}
