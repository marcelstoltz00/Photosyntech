#include "SeasonIterator.h"
#include "AggSeason.h"

SeasonIterator::SeasonIterator(AggSeason* aggregate) : currentPlant(nullptr), inComposite(false)
{
	this->aggregate = aggregate;
	first();
}

void SeasonIterator::first()
{
	// Clear stack and reset state
	while (!traversalStack.empty()) {
		traversalStack.pop();
	}
	inComposite = false;

	// Push root level frame
	StackFrame root;
	root.plantList = aggregate->plants;
	root.current = aggregate->plants->begin();
	root.end = aggregate->plants->end();
	traversalStack.push(root);

	// Find first matching plant
	advanceToNextPlant();
}

void SeasonIterator::next()
{
	if (traversalStack.empty()) {
		currentPlant = nullptr;
		return;
	}

	// Advance current position
	traversalStack.top().current++;
	advanceToNextPlant();
}

bool SeasonIterator::isDone()
{
	return currentPlant == nullptr;
}

LivingPlant* SeasonIterator::currentItem()
{
	return currentPlant;
}

void SeasonIterator::advanceToNextPlant()
{
	// Need to cast aggregate to access targetSeason
	AggSeason* seasonAgg = static_cast<AggSeason*>(aggregate);

	while (!traversalStack.empty()) {
		StackFrame& frame = traversalStack.top();

		// Check if we've exhausted this level
		if (frame.current == frame.end) {
			traversalStack.pop();
			inComposite = !traversalStack.empty();
			continue;
		}

		PlantComponent* component = *frame.current;
		ComponentType type = component->getType();

		// Found a living plant - check if it matches season
		if (type == ComponentType::LIVING_PLANT) {
			LivingPlant* plant = static_cast<LivingPlant*>(component);

			// Check season match using direct Flyweight pointer comparison
			// Flyweight pattern ensures same season strings share same pointer
			if (plant->getSeason() == seasonAgg->targetSeason) {
				currentPlant = plant;
				return;
			}

			// Doesn't match season - skip it
			frame.current++;
			continue;
		}

		// Found a plant group - descend into it
		if (type == ComponentType::PLANT_GROUP) {
			PlantGroup* group = static_cast<PlantGroup*>(component);
			std::list<PlantComponent*>* children = group->getPlants();

			// Advance parent iterator before descending
			frame.current++;

			// Push child frame onto stack
			StackFrame childFrame;
			childFrame.plantList = children;
			childFrame.current = children->begin();
			childFrame.end = children->end();
			traversalStack.push(childFrame);
			inComposite = true;
			continue;
		}

		// Unknown type - skip it
		frame.current++;
	}

	// Stack exhausted - no more matching plants
	currentPlant = nullptr;
	inComposite = false;
}
