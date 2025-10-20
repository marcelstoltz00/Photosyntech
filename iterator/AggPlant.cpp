#include "AggPlant.h"

Iterator* AggPlant::createIterator(std::list<PlantComponent*>* plants)
{
	return new PlantIterator(plants);
}
