#include "AggAutumn.h"

AggAutumn::AggAutumn(std::list<PlantComponent*>* plants) : Aggregate(plants)
{
}

Iterator* AggAutumn::createIterator()
{
	return new AutumnIterator(this);
}
