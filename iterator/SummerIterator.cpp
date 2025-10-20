#include "SummerIterator.h"

SummerIterator::SummerIterator(std::list<PlantComponent*>* plants)
{
	this->plants = plants;
	first();
}

void SummerIterator::first()
{
	current = plants->begin();
}

void SummerIterator::next()
{
	++current;
}

bool SummerIterator::isDone()
{
	return current == plants->end();
}

LivingPlant* SummerIterator::currentItem()
{
	return dynamic_cast<LivingPlant*>(*current);
}
