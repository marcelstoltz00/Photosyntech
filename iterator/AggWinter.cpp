#include "AggWinter.h"

AggWinter::AggWinter(std::list<PlantComponent*>* plants) : Aggregate(plants)
{
}

Iterator* AggWinter::createIterator()
{
	return new WinterIterator(this);
}
