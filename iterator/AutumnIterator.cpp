#include "AutumnIterator.h"
#include "AggAutumn.h"
#include "../prototype/LivingPlant.h"

AutumnIterator::AutumnIterator(AggAutumn* aggregate)
{
	this->aggregate = aggregate;
	first();
}

void AutumnIterator::first()
{
	currentIndex = -1;
	next();
}

void AutumnIterator::next()
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

bool AutumnIterator::isDone()
{
	return currentIndex >= (int)aggregate->plants->size();
}

LivingPlant* AutumnIterator::currentItem()
{
	auto it = aggregate->plants->begin();
	for (int i = 0; i < currentIndex; ++i) {
		++it;
	}
	return dynamic_cast<LivingPlant*>(*it);
}
