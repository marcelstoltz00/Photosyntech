#include "AggSummer.h"

AggSummer::AggSummer(std::list<PlantComponent*>* plants, const std::string& season) : Aggregate(plants)
{
	targetSeason = season;
}

Iterator* AggSummer::createIterator()
{
	return new SummerIterator(this);
}
