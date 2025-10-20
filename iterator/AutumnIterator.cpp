#include "AutumnIterator.h"

AutumnIterator::AutumnIterator(std::list<PlantComponent*>* plants)
{
	this->plants = plants;
	first();
}

void AutumnIterator::first()
{
	current = plants->begin();
}

void AutumnIterator::next()
{
	++current;
}

bool AutumnIterator::isDone()
{
	return current == plants->end();
}

LivingPlant* AutumnIterator::currentItem()
{
	return dynamic_cast<LivingPlant*>(*current);
}
