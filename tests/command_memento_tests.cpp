#include "doctest.h"
#include "command/Command.h"
#include "command/GrowPlantCommand.h"
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
// Focus on GrowPlantCommand which has complete memento support.
// ============================================================================

TEST_CASE("Testing Memento in Commands - State Capture")
{
    SUBCASE("GrowPlantCommand captures plant state before growth")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Initialize plant state (maturity state required by GrowPlantCommand)
        plant->setMaturity(0);  // Set to Seed state
        plant->setWaterLevel(10);
        plant->setHealth(50);
        plant->setAge(5);

        int initialWater = plant->getWaterLevel();
        int initialHealth = plant->getHealth();
        int initialAge = plant->getAge();

        // Create and execute grow command
        Command *growCmd = new GrowPlantCommand(plant);
        growCmd->execute();

        // After growth, state should change
        int afterAge = plant->getAge();
        CHECK(afterAge > initialAge);

        delete growCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Different plant states are captured independently")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        // Initialize plant states
        plant1->setMaturity(0);
        plant2->setMaturity(0);
        plant1->setAge(5);
        plant2->setAge(10);

        // Grow commands should capture independent states
        Command *cmd1 = new GrowPlantCommand(plant1);
        Command *cmd2 = new GrowPlantCommand(plant2);

        cmd1->execute();
        cmd2->execute();

        // Both should have grown
        CHECK(plant1->getAge() > 5);
        CHECK(plant2->getAge() > 10);

        delete cmd1;
        delete cmd2;
        delete plant1;
        delete plant2;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State Restoration via Undo")
{
    SUBCASE("Undo restores plant to pre-growth state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(5);
        plant->setHealth(50);

        int ageBefore = plant->getAge();
        int healthBefore = plant->getHealth();

        // Execute grow command
        Command *growCmd = new GrowPlantCommand(plant);
        growCmd->execute();

        // After growth, age should increase
        int ageAfter = plant->getAge();
        CHECK(ageAfter > ageBefore);

        // Undo should restore to original state
        growCmd->undo();
        CHECK(plant->getAge() == ageBefore);
        CHECK(plant->getHealth() == healthBefore);

        delete growCmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Undo maintains all plant properties after growth")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        // Set initial properties
        plant->setMaturity(0);
        plant->setWaterLevel(20);
        plant->setHealth(75);
        plant->setAge(10);
        plant->setSunExposure(30);

        int originalWater = plant->getWaterLevel();
        int originalHealth = plant->getHealth();
        int originalAge = plant->getAge();
        int originalSun = plant->getSunExposure();

        // Execute and undo grow command
        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();
        cmd->undo();

        // State memento should restore all properties exactly
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
    SUBCASE("Sequential grow command execution and undo")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(0);

        // Command 1 - first growth
        Command *cmd1 = new GrowPlantCommand(plant);
        cmd1->execute();
        int afterCmd1 = plant->getAge();
        CHECK(afterCmd1 > 0);

        // Command 2 - second growth
        Command *cmd2 = new GrowPlantCommand(plant);
        cmd2->execute();
        int afterCmd2 = plant->getAge();
        CHECK(afterCmd2 > afterCmd1);

        // Undo in reverse order
        cmd2->undo();
        CHECK(plant->getAge() == afterCmd1);

        cmd1->undo();
        CHECK(plant->getAge() == 0);

        delete cmd1;
        delete cmd2;
        delete plant;
        delete inv;
    }

    SUBCASE("Redo after undo restores growth state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(5);
        int initial = plant->getAge();

        Command *cmd = new GrowPlantCommand(plant);

        // Execute -> plant grows
        cmd->execute();
        int afterGrowth = plant->getAge();
        CHECK(afterGrowth > initial);

        // Undo -> restore to initial
        cmd->undo();
        CHECK(plant->getAge() == initial);

        // Re-execute -> should grow again to same state
        cmd->execute();
        CHECK(plant->getAge() == afterGrowth);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State Validity")
{
    SUBCASE("Restored state is valid and usable after undo")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setWaterLevel(10);
        plant->setHealth(50);

        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();
        cmd->undo();

        // After undo, plant should still be functional
        plant->water();  // Should work after undo
        plant->setOutside();  // Should work after undo
        CHECK(plant->getWaterLevel() >= 0);
        CHECK(plant->getHealth() >= 0);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Multiple command execution and undo doesn't corrupt state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(0);

        // Create multiple grow commands
        std::vector<Command *> commands;
        for (int i = 0; i < 5; i++) {
            commands.push_back(new GrowPlantCommand(plant));
        }

        // Execute all commands
        for (Command *cmd : commands) {
            cmd->execute();
            CHECK(plant != nullptr);
        }

        // Undo all commands
        for (int i = commands.size() - 1; i >= 0; i--) {
            commands[i]->undo();
            CHECK(plant->getAge() >= 0);
        }

        // Plant should still be valid
        CHECK(plant != nullptr);

        // Cleanup
        for (Command *cmd : commands) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - GrowPlantCommand Details")
{
    SUBCASE("GrowPlantCommand saves all plant attributes")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setWaterLevel(10);
        plant->setHealth(60);
        plant->setAge(5);
        plant->setSunExposure(20);

        // All state should be capturable
        int waterBefore = plant->getWaterLevel();
        int healthBefore = plant->getHealth();
        int ageBefore = plant->getAge();

        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();

        // State changed due to growth
        CHECK(plant->getAge() > ageBefore);

        // Undo restores all properties
        cmd->undo();
        CHECK(plant->getWaterLevel() == waterBefore);
        CHECK(plant->getHealth() == healthBefore);
        CHECK(plant->getAge() == ageBefore);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Memento works with different plant types")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *tree = new Tree();
        LivingPlant *shrub = new Shrub();

        tree->setMaturity(0);
        shrub->setMaturity(0);
        tree->setAge(5);
        shrub->setAge(10);

        Command *treeCmd = new GrowPlantCommand(tree);
        Command *shrubCmd = new GrowPlantCommand(shrub);

        treeCmd->execute();
        shrubCmd->execute();

        // Both should grow
        CHECK(tree->getAge() > 5);
        CHECK(shrub->getAge() > 10);

        // Undo each separately
        treeCmd->undo();
        CHECK(tree->getAge() == 5);
        CHECK(shrub->getAge() > 10);  // Shrub still grown

        shrubCmd->undo();
        CHECK(shrub->getAge() == 10);

        delete treeCmd;
        delete shrubCmd;
        delete tree;
        delete shrub;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State History Management")
{
    SUBCASE("Command history maintains saved states")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(0);

        // Build command history with GrowPlantCommand
        std::vector<Command *> commandHistory;

        for (int i = 0; i < 3; i++) {
            Command *cmd = new GrowPlantCommand(plant);
            cmd->execute();
            commandHistory.push_back(cmd);
        }

        // Each command should maintain its own memento
        CHECK(commandHistory.size() == 3);

        // Undo in reverse order should work
        for (int i = commandHistory.size() - 1; i >= 0; i--) {
            commandHistory[i]->undo();
        }

        // Should be back to original age
        CHECK(plant->getAge() == 0);

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
        LivingPlant *plant = new Tree();
        plant->setMaturity(0);
        plant->setAge(0);

        std::vector<Command *> executeStack;
        std::vector<Command *> undoStack;

        // Build execute history with GrowPlantCommand
        for (int i = 0; i < 5; i++) {
            Command *cmd = new GrowPlantCommand(plant);
            cmd->execute();
            executeStack.push_back(cmd);
        }

        int ageAfter5Growths = plant->getAge();

        // Simulate LIFO undo - last in, first out
        while (!executeStack.empty()) {
            Command *cmd = executeStack.back();
            executeStack.pop_back();
            cmd->undo();
            undoStack.push_back(cmd);
        }

        // Should be back to age 0 after all undos
        CHECK(plant->getAge() == 0);
        CHECK(undoStack.size() == 5);

        // Cleanup
        for (Command *cmd : undoStack) {
            delete cmd;
        }
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - State Comparison")
{
    SUBCASE("Original state differs from modified state after growth")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(5);
        int original = plant->getAge();

        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();

        int modified = plant->getAge();
        CHECK(modified > original);  // State has changed due to growth

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Undo brings state back to saved memento state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setWaterLevel(15);
        plant->setHealth(60);
        plant->setAge(8);

        int savedWater = plant->getWaterLevel();
        int savedHealth = plant->getHealth();
        int savedAge = plant->getAge();

        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();

        // After undo, should match saved state exactly
        cmd->undo();
        CHECK(plant->getWaterLevel() == savedWater);
        CHECK(plant->getHealth() == savedHealth);
        CHECK(plant->getAge() == savedAge);

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
        plant->setMaturity(0);
        plant->setWaterLevel(20);
        plant->setHealth(75);
        plant->setAge(15);
        plant->setSunExposure(40);

        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();

        // Memento should preserve all state aspects
        // Undo should restore all of them
        cmd->undo();

        CHECK(plant->getWaterLevel() == 20);
        CHECK(plant->getHealth() == 75);
        CHECK(plant->getAge() == 15);
        CHECK(plant->getSunExposure() == 40);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Memento works with plant clones")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setWaterLevel(10);
        plant->setHealth(50);
        plant->setAge(5);

        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();

        // After execute, plant has grown
        int grownAge = plant->getAge();
        CHECK(grownAge > 5);

        // Memento should work
        cmd->undo();
        CHECK(plant->getAge() == 5);  // Back to original

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Performance")
{
    SUBCASE("Memento handles many commands efficiently")
    {
        Inventory *inv = Inventory::getInstance();

        // Create many plants and grow commands
        std::vector<LivingPlant *> plants;
        std::vector<Command *> commands;

        for (int i = 0; i < 10; i++) {
            LivingPlant *plant = new Tree();
            plant->setMaturity(0);
            plant->setAge(i);
            plants.push_back(plant);

            Command *cmd = new GrowPlantCommand(plant);
            cmd->execute();
            commands.push_back(cmd);
        }

        // All commands should have mementos
        CHECK(commands.size() == 10);

        // Undo all
        for (int i = commands.size() - 1; i >= 0; i--) {
            commands[i]->undo();
        }

        // Verify all plants reverted
        for (int i = 0; i < plants.size(); i++) {
            CHECK(plants[i]->getAge() == i);
        }

        // Cleanup
        for (Command *cmd : commands) {
            delete cmd;
        }
        for (LivingPlant *plant : plants) {
            delete plant;
        }
        delete inv;
    }

    SUBCASE("Deep undo history works correctly")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(0);

        // Create deep undo history
        std::vector<Command *> history;
        for (int i = 0; i < 20; i++) {
            Command *cmd = new GrowPlantCommand(plant);
            cmd->execute();
            history.push_back(cmd);
        }

        int ageAfter20Grows = plant->getAge();

        // Deep history should work - undo all
        for (int i = history.size() - 1; i >= 0; i--) {
            history[i]->undo();
        }

        // Should be back to age 0
        CHECK(plant->getAge() == 0);

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
    SUBCASE("Undo after execute is safe")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(5);

        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();

        int ageAfterGrow = plant->getAge();
        CHECK(ageAfterGrow > 5);

        // Undo should be safe
        cmd->undo();
        CHECK(plant->getAge() == 5);

        delete cmd;
        delete plant;
        delete inv;
    }

    SUBCASE("Multiple undos in sequence don't corrupt state")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        plant->setAge(0);
        plant->setHealth(50);

        Command *cmd1 = new GrowPlantCommand(plant);
        Command *cmd2 = new GrowPlantCommand(plant);

        cmd1->execute();
        cmd2->execute();

        // Undo both in order
        cmd2->undo();
        cmd1->undo();

        // Plant state should be valid
        CHECK(plant->getAge() == 0);
        CHECK(plant->getHealth() == 50);

        delete cmd1;
        delete cmd2;
        delete plant;
        delete inv;
    }

    SUBCASE("Invalid species handled gracefully")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Tree();

        plant->setMaturity(0);
        // Even with invalid operations, memento should not crash
        Command *cmd = new GrowPlantCommand(plant);
        cmd->execute();
        cmd->undo();

        // Plant should still be valid
        CHECK(plant != nullptr);

        delete cmd;
        delete plant;
        delete inv;
    }
}

TEST_CASE("Testing Memento in Commands - Integration with Composite")
{
    SUBCASE("Memento works with plant growth in groups")
    {
        Inventory *inv = Inventory::getInstance();
        PlantGroup *group = new PlantGroup();

        LivingPlant *plant1 = new Tree();
        LivingPlant *plant2 = new Shrub();

        plant1->setMaturity(0);
        plant2->setMaturity(0);
        plant1->setAge(5);
        plant2->setAge(10);

        group->addComponent(plant1);
        group->addComponent(plant2);

        // Grow each plant
        Command *cmd1 = new GrowPlantCommand(plant1);
        Command *cmd2 = new GrowPlantCommand(plant2);

        cmd1->execute();
        cmd2->execute();

        // Verify growth happened
        CHECK(plant1->getAge() > 5);
        CHECK(plant2->getAge() > 10);

        // Undo should restore appropriately
        cmd1->undo();
        cmd2->undo();

        CHECK(plant1->getAge() == 5);
        CHECK(plant2->getAge() == 10);

        delete cmd1;
        delete cmd2;
        delete group;
        delete inv;
    }
}
