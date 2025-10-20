#include "PlantIterator.h"

PlantIterator::PlantIterator(std::list<PlantComponent*>* plants)
{
	this->plants = plants;
	first();
}

void PlantIterator::first()
{
	current = plants->begin();
}

void PlantIterator::next()
{
	++current;
}

bool PlantIterator::isDone()
{
	return current == plants->end();
}

LivingPlant* PlantIterator::currentItem()
{
	return dynamic_cast<LivingPlant*>(*current);
}
