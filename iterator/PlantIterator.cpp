#include "PlantIterator.h"
#include "AggPlant.h"

PlantIterator::PlantIterator(AggPlant* aggregate) : currentPlant(nullptr), inComposite(false)
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

	// Push root level frame
	StackFrame root;
	root.plantList = aggregate->plants;
	root.current = aggregate->plants->begin();
	root.end = aggregate->plants->end();
	traversalStack.push(root);

	// Find first plant
	advanceToNextPlant();
}

void PlantIterator::next()
{
	if (traversalStack.empty()) {
		currentPlant = nullptr;
		return;
	}

	// Advance current position
	traversalStack.top().current++;
	advanceToNextPlant();
}

bool PlantIterator::isDone()
{
	return currentPlant == nullptr;
}

LivingPlant* PlantIterator::currentItem()
{
	return currentPlant;
}

void PlantIterator::advanceToNextPlant()
{
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

		// Found a living plant - return it
		if (type == ComponentType::LIVING_PLANT) {
			currentPlant = static_cast<LivingPlant*>(component);
			return;
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

	// Stack exhausted - no more plants
	currentPlant = nullptr;
	inComposite = false;
}
