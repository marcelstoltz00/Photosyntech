#include "AggAutumn.h"

AggAutumn::AggAutumn(std::list<PlantComponent*>* plants, const std::string& season) : Aggregate(plants)
{
	targetSeason = season;
}

Iterator* AggAutumn::createIterator()
{
	return new AutumnIterator(this);
}
