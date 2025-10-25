#include "PurchasePlantCommand.h"

void PurchasePlantCommand::execute()
{
    // Implementation: Process plant purchase
    // This would:
    // - Remove plant from inventory
    // - Update customer's plant list
    // - Store transaction details for undo
}

void PurchasePlantCommand::undo()
{
    // Implementation: Reverse the purchase
    // - Return plant to inventory
    // - Remove from customer's list
}
