#include "SeasonIterator.h"
#include "AggSeason.h"

SeasonIterator::SeasonIterator(AggSeason* aggregate) : currentPlant(nullptr)
{
	this->aggregate = aggregate;
	first();
}

void SeasonIterator::first()
{
	currentPlant = findNextMatch(aggregate->plants, true);
}

void SeasonIterator::next()
{
	currentPlant = findNextMatch(aggregate->plants, false);
}

bool SeasonIterator::isDone()
{
	return currentPlant == nullptr;
}

LivingPlant* SeasonIterator::currentItem()
{
	return currentPlant;
}

LivingPlant* SeasonIterator::findNextMatch(std::list<PlantComponent*>* plants, bool findFirst)
{
	for (auto component : *plants) {
		// Try to cast to LivingPlant
		LivingPlant* plant = dynamic_cast<LivingPlant*>(component);

		if (plant != nullptr) {
			// It's a LivingPlant, check if it matches season
			if (plant->getSeason() == aggregate->targetSeason) {
				if (findFirst) {
					return plant;
				}
				if (plant == currentPlant) {
					// We found the current plant, switch to finding mode
					findFirst = true;
					continue;  // Skip current, look for next
				}
			}
		} else {
			// Not a LivingPlant, try to cast to PlantGroup
			PlantGroup* group = dynamic_cast<PlantGroup*>(component);
			if (group != nullptr) {
				// Recursively search the group's plants
				LivingPlant* found = findNextMatch(group->getPlants(), findFirst);
				if (found != nullptr) {
					return found;
				}
				// If nothing found in this group, continue to next component
			}
		}
	}

	return nullptr;
}
