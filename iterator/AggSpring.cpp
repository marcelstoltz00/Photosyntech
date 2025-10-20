#include "AggSpring.h"

Iterator* AggSpring::createIterator(std::list<PlantComponent*>* plants)
{
	return new SpringIterator(plants);
}
