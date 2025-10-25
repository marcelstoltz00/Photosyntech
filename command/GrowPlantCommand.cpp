#include "GrowPlantCommand.h"
#include "../prototype/LivingPlant.h"
#include "../state/PlantMemento.h"
#include "../singleton/Singleton.h"
#include "../state/MaturityState.h"
#include "../composite/PlantGroup.h"
#include <stdexcept>

GrowPlantCommand::GrowPlantCommand(LivingPlant *plant)
	: plant(plant), memento(nullptr)
{
	if (plant == nullptr)
	{
		throw std::invalid_argument("GrowPlantCommand: plant cannot be null");
	}
}

void GrowPlantCommand::execute()
{
	if (plant == nullptr)
	{
		throw std::runtime_error("GrowPlantCommand::execute(): plant is null");
	}

	// Create memento of current plant state before growth
	memento = new PlantMemento(plant);

	// Get the current maturity state from the plant's flyweight
	if (plant->maturityState == nullptr)
	{
		delete memento;
		memento = nullptr;
		throw std::runtime_error("GrowPlantCommand::execute(): plant has no maturity state");
	}

	MaturityState *currentState = plant->maturityState->getState();
	if (currentState == nullptr)
	{
		delete memento;
		memento = nullptr;
		throw std::runtime_error("GrowPlantCommand::execute(): maturity state is null");
	}

	// Execute growth via the State pattern
	currentState->grow(plant);

	// Notify observers of the state change via the global inventory's plant group
	PlantGroup *inventory = Inventory::getInstance()->getInventory();
	if (inventory != nullptr)
	{
		inventory->stateUpdated();
	}
}

void GrowPlantCommand::undo()
{
	if (plant == nullptr)
	{
		throw std::runtime_error("GrowPlantCommand::undo(): plant is null");
	}

	if (memento == nullptr)
	{
		throw std::runtime_error("GrowPlantCommand::undo(): no memento available (execute was not called?)");
	}

	// Restore plant state from memento
	memento->restoreState(plant);

	// Notify observers of the state restoration
	PlantGroup *inventory = Inventory::getInstance()->getInventory();
	if (inventory != nullptr)
	{
		inventory->stateUpdated();
	}

	// Delete memento after restoration
	delete memento;
	memento = nullptr;
}

GrowPlantCommand::~GrowPlantCommand()
{
	// Clean up memento if it still exists
	if (memento != nullptr)
	{
		delete memento;
		memento = nullptr;
	}
}
