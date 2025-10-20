#include "AggSpring.h"

AggSpring::AggSpring(std::list<PlantComponent*>* plants) : Aggregate(plants)
{
}

Iterator* AggSpring::createIterator()
{
	return new SpringIterator(this);
}
