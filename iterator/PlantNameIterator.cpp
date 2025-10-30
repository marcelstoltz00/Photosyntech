#include "PlantNameIterator.h"
#include "AggPlantName.h"

PlantNameIterator::PlantNameIterator(AggPlantName* aggregate) : currentPlant(nullptr), inComposite(false), pastEnd(false)
{
	this->aggregate = aggregate;
	first();
}

void PlantNameIterator::first()
{
	// Clear stack and reset state
	while (!traversalStack.empty()) {
		traversalStack.pop();
	}
	inComposite = false;
	pastEnd = false;  // Reset position flags

	// Cast aggregate to access plants member
	AggPlantName* nameAgg = static_cast<AggPlantName*>(aggregate);

	// Push root level frame
	StackFrame root;
	root.plantList = nameAgg->plants;
	root.current = nameAgg->plants->begin();
	root.end = nameAgg->plants->end();
	traversalStack.push(root);

	// Find first matching plant
	advanceToNextPlant();
}

void PlantNameIterator::next()
{
	if (traversalStack.empty()) {
		currentPlant = nullptr;
		return;
	}

	// Advance current position
	traversalStack.top().current++;
	advanceToNextPlant();
}

void PlantNameIterator::back()
{
	if (traversalStack.empty()) {
		// Use pastEnd flag to determine if we should go to last matching element
		if (pastEnd) {
			// We're past the end, go to last matching element
			findLastPlant();
		}
		// Otherwise we're before beginning, stay there (do nothing)
		return;
	}

	// Move back in current position
	moveToPreviousPlant();
}

bool PlantNameIterator::isDone()
{
	return currentPlant == nullptr;
}

LivingPlant* PlantNameIterator::currentItem()
{
	return currentPlant;
}

void PlantNameIterator::advanceToNextPlant()
{
	// Need to cast aggregate to access targetName
	AggPlantName* nameAgg = static_cast<AggPlantName*>(aggregate);

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

		// Found a living plant - check if it matches name
		if (type == ComponentType::LIVING_PLANT) {
			LivingPlant* plant = static_cast<LivingPlant*>(component);

			// Check name match using direct Flyweight pointer comparison
			// Flyweight pattern ensures same name strings share same pointer
			if (plant->getNameFlyweight() == nameAgg->targetName) {
				currentPlant = plant;
				return;
			}

			// Doesn't match name - skip it
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
	pastEnd = true;  // We moved past the end
}

void PlantNameIterator::moveToPreviousPlant()
{
	// Need to cast aggregate to access targetName
	AggPlantName* nameAgg = static_cast<AggPlantName*>(aggregate);

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
						LivingPlant* plant = static_cast<LivingPlant*>(component);
						// Check name match
						if (plant->getNameFlyweight() == nameAgg->targetName) {
							currentPlant = plant;
							return;
						}
					}
				}
			}
			continue;
		}

		// Handle position movement: only move back if not just descended
		if (frame.justDescended) {
			// We just descended into this frame, so current is already at the last element
			// Clear the flag and check this element first before moving back
			frame.justDescended = false;
		} else {
			// Normal backward movement
			frame.current--;
		}

		PlantComponent* component = *frame.current;
		ComponentType type = component->getType();

		// Found a living plant - check if it matches name
		if (type == ComponentType::LIVING_PLANT) {
			LivingPlant* plant = static_cast<LivingPlant*>(component);

			// Check name match using direct Flyweight pointer comparison
			if (plant->getNameFlyweight() == nameAgg->targetName) {
				currentPlant = plant;
				return;
			}

			// Doesn't match name - continue backwards
			continue;
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
			childFrame.justDescended = true;  // Mark that we just descended
			traversalStack.push(childFrame);
			inComposite = true;

			// Continue to find the actual matching plant in this group
			continue;
		}

		// Unknown type - skip it
		continue;
	}

	// Stack exhausted - moved before beginning
	currentPlant = nullptr;
	inComposite = false;
	pastEnd = false;  // We moved before the beginning
}

void PlantNameIterator::findLastPlant()
{
	// Clear stack and reset state
	while (!traversalStack.empty()) {
		traversalStack.pop();
	}
	inComposite = false;
	currentPlant = nullptr;
	pastEnd = false;  // Reset flag since we're positioning at a valid element

	// Cast aggregate to access plants member and target name
	AggPlantName* nameAgg = static_cast<AggPlantName*>(aggregate);

	if (nameAgg->plants->empty()) {
		return;
	}

	// Start from the root level at the last element
	StackFrame root;
	root.plantList = nameAgg->plants;
	root.end = nameAgg->plants->end();
	root.current = nameAgg->plants->end();
	--root.current;  // Move to last element
	traversalStack.push(root);

	// Navigate to the deepest last matching plant
	while (!traversalStack.empty()) {
		StackFrame& frame = traversalStack.top();

		PlantComponent* component = *frame.current;
		ComponentType type = component->getType();

		// Found a living plant - check if it matches name
		if (type == ComponentType::LIVING_PLANT) {
			LivingPlant* plant = static_cast<LivingPlant*>(component);

			// Check name match using Flyweight pointer comparison
			if (plant->getNameFlyweight() == nameAgg->targetName) {
				currentPlant = plant;
				pastEnd = false;  // At valid position
				return;
			}

			// Doesn't match - try previous element
			if (frame.current == frame.plantList->begin()) {
				traversalStack.pop();
				inComposite = !traversalStack.empty();
			} else {
				--frame.current;
			}
			continue;
		}

		// Found a plant group - descend to its last element
		if (type == ComponentType::PLANT_GROUP) {
			PlantGroup* group = static_cast<PlantGroup*>(component);
			std::list<PlantComponent*>* children = group->getPlants();

			if (children->empty()) {
				// Empty group, move back at this level
				if (frame.current == frame.plantList->begin()) {
					traversalStack.pop();
					inComposite = !traversalStack.empty();
					continue;
				}
				--frame.current;
				continue;
			}

			// Push child frame starting at end
			StackFrame childFrame;
			childFrame.plantList = children;
			childFrame.end = children->end();
			childFrame.current = children->end();
			--childFrame.current;  // Move to last element
			traversalStack.push(childFrame);
			inComposite = true;
			continue;
		}

		// Unknown type or can't find plant - try previous
		if (frame.current == frame.plantList->begin()) {
			traversalStack.pop();
			inComposite = !traversalStack.empty();
		} else {
			--frame.current;
		}
	}

	// Couldn't find any matching plant
	currentPlant = nullptr;
	inComposite = false;
	pastEnd = false;
}
