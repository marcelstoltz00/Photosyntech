#include "AggWinter.h"

Iterator* AggWinter::createIterator(std::list<PlantComponent*>* plants)
{
	return new WinterIterator(plants);
}
