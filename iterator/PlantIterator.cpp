#include "PlantIterator.h"
#include "AggPlant.h"

PlantIterator::PlantIterator(AggPlant* aggregate)
{
	this->aggregate = aggregate;
	first();
}

void PlantIterator::first()
{
	currentIndex = 0;
}

void PlantIterator::next()
{
	++currentIndex;
}

bool PlantIterator::isDone()
{
	return currentIndex >= (int)aggregate->plants->size();
}

LivingPlant* PlantIterator::currentItem()
{
	auto it = aggregate->plants->begin();
	for (int i = 0; i < currentIndex; ++i) {
		++it;
	}
	return dynamic_cast<LivingPlant*>(*it);
}
