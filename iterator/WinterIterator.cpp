#include "WinterIterator.h"
#include "AggWinter.h"
#include "../prototype/LivingPlant.h"

WinterIterator::WinterIterator(AggWinter* aggregate)
{
	this->aggregate = aggregate;
	first();
}

void WinterIterator::first()
{
	currentIndex = -1;
	next();
}

void WinterIterator::next()
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

bool WinterIterator::isDone()
{
	return currentIndex >= (int)aggregate->plants->size();
}

LivingPlant* WinterIterator::currentItem()
{
	auto it = aggregate->plants->begin();
	for (int i = 0; i < currentIndex; ++i) {
		++it;
	}
	return dynamic_cast<LivingPlant*>(*it);
}
