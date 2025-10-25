#include "CreatePlantCommand.h"
#include "../builder/Director.h"
#include "../builder/Builder.h"
#include "../builder/RoseBuilder.h"
#include "../builder/CactusBuilder.h"
#include "../builder/SunflowerBuilder.h"
#include "../builder/PineBuilder.h"
#include "../builder/MapleBuilder.h"
#include "../builder/JadePlantBuilder.h"
#include "../builder/LavenderBuilder.h"
#include "../builder/CherryBlossomBuilder.h"
#include "../singleton/Singleton.h"
#include "../composite/PlantGroup.h"
#include <stdexcept>
#include <sstream>

CreatePlantCommand::CreatePlantCommand(const char *species)
	: species(species), createdPlant(nullptr)
{
	if (species == nullptr)
	{
		throw std::invalid_argument("CreatePlantCommand: species cannot be null");
	}
}

Builder *CreatePlantCommand::createBuilder(const std::string &speciesName)
{
	if (speciesName == "Rose")
		return new RoseBuilder();
	if (speciesName == "Cactus")
		return new CactusBuilder();
	if (speciesName == "Sunflower")
		return new SunflowerBuilder();
	if (speciesName == "Pine")
		return new PineBuilder();
	if (speciesName == "Maple")
		return new MapleBuilder();
	if (speciesName == "JadePlant")
		return new JadePlantBuilder();
	if (speciesName == "Lavender")
		return new LavenderBuilder();
	if (speciesName == "CherryBlossom")
		return new CherryBlossomBuilder();

	// Unknown species
	std::stringstream ss;
	ss << "CreatePlantCommand: Unknown species '" << speciesName << "'. "
	   << "Available species: Rose, Cactus, Sunflower, Pine, Maple, JadePlant, Lavender, CherryBlossom";
	throw std::invalid_argument(ss.str());
}

void CreatePlantCommand::execute()
{
	if (species.empty())
	{
		throw std::runtime_error("CreatePlantCommand::execute(): species is empty");
	}

	// Create appropriate builder for the species
	Builder *builder = nullptr;
	try
	{
		builder = createBuilder(species);
	}
	catch (const std::invalid_argument &e)
	{
		throw e;
	}

	if (builder == nullptr)
	{
		throw std::runtime_error("CreatePlantCommand::execute(): failed to create builder");
	}

	// Create director and construct the plant
	Director director(builder);
	director.construct();

	// Get the created plant
	createdPlant = director.getPlant();
	if (createdPlant == nullptr)
	{
		delete builder;
		throw std::runtime_error("CreatePlantCommand::execute(): director failed to create plant");
	}

	// Add to inventory
	PlantGroup *inventory = Inventory::getInstance()->getInventory();
	if (inventory == nullptr)
	{
		delete createdPlant;
		createdPlant = nullptr;
		delete builder;
		throw std::runtime_error("CreatePlantCommand::execute(): inventory is null");
	}

	inventory->addComponent(createdPlant);

	// Clean up builder (it's no longer needed after construction)
	delete builder;
}

void CreatePlantCommand::undo()
{
	if (createdPlant == nullptr)
	{
		throw std::runtime_error("CreatePlantCommand::undo(): no plant was created (execute was not called?)");
	}

	// Get inventory
	PlantGroup *inventory = Inventory::getInstance()->getInventory();
	if (inventory == nullptr)
	{
		throw std::runtime_error("CreatePlantCommand::undo(): inventory is null");
	}

	// Remove plant from inventory
	inventory->removeComponent(createdPlant);

	// Delete decorators
	PlantComponent *decorator = createdPlant->getDecorator();
	if (decorator != nullptr && decorator != createdPlant)
	{
		delete decorator;
	}

	// Delete the plant itself
	delete createdPlant;
	createdPlant = nullptr;
}

PlantComponent* CreatePlantCommand::getCreatedPlant() const
{
	return createdPlant;
}
