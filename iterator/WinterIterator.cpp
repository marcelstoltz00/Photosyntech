#include "WinterIterator.h"

WinterIterator::WinterIterator(std::list<PlantComponent*>* plants)
{
	this->plants = plants;
	first();
}

void WinterIterator::first()
{
	current = plants->begin();
}

void WinterIterator::next()
{
	++current;
}

bool WinterIterator::isDone()
{
	return current == plants->end();
}

LivingPlant* WinterIterator::currentItem()
{
	return dynamic_cast<LivingPlant*>(*current);
}
