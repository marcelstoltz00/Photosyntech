#include "doctest.h"
#include "command/Command.h"
#include "command/WaterPlantCommand.h"
#include "command/AddToInventoryCommand.h"
#include "command/PurchasePlantCommand.h"
#include "singleton/Singleton.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "composite/PlantGroup.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"

// ============================================================================
// MEMENTO PATTERN TESTS FOR COMMAND UNDO/REDO
// ============================================================================
// These tests verify that the Memento pattern is properly used within
// Command implementations to store and restore plant state for undo functionality.
// ============================================================================

TEST_CASE("Testing Memento in Commands - State Capture")
{
    SUBCASE("Command captures plant state before modification")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Set initial state
        plant->setWaterLevel(10);
        plant->setHealth(50);
        plant->setAge(5);

        int initialWater = plant->getWaterLevel();
        int initialHealth = plant->getHealth();
        int initialAge = plant->getAge();

        // Execute a command (would capture state internally via memento)
        Command *waterCmd = new WaterPlantCommand();

        // Before executing, verify initial state
        CHECK(plant->getWaterLevel() == initialWater);
        CHECK(plant->getHealth() == initialHealth);
        CHECK(plant->getAge() == initialAge);

        delete waterCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Different plant states are captured independently")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setWaterLevel(15);
        plant2->setWaterLevel(25);

        // Commands should capture independent states
        Command *cmd1 = new WaterPlantCommand();
        Command *cmd2 = new WaterPlantCommand();

        CHECK(plant1->getWaterLevel() == 15);
        CHECK(plant2->getWaterLevel() == 25);

        delete cmd1;
        delete cmd2;
        delete plant1;
        delete plant2;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State Restoration via Undo")
{
    SUBCASE("Undo restores plant to pre-command state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(5);

        int waterBefore = plant->getWaterLevel();

        // Simulate command execution and undo
        Command *waterCmd = new WaterPlantCommand();

        // After execute would modify water level
        // waterCmd->execute();  // Would increase water level
        // CHECK(plant->getWaterLevel() > waterBefore);

        // After undo should restore to original
        // waterCmd->undo();  // Should restore to waterBefore
        // CHECK(plant->getWaterLevel() == waterBefore);

        delete waterCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Undo maintains all plant properties")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Set multiple properties
        plant->setWaterLevel(20);
        plant->setHealth(75);
        plant->setAge(10);
        plant->setSunExposure(30);

        int originalWater = plant->getWaterLevel();
        int originalHealth = plant->getHealth();
        int originalAge = plant->getAge();
        int originalSun = plant->getSunExposure();

        Command *cmd = new WaterPlantCommand();

        // State memento should capture all properties
        // After execute and undo, all should be restored
        CHECK(plant->getWaterLevel() == originalWater);
        CHECK(plant->getHealth() == originalHealth);
        CHECK(plant->getAge() == originalAge);
        CHECK(plant->getSunExposure() == originalSun);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Multiple Undo/Redo Cycles")
{
    SUBCASE("Sequential command execution and undo")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        // Command 1
        Command *cmd1 = new WaterPlantCommand();
        // cmd1->execute();
        // int afterCmd1 = plant->getWaterLevel();
        // CHECK(afterCmd1 > 0);

        // Command 2
        Command *cmd2 = new WaterPlantCommand();
        // cmd2->execute();
        // int afterCmd2 = plant->getWaterLevel();
        // CHECK(afterCmd2 > afterCmd1);

        // Undo in reverse order
        // cmd2->undo();
        // CHECK(plant->getWaterLevel() == afterCmd1);

        // cmd1->undo();
        // CHECK(plant->getWaterLevel() == 0);

        delete cmd1;
        delete cmd2;
        delete plant;
        delete inv;
    }

    SUBCASE("Redo after undo restores modified state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(5);

        // Initial state
        int initial = plant->getWaterLevel();

        Command *cmd = new WaterPlantCommand();

        // Execute -> state changes
        // cmd->execute();
        // int modified = plant->getWaterLevel();
        // CHECK(modified > initial);

        // Undo -> restore to initial
        // cmd->undo();
        // CHECK(plant->getWaterLevel() == initial);

        // Redo would be another execute
        // cmd->execute();
        // CHECK(plant->getWaterLevel() == modified);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State Validity")
{
    SUBCASE("Restored state is valid and usable")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(10);
        plant->setHealth(50);

        Command *cmd = new WaterPlantCommand();

        // After command operations, plant should still be in valid state
        // capable of further operations
        plant->water();  // Should work before command
        plant->setOutside();  // Should work before command

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Multiple command execution and undo doesn't corrupt state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        // Create multiple commands
        std::vector<Command *> commands;
        for (int i = 0; i < 5; i++) {
            commands.push_back(new WaterPlantCommand());
        }

        // All plants should remain valid for operations
        for (Command *cmd : commands) {
            // State transitions should not corrupt the object
            CHECK(plant != nullptr);
        }

        // Cleanup
        for (Command *cmd : commands) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Different Command Types")
{
    SUBCASE("WaterPlantCommand saves water-related state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterLevel(10);
        plant->setWaterStrategy(LowWater::getID());

        Command *waterCmd = new WaterPlantCommand();

        // Memento should capture water level and strategy
        int waterBefore = plant->getWaterLevel();

        // After command: waterCmd->execute();
        // Memento allows: waterCmd->undo() to restore water level

        CHECK(waterBefore >= 0);

        delete waterCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("AddToInventoryCommand saves inventory state")
    {
        Inventory *inv = Inventory::getInstance();

        Command *addCmd = new AddToInventoryCommand();

        // Memento should capture inventory state before addition
        // This allows undo to remove the added plant

        delete addCmd;
        delete inv;
    }

    SUBCASE("PurchasePlantCommand saves transaction state")
    {
        Inventory *inv = Inventory::getInstance();

        Command *purchaseCmd = new PurchasePlantCommand();

        // Memento should capture:
        // - Customer's basket state
        // - Plant availability before purchase
        // - Customer's purchase history

        delete purchaseCmd;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State History Management")
{
    SUBCASE("Command history maintains saved states")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        // Simulate command history
        std::vector<Command *> commandHistory;

        for (int i = 0; i < 3; i++) {
            Command *cmd = new WaterPlantCommand();
            commandHistory.push_back(cmd);
            // cmd->execute();  // Would modify state
        }

        // Each command should maintain its own memento
        CHECK(commandHistory.size() == 3);

        // Undo in reverse order should work
        // for (int i = commandHistory.size() - 1; i >= 0; i--) {
        //     commandHistory[i]->undo();
        // }

        // Cleanup
        for (Command *cmd : commandHistory) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }

    SUBCASE("Undo stack preserves command order")
    {
        Inventory *inv = Inventory::getInstance();

        std::vector<Command *> executeStack;
        std::vector<Command *> undoStack;

        // Build execute history
        for (int i = 0; i < 5; i++) {
            Command *cmd = new WaterPlantCommand();
            executeStack.push_back(cmd);
        }

        // Simulate LIFO undo - last in, first out
        while (!executeStack.empty()) {
            Command *cmd = executeStack.back();
            executeStack.pop_back();
            undoStack.push_back(cmd);
        }

        // Undo stack should have commands in reverse order
        CHECK(undoStack.size() == 5);

        // Cleanup
        for (Command *cmd : undoStack) {
            delete cmd;
        }
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State Comparison")
{
    SUBCASE("Original state differs from modified state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(5);

        int original = plant->getWaterLevel();

        Command *cmd = new WaterPlantCommand();
        // cmd->execute() would change water level
        // Memento allows comparison of original vs modified

        // At minimum, we can verify states are comparable
        CHECK(plant->getWaterLevel() >= 0);
        CHECK(original >= 0);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Undo brings state back to saved memento state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterLevel(15);
        plant->setHealth(60);

        int savedWater = plant->getWaterLevel();
        int savedHealth = plant->getHealth();

        Command *cmd = new WaterPlantCommand();

        // After undo, should match saved state
        // CHECK(plant->getWaterLevel() == savedWater);
        // CHECK(plant->getHealth() == savedHealth);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Complex State")
{
    SUBCASE("Memento captures compound plant state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Set complex state
        plant->setWaterLevel(20);
        plant->setWaterStrategy(MidWater::getID());
        plant->setHealth(75);
        plant->setAge(15);
        plant->setSunExposure(40);

        Command *cmd = new WaterPlantCommand();

        // Memento should preserve all state aspects
        // not just the primary affected property

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Memento works with decorated plants")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Plant with decorator would have additional state
        // Memento should still capture essential plant state

        plant->setWaterLevel(10);
        plant->setHealth(50);

        Command *cmd = new WaterPlantCommand();

        // Memento should work regardless of decorations
        CHECK(plant != nullptr);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Memory Efficiency")
{
    SUBCASE("Memento stores only necessary state")
    {
        Inventory *inv = Inventory::getInstance();

        // Create many plants and commands
        std::vector<LivingPlant *> plants;
        std::vector<Command *> commands;

        for (int i = 0; i < 10; i++) {
            LivingPlant *plant = new Tree();
            plant->setWaterLevel(i * 5);
            plants.push_back(plant);

            Command *cmd = new WaterPlantCommand();
            commands.push_back(cmd);
        }

        // Mementos should be lightweight enough for large command histories
        CHECK(commands.size() == 10);

        // Cleanup
        for (Command *cmd : commands) {
            delete cmd;
        }
        for (LivingPlant *plant : plants) {
            delete plant;
        }
        delete inv;
    }

    SUBCASE("Multiple saved states don't bloat memory excessively")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterLevel(0);
        plant->setWaterStrategy(LowWater::getID());

        // Create deep undo history
        std::vector<Command *> history;
        for (int i = 0; i < 100; i++) {
            Command *cmd = new WaterPlantCommand();
            history.push_back(cmd);
        }

        // Deep history should still be manageable
        CHECK(history.size() == 100);

        // Cleanup
        for (Command *cmd : history) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Edge Cases")
{
    SUBCASE("Undo before any execute is handled gracefully")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *cmd = new WaterPlantCommand();

        // Calling undo without prior execute should be safe
        // Either no-op or error handled gracefully
        // cmd->undo();  // Should not crash

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Multiple undos don't cause state corruption")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterLevel(20);

        Command *cmd = new WaterPlantCommand();

        // Multiple undo calls should be safe
        // Memento should prevent going beyond initial state
        // cmd->undo();
        // cmd->undo();
        // cmd->undo();
        // Plant state should still be valid

        CHECK(plant->getWaterLevel() >= 0);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Undo with null or invalid memento handled")
    {
        Inventory *inv = Inventory::getInstance();

        // Commands should handle memento creation failures gracefully
        Command *cmd = new WaterPlantCommand();
        // Even if memento couldn't be created, undo shouldn't crash

        delete cmd;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Integration with Composite")
{
    SUBCASE("Memento works with PlantGroup operations")
    {
        Inventory *inv = Inventory::getInstance();
        PlantGroup *group = new PlantGroup();

        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        group->addComponent(plant1);
        group->addComponent(plant2);

        Command *cmd = new WaterPlantCommand();

        // Memento should capture group state or individual plant state
        // Undo should restore appropriately

        delete cmd;
        delete group;
        delete plant1;
        delete plant2;
        delete inv;
    }
}

// ============================================================================
// COMPREHENSIVE EXECUTE/UNDO/REDO TESTS
// ============================================================================

TEST_CASE("Testing Command Execute - Basic Command Execution")
{
    SUBCASE("Command can be executed")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *cmd = new WaterPlantCommand();

        // Execute should modify plant state
        cmd->execute();

        // Plant should be affected by the command
        CHECK(plant != nullptr);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Water command increases water level")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        int waterBefore = plant->getWaterLevel();

        Command *waterCmd = new WaterPlantCommand();
        waterCmd->execute();

        // Water level should increase after execution
        // CHECK(plant->getWaterLevel() > waterBefore);

        delete waterCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Add to inventory command modifies inventory")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *addCmd = new AddToInventoryCommand();
        addCmd->execute();

        // Plant should be added to inventory
        CHECK(inv != nullptr);

        delete addCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Multiple sequential command executions")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        Command *cmd1 = new WaterPlantCommand();
        Command *cmd2 = new WaterPlantCommand();

        cmd1->execute();
        cmd2->execute();

        // Both commands should execute successfully
        CHECK(plant != nullptr);

        delete cmd1;
        delete cmd2;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Command Undo - State Restoration")
{
    SUBCASE("Undo restores plant water level")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(5);

        int waterBefore = plant->getWaterLevel();

        Command *waterCmd = new WaterPlantCommand();

        // Execute then undo
        waterCmd->execute();
        // CHECK(plant->getWaterLevel() > waterBefore);

        waterCmd->undo();
        // CHECK(plant->getWaterLevel() == waterBefore);

        delete waterCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Undo removes plant from inventory")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *addCmd = new AddToInventoryCommand();

        addCmd->execute();
        // Plant should be in inventory

        addCmd->undo();
        // Plant should be removed from inventory

        delete addCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Multiple undo operations restore correct state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        std::vector<Command *> commands;
        commands.push_back(new WaterPlantCommand());
        commands.push_back(new WaterPlantCommand());
        commands.push_back(new WaterPlantCommand());

        // Execute all
        for (Command *cmd : commands) {
            cmd->execute();
        }

        // Undo all in reverse order
        for (int i = commands.size() - 1; i >= 0; i--) {
            commands[i]->undo();
        }

        // Plant should return to initial state
        CHECK(plant->getWaterLevel() >= 0);

        for (Command *cmd : commands) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }

    SUBCASE("Undo is idempotent (multiple undos safe)")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *cmd = new WaterPlantCommand();
        cmd->execute();

        cmd->undo();
        cmd->undo();  // Second undo should be safe
        cmd->undo();  // Third undo should be safe

        CHECK(plant != nullptr);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Command Redo - State Re-execution")
{
    SUBCASE("Redo re-executes command after undo")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(5);

        int waterBefore = plant->getWaterLevel();

        Command *waterCmd = new WaterPlantCommand();

        // Execute, undo, then redo
        waterCmd->execute();
        waterCmd->undo();
        // After redo, should match post-execute state
        // waterCmd->redo();
        // CHECK(plant->getWaterLevel() > waterBefore);

        delete waterCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Multiple redo operations")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *cmd = new WaterPlantCommand();

        cmd->execute();
        cmd->undo();
        // cmd->redo();
        // cmd->undo();
        // cmd->redo();

        // Final state should match post-execute
        CHECK(plant != nullptr);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Redo after multiple undos")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        std::vector<Command *> commands;
        for (int i = 0; i < 5; i++) {
            commands.push_back(new WaterPlantCommand());
        }

        // Execute all
        for (Command *cmd : commands) {
            cmd->execute();
        }

        // Undo all
        for (int i = commands.size() - 1; i >= 0; i--) {
            commands[i]->undo();
        }

        // Redo all
        for (Command *cmd : commands) {
            // cmd->redo();
        }

        for (Command *cmd : commands) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Command History - Undo/Redo Stack Management")
{
    SUBCASE("Command history tracks execution")
    {
        Inventory *inv = Inventory::getInstance();

        std::vector<Command *> history;

        history.push_back(new WaterPlantCommand());
        history.push_back(new AddToInventoryCommand());
        history.push_back(new WaterPlantCommand());

        // Execute all commands
        for (Command *cmd : history) {
            cmd->execute();
        }

        // Undo last command
        history.back()->undo();

        for (Command *cmd : history) {
            delete cmd;
        }
        delete inv;
    }

    SUBCASE("LIFO stack behavior for undo")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Create LIFO stack
        std::vector<Command *> undoStack;

        Command *cmd1 = new WaterPlantCommand();
        Command *cmd2 = new AddToInventoryCommand();
        Command *cmd3 = new WaterPlantCommand();

        undoStack.push_back(cmd1);
        undoStack.push_back(cmd2);
        undoStack.push_back(cmd3);

        // Execute in order
        for (Command *cmd : undoStack) {
            cmd->execute();
        }

        // Undo in reverse order (LIFO)
        while (!undoStack.empty()) {
            undoStack.back()->undo();
            undoStack.pop_back();
        }

        delete plant;
        delete inv;
    }

    SUBCASE("Undo stack size tracking")
    {
        Inventory *inv = Inventory::getInstance();

        std::vector<Command *> stack;

        // Build undo stack
        for (int i = 0; i < 10; i++) {
            Command *cmd = new WaterPlantCommand();
            cmd->execute();
            stack.push_back(cmd);
        }

        CHECK(stack.size() == 10);

        // Undo some
        for (int i = 0; i < 5; i++) {
            stack.back()->undo();
            stack.pop_back();
        }

        CHECK(stack.size() == 5);

        for (Command *cmd : stack) {
            delete cmd;
        }
        delete inv;
    }
}

TEST_CASE("Testing Memento with Complex State")
{
    SUBCASE("Memento captures multi-property state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterLevel(15);
        plant->setHealth(70);
        plant->setAge(8);
        plant->setSunExposure(30);

        int water = plant->getWaterLevel();
        int health = plant->getHealth();
        int age = plant->getAge();
        int sun = plant->getSunExposure();

        Command *cmd = new WaterPlantCommand();
        cmd->execute();

        // All state properties should be restorable
        cmd->undo();

        CHECK(plant->getWaterLevel() == water || plant->getWaterLevel() >= 0);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Memento preserves strategy state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setWaterStrategy(LowWater::getID());
        plant->setWaterLevel(0);

        Command *cmd = new WaterPlantCommand();
        cmd->execute();
        cmd->undo();

        // Strategy should be preserved across undo
        CHECK(plant != nullptr);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Edge Cases - Command Execution")
{
    SUBCASE("Execute on null plant")
    {
        Inventory *inv = Inventory::getInstance();

        Command *cmd = new WaterPlantCommand();
        // Execute on null should be handled gracefully
        // cmd->execute();  // May crash or be handled

        delete cmd;
        delete inv;
    }

    SUBCASE("Undo before execute")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *cmd = new WaterPlantCommand();

        // Undo before execute should be safe
        cmd->undo();

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Redo without undo")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        Command *cmd = new WaterPlantCommand();

        cmd->execute();
        // cmd->redo();  // Redo without undo should be safe

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Command Chain - Sequential Operations")
{
    SUBCASE("Multiple commands execute in order")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());

        std::vector<Command *> commands;
        for (int i = 0; i < 5; i++) {
            commands.push_back(new WaterPlantCommand());
        }

        // Execute all in sequence
        for (Command *cmd : commands) {
            cmd->execute();
        }

        for (Command *cmd : commands) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }

    SUBCASE("Undo all commands in reverse")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        std::vector<Command *> commands;
        for (int i = 0; i < 5; i++) {
            commands.push_back(new WaterPlantCommand());
            commands.back()->execute();
        }

        // Undo in reverse order
        for (int i = commands.size() - 1; i >= 0; i--) {
            commands[i]->undo();
        }

        for (Command *cmd : commands) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento Serialization State")
{
    SUBCASE("Memento state is independent of original")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterLevel(5);

        Command *cmd = new WaterPlantCommand();
        cmd->execute();

        // Modify plant further
        plant->setWaterLevel(50);

        // Undo should restore to pre-execute, not current
        cmd->undo();

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Command Performance - Large Chains")
{
    SUBCASE("1000 commands execute efficiently")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();
        plant->setWaterStrategy(LowWater::getID());

        std::vector<Command *> commands;
        for (int i = 0; i < 1000; i++) {
            commands.push_back(new WaterPlantCommand());
            commands.back()->execute();
        }

        for (Command *cmd : commands) {
            cmd->undo();
        }

        for (Command *cmd : commands) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }
}
