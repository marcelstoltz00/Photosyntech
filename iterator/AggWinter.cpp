#include "AggWinter.h"

AggWinter::AggWinter(std::list<PlantComponent*>* plants, const std::string& season) : Aggregate(plants)
{
	targetSeason = season;
}

Iterator* AggWinter::createIterator()
{
	return new WinterIterator(this);
}
