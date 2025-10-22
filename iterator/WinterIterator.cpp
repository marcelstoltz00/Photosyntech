#include "WinterIterator.h"
#include "AggWinter.h"

WinterIterator::WinterIterator(AggWinter* aggregate) : currentPlant(nullptr)
{
	this->aggregate = aggregate;
	first();
}

void WinterIterator::first()
{
	currentPlant = findNextMatch(aggregate->plants, true);
}

void WinterIterator::next()
{
	currentPlant = findNextMatch(aggregate->plants, false);
}

bool WinterIterator::isDone()
{
	return currentPlant == nullptr;
}

LivingPlant* WinterIterator::currentItem()
{
	return currentPlant;
}

LivingPlant* WinterIterator::findNextMatch(std::list<PlantComponent*>* plants, bool findFirst)
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
