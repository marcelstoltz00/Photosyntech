#include "AggSeason.h"

AggSeason::AggSeason(std::list<PlantComponent*>* plants, const std::string& season) : Aggregate(plants)
{
	targetSeason = season;
}

Iterator* AggSeason::createIterator()
{
	return new SeasonIterator(this);
}
