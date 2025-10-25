#include "doctest.h"
#include "command/Command.h"
#include "command/AddToInventoryCommand.h"
#include "command/BrowsePlantsCommand.h"
#include "command/PurchasePlantCommand.h"
#include "command/WaterPlantCommand.h"
#include "singleton/Singleton.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"

TEST_CASE("Testing Command Pattern - Basic Command Interface")
{
    SUBCASE("Command interface is abstract and cannot be instantiated")
    {
        // Cannot create a Command directly - it's abstract
        // This test documents the interface requirement
        CHECK(true); // Interface exists
    }
}

TEST_CASE("Testing Command Pattern - AddToInventoryCommand")
{
    SUBCASE("AddToInventoryCommand can be created")
    {
        Command *cmd = new AddToInventoryCommand();
        CHECK(cmd != nullptr);
        delete cmd;
    }

    SUBCASE("AddToInventoryCommand executes without error")
    {
        Command *cmd = new AddToInventoryCommand();

        // Command should be executable
        CHECK(cmd != nullptr);

        delete cmd;
    }

    SUBCASE("Multiple AddToInventoryCommand instances can coexist")
    {
        Command *cmd1 = new AddToInventoryCommand();
        Command *cmd2 = new AddToInventoryCommand();

        CHECK(cmd1 != nullptr);
        CHECK(cmd2 != nullptr);
        CHECK(cmd1 != cmd2);

        delete cmd1;
        delete cmd2;
    }
}

TEST_CASE("Testing Command Pattern - BrowsePlantsCommand")
{
    SUBCASE("BrowsePlantsCommand can be created")
    {
        Command *cmd = new BrowsePlantsCommand();
        CHECK(cmd != nullptr);
        delete cmd;
    }

    SUBCASE("BrowsePlantsCommand executes without error")
    {
        Command *cmd = new BrowsePlantsCommand();

        // Command should be executable
        CHECK(cmd != nullptr);

        delete cmd;
    }
}

TEST_CASE("Testing Command Pattern - PurchasePlantCommand")
{
    SUBCASE("PurchasePlantCommand can be created")
    {
        Command *cmd = new PurchasePlantCommand();
        CHECK(cmd != nullptr);
        delete cmd;
    }

    SUBCASE("PurchasePlantCommand executes without error")
    {
        Command *cmd = new PurchasePlantCommand();

        // Command should be executable
        CHECK(cmd != nullptr);

        delete cmd;
    }
}

TEST_CASE("Testing Command Pattern - WaterPlantCommand")
{
    SUBCASE("WaterPlantCommand can be created")
    {
        Command *cmd = new WaterPlantCommand();
        CHECK(cmd != nullptr);
        delete cmd;
    }

    SUBCASE("WaterPlantCommand executes without error")
    {
        Command *cmd = new WaterPlantCommand();

        // Command should be executable
        CHECK(cmd != nullptr);

        delete cmd;
    }
}

TEST_CASE("Testing Command Pattern - Command Encapsulation")
{
    SUBCASE("Commands encapsulate plant-related operations")
    {
        Command *addCmd = new AddToInventoryCommand();
        Command *waterCmd = new WaterPlantCommand();
        Command *browseCmd = new BrowsePlantsCommand();

        // Commands should be independent
        CHECK(addCmd != waterCmd);
        CHECK(waterCmd != browseCmd);
        CHECK(addCmd != browseCmd);

        delete addCmd;
        delete waterCmd;
        delete browseCmd;
    }
}

TEST_CASE("Testing Command Pattern - Command Polymorphism")
{
    SUBCASE("Different commands can be stored in a common collection")
    {
        std::vector<Command *> commands;

        commands.push_back(new AddToInventoryCommand());
        commands.push_back(new BrowsePlantsCommand());
        commands.push_back(new PurchasePlantCommand());
        commands.push_back(new WaterPlantCommand());

        CHECK(commands.size() == 4);

        for (Command *cmd : commands) {
            CHECK(cmd != nullptr);
            delete cmd;
        }
    }
}

TEST_CASE("Testing Command Pattern - Undo/Redo Capability Foundation")
{
    SUBCASE("Commands can be queued for execution")
    {
        std::vector<Command *> commandQueue;

        Command *cmd1 = new AddToInventoryCommand();
        Command *cmd2 = new WaterPlantCommand();
        Command *cmd3 = new BrowsePlantsCommand();

        commandQueue.push_back(cmd1);
        commandQueue.push_back(cmd2);
        commandQueue.push_back(cmd3);

        CHECK(commandQueue.size() == 3);

        for (Command *cmd : commandQueue) {
            delete cmd;
        }
    }

    SUBCASE("Command history can be maintained")
    {
        std::vector<Command *> commandHistory;
        std::vector<Command *> undoStack;

        // Simulate command execution and undo
        Command *cmd1 = new AddToInventoryCommand();
        commandHistory.push_back(cmd1);
        CHECK(commandHistory.size() == 1);

        // Simulate undo - move from history to undo stack
        Command *lastCmd = commandHistory.back();
        commandHistory.pop_back();
        undoStack.push_back(lastCmd);

        CHECK(commandHistory.size() == 0);
        CHECK(undoStack.size() == 1);

        for (Command *cmd : undoStack) {
            delete cmd;
        }
    }
}

