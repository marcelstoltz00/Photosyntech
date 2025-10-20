#include "SpringIterator.h"

SpringIterator::SpringIterator(std::list<PlantComponent*>* plants)
{
	this->plants = plants;
	first();
}

void SpringIterator::first()
{
	current = plants->begin();
}

void SpringIterator::next()
{
	++current;
}

bool SpringIterator::isDone()
{
	return current == plants->end();
}

LivingPlant* SpringIterator::currentItem()
{
	return dynamic_cast<LivingPlant*>(*current);
}
