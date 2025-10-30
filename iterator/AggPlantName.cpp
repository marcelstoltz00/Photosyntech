#include "AggPlantName.h"
#include "../singleton/Singleton.h"

AggPlantName::AggPlantName(std::list<PlantComponent*>* plants, const std::string& name) : Aggregate(plants)
{
	// Convert string to Flyweight pointer via Singleton
	targetName = Inventory::getInstance()->getString(name);
}

AggPlantName::AggPlantName(std::list<PlantComponent*>* plants, Flyweight<std::string*>* name) : Aggregate(plants)
{
	// Directly assign the Flyweight pointer
	targetName = name;
}

Iterator* AggPlantName::createIterator()
{
	return new PlantNameIterator(this);
}
