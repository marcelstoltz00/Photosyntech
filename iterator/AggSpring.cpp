#include "AggSpring.h"

AggSpring::AggSpring(std::list<PlantComponent*>* plants, const std::string& season) : Aggregate(plants)
{
	targetSeason = season;
}

Iterator* AggSpring::createIterator()
{
	return new SpringIterator(this);
}
