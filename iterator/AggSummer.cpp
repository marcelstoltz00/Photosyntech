#include "AggSummer.h"

Iterator* AggSummer::createIterator(std::list<PlantComponent*>* plants)
{
	return new SummerIterator(plants);
}
