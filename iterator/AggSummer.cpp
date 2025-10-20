#include "AggSummer.h"

AggSummer::AggSummer(std::list<PlantComponent*>* plants) : Aggregate(plants)
{
}

Iterator* AggSummer::createIterator()
{
	return new SummerIterator(this);
}