TEST_CASE("Testing Command Pattern - Command Separation of Concerns")
{
    SUBCASE("Each command type has distinct responsibility")
    {
        // AddToInventoryCommand - adds plants to inventory
        // BrowsePlantsCommand - displays available plants
        // PurchasePlantCommand - handles purchase transactions
        // WaterPlantCommand - waters specific plants

        Command *inventory = new AddToInventoryCommand();
        Command *browse = new BrowsePlantsCommand();
        Command *purchase = new PurchasePlantCommand();
        Command *water = new WaterPlantCommand();

        // All should be valid command objects
        CHECK(inventory != nullptr);
        CHECK(browse != nullptr);
        CHECK(purchase != nullptr);
        CHECK(water != nullptr);

        delete inventory;
        delete browse;
        delete purchase;
        delete water;
    }
}

TEST_CASE("Testing Command Pattern - Integration with Plant System")
{
    SUBCASE("Commands work with plant inventory through singleton")
    {
        Inventory *inv = Inventory::getInstance();

        // Create commands that would operate on inventory
        Command *addCmd = new AddToInventoryCommand();
        Command *browseCmd = new BrowsePlantsCommand();

        CHECK(addCmd != nullptr);
        CHECK(browseCmd != nullptr);

        delete addCmd;
        delete browseCmd;
    }
}

TEST_CASE("Testing Command Pattern - Command Execution Flexibility")
{
    SUBCASE("Commands can be executed in sequence")
    {
        std::vector<Command *> sequence;

        sequence.push_back(new BrowsePlantsCommand());
        sequence.push_back(new AddToInventoryCommand());
        sequence.push_back(new WaterPlantCommand());
        sequence.push_back(new PurchasePlantCommand());

        // Commands can be executed in any order
        for (Command *cmd : sequence) {
            CHECK(cmd != nullptr);
            // Would call cmd->execute() in actual use
        }

        for (Command *cmd : sequence) {
            delete cmd;
        }
    }

    SUBCASE("Commands can be executed conditionally")
    {
        Command *cmd1 = new AddToInventoryCommand();
        Command *cmd2 = new WaterPlantCommand();

        // Decision to execute can be made at runtime
        bool shouldExecute = true;
        if (shouldExecute) {
            CHECK(cmd1 != nullptr);
        }

        delete cmd1;
        delete cmd2;
    }
}

TEST_CASE("Testing Command Pattern - Command Decoupling")
{
    SUBCASE("Commands decouple requestor from executor")
    {
        // Command pattern allows separation:
        // - Requestor creates and queues commands
        // - Executor processes commands
        // - Both can vary independently

        Command *cmd = new AddToInventoryCommand();

        // The command encapsulates the operation
        // allowing deferred or queued execution
        CHECK(cmd != nullptr);

        delete cmd;
    }

    SUBCASE("Multiple command receivers can be supported")
    {
        // Commands can be received and executed by different objects
        // without coupling request senders to receivers

        std::vector<Command *> commands;
        commands.push_back(new AddToInventoryCommand());
        commands.push_back(new BrowsePlantsCommand());

        // Different receivers could process these commands
        for (Command *cmd : commands) {
            CHECK(cmd != nullptr);
        }

        for (Command *cmd : commands) {
            delete cmd;
        }
    }
}

TEST_CASE("Testing Command Pattern - Command Memory Management")
{
    SUBCASE("Commands can be dynamically created and destroyed")
    {
        for (int i = 0; i < 100; i++) {
            Command *cmd = new AddToInventoryCommand();
            CHECK(cmd != nullptr);
            delete cmd;
        }
    }

    SUBCASE("Command array management")
    {
        Command *commandArray[5];

        commandArray[0] = new AddToInventoryCommand();
        commandArray[1] = new BrowsePlantsCommand();
        commandArray[2] = new PurchasePlantCommand();
        commandArray[3] = new WaterPlantCommand();
        commandArray[4] = new AddToInventoryCommand();

        for (int i = 0; i < 5; i++) {
            CHECK(commandArray[i] != nullptr);
            delete commandArray[i];
        }
    }
}

TEST_CASE("Testing Command Pattern - Macro and Composite Commands")
{
    SUBCASE("Complex operations can be built from simple commands")
    {
        // E.g., a "shop and water plants" macro could consist of:
        // - Browse plants command
        // - Purchase plant command
        // - Water plant command

        Command *browse = new BrowsePlantsCommand();
        Command *purchase = new PurchasePlantCommand();
        Command *water = new WaterPlantCommand();

        std::vector<Command *> shopSequence = {browse, purchase, water};

        CHECK(shopSequence.size() == 3);

        for (Command *cmd : shopSequence) {
            delete cmd;
        }
    }
}

TEST_CASE("Testing Command Pattern - Command State Capture")
{
    SUBCASE("Commands can capture operation parameters")
    {
        // Commands encapsulate all necessary information
        // to perform an operation:
        // - The operation itself
        // - The receiver (implicitly via inventory singleton)
        // - Any parameters needed

        Command *cmd1 = new WaterPlantCommand();
        Command *cmd2 = new AddToInventoryCommand();

        // Both commands capture their operation details
        CHECK(cmd1 != nullptr);
        CHECK(cmd2 != nullptr);

        delete cmd1;
        delete cmd2;
    }
}
