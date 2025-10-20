#include "SummerIterator.h"
#include "AggSummer.h"
#include "../prototype/LivingPlant.h"

SummerIterator::SummerIterator(AggSummer* aggregate)
{
	this->aggregate = aggregate;
	first();
}

void SummerIterator::first()
{
	currentIndex = -1;
	next();
}

void SummerIterator::next()
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

bool SummerIterator::isDone()
{
	return currentIndex >= (int)aggregate->plants->size();
}

LivingPlant* SummerIterator::currentItem()
{
	auto it = aggregate->plants->begin();
	for (int i = 0; i < currentIndex; ++i) {
		++it;
	}
	return dynamic_cast<LivingPlant*>(*it);
}
