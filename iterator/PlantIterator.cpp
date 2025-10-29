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
	if (traversalStack.empty()) {
		currentPlant = nullptr;
		return;
	}

	// Advance current position
	traversalStack.top().current++;
	advanceToNextPlant();
}

void PlantIterator::back()
{
	if (traversalStack.empty()) {
		currentPlant = nullptr;
		return;
	}

	// Move back in current position
	moveToPreviousPlant();
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

void PlantIterator::moveToPreviousPlant()
{
	while (!traversalStack.empty()) {
		StackFrame& frame = traversalStack.top();

		// Check if we're at the beginning of this level
		if (frame.current == frame.plantList->begin()) {
			// Pop this level and return to parent
			traversalStack.pop();
			inComposite = !traversalStack.empty();

			if (!traversalStack.empty()) {
				// We're back at parent level, need to go back one more
				StackFrame& parentFrame = traversalStack.top();
				if (parentFrame.current != parentFrame.plantList->begin()) {
					parentFrame.current--;

					PlantComponent* component = *parentFrame.current;
					if (component->getType() == ComponentType::LIVING_PLANT) {
						currentPlant = static_cast<LivingPlant*>(component);
						return;
					}
				}
			}
			continue;
		}

		// Move back one position
		frame.current--;

		PlantComponent* component = *frame.current;
		ComponentType type = component->getType();

		// Found a living plant - return it
		if (type == ComponentType::LIVING_PLANT) {
			currentPlant = static_cast<LivingPlant*>(component);
			return;
		}

		// Found a plant group - descend into it and go to the last element
		if (type == ComponentType::PLANT_GROUP) {
			PlantGroup* group = static_cast<PlantGroup*>(component);
			std::list<PlantComponent*>* children = group->getPlants();

			if (children->empty()) {
				// Empty group, skip it and continue backwards
				continue;
			}

			// Push child frame onto stack, starting at the end
			StackFrame childFrame;
			childFrame.plantList = children;
			childFrame.current = children->end();
			childFrame.end = children->end();
			childFrame.current--;  // Move to last element
			traversalStack.push(childFrame);
			inComposite = true;

			// Continue to find the actual plant in this group
			continue;
		}

		// Unknown type - skip it
		continue;
	}

	// Stack exhausted - no more plants
	currentPlant = nullptr;
	inComposite = false;
}
