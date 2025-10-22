#include "PlantIterator.h"
#include "AggPlant.h"

PlantIterator::PlantIterator(AggPlant* aggregate) : currentPlant(nullptr)
{
	this->aggregate = aggregate;
	first();
}

void PlantIterator::first()
{
	// Clear stack and reset state
	while (!traversalStack.empty()) {
		traversalStack.pop();
	}
	inComposite = false;

	// Cast aggregate to access plants member
	AggPlant* plantAgg = static_cast<AggPlant*>(aggregate);

	// Push root level frame
	StackFrame root;
	root.plantList = plantAgg->plants;
	root.current = plantAgg->plants->begin();
	root.end = plantAgg->plants->end();
	traversalStack.push(root);

	// Find first plant
	advanceToNextPlant();
}

void PlantIterator::next()
{
	currentPlant = findNextMatch(aggregate->plants, false);
}

bool PlantIterator::isDone()
{
	return currentPlant == nullptr;
}

LivingPlant* PlantIterator::currentItem()
{
	return currentPlant;
}

LivingPlant* PlantIterator::findNextMatch(std::list<PlantComponent*>* plants, bool findFirst)
{
	for (auto component : *plants) {
		// Try to cast to LivingPlant
		LivingPlant* plant = dynamic_cast<LivingPlant*>(component);

		if (plant != nullptr) {
			// It's a LivingPlant, return it if we're finding first or if it's the one after current
			if (findFirst) {
				return plant;
			}
			if (plant == currentPlant) {
				// We found the current plant, switch to finding mode
				findFirst = true;
				continue;  // Skip current, look for next
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
