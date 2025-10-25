#include "AddPlantToBasketCommand.h"
#include "../mediator/Customer.h"
#include "../composite/PlantGroup.h"
#include <stdexcept>

AddPlantToBasketCommand::AddPlantToBasketCommand(Customer *customer, PlantComponent *plant)
	: customer(customer), plant(plant), basketWasNull(false)
{
	if (customer == nullptr)
	{
		throw std::invalid_argument("AddPlantToBasketCommand: customer cannot be null");
	}
	if (plant == nullptr)
	{
		throw std::invalid_argument("AddPlantToBasketCommand: plant cannot be null");
	}
}

void AddPlantToBasketCommand::execute()
{
	if (customer == nullptr)
	{
		throw std::runtime_error("AddPlantToBasketCommand::execute(): customer is null");
	}
	if (plant == nullptr)
	{
		throw std::runtime_error("AddPlantToBasketCommand::execute(): plant is null");
	}

	// Check if basket exists before adding
	basketWasNull = (customer->getBasket() == nullptr);

	// Add plant to basket (creates basket if it doesn't exist)
	customer->addPlant(plant);
}

void AddPlantToBasketCommand::undo()
{
	if (customer == nullptr)
	{
		throw std::runtime_error("AddPlantToBasketCommand::undo(): customer is null");
	}
	if (plant == nullptr)
	{
		throw std::runtime_error("AddPlantToBasketCommand::undo(): plant is null");
	}

	// Get the basket to remove the plant from
	PlantGroup *basket = customer->getBasket();
	if (basket == nullptr)
	{
		throw std::runtime_error("AddPlantToBasketCommand::undo(): basket is null (execute was not called?)");
	}

	// Remove plant from basket
	basket->removeComponent(plant);

	// If we created the basket, clear it
	if (basketWasNull)
	{
		customer->clearBasket();
	}
}
