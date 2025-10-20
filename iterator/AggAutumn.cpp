#include "AggAutumn.h"

Iterator* AggAutumn::createIterator(std::list<PlantComponent*>* plants)
{
	return new AutumnIterator(plants);
}
