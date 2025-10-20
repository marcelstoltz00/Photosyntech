#include "SpringIterator.h"
#include "AggSpring.h"
#include "../prototype/LivingPlant.h"

SpringIterator::SpringIterator(AggSpring* aggregate)
{
	this->aggregate = aggregate;
	first();
}

void SpringIterator::first()
{
	currentIndex = -1;
	next();
}

void SpringIterator::next()
{
	++currentIndex;
	while (!isDone()) {
		auto it = aggregate->plants->begin();
		for (int i = 0; i < currentIndex; ++i) {
			++it;
		}
		PlantComponent* component = *it;
		LivingPlant* plant = dynamic_cast<LivingPlant*>(component);

		if (plant != nullptr && plant->getSeason() == aggregate->targetSeason) {
			break;
		}
		++currentIndex;
	}
}

bool SpringIterator::isDone()
{
	return currentIndex >= (int)aggregate->plants->size();
}

LivingPlant* SpringIterator::currentItem()
{
	auto it = aggregate->plants->begin();
	for (int i = 0; i < currentIndex; ++i) {
		++it;
	}
	return dynamic_cast<LivingPlant*>(*it);
}
