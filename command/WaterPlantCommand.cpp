#include "WaterPlantCommand.h"

void WaterPlantCommand::execute()
{
    // Implementation: Water a plant using its strategy
    // This would:
    // - Save pre-watering state (memento)
    // - Apply water using plant's WaterStrategy
    // - Notify observers of state change
}

void WaterPlantCommand::undo()
{
    // Implementation: Restore plant to pre-watering state
    // This would:
    // - Use stored memento to restore water level
    // - Notify observers of restoration
}
