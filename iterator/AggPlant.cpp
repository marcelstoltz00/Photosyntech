#include "AggPlant.h"

AggPlant::AggPlant(std::list<PlantComponent*>* plants) : Aggregate(plants)
{
}

Iterator* AggPlant::createIterator()
{
	return new PlantIterator(this);
}
