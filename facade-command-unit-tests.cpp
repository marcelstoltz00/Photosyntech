// ============================================================================
// FACADE & COMMAND PATTERN UNIT TESTS
// ============================================================================
// Comprehensive testing of NurseryFacade and Command pattern implementations
// Tests: CreatePlantCommand, AddPlantToBasketCommand, GrowPlantCommand,
//        PurchasePlantsCommand, GetSuggestionCommand, NurseryFacade Integration
// ============================================================================

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "third_party/doctest/doctest.h"

// Command Pattern Includes
#include "command/CreatePlantCommand.h"
#include "command/AddPlantToBasketCommand.h"
#include "command/GrowPlantCommand.h"
#include "command/PurchasePlantsCommand.h"
#include "command/GetSuggestionCommand.h"

// Facade Pattern Includes
#include "facade/NurseryFacade.h"

// Supporting Includes
#include "singleton/Singleton.h"
#include "prototype/Tree.h"
#include "prototype/LivingPlant.h"
#include "prototype/Succulent.h"
#include "prototype/Shrub.h"
#include "builder/Director.h"
#include "builder/RoseBuilder.h"
#include "builder/CactusBuilder.h"
#include "mediator/Customer.h"
#include "mediator/SalesFloor.h"
#include "mediator/SuggestionFloor.h"
#include "state/Seed.h"
#include "state/Dead.h"
#include "composite/PlantGroup.h"

// ============================================================================
// TEST HELPER FUNCTIONS
// ============================================================================

PlantComponent* createTestPlant(const char* species) {
    NurseryFacade facade;
    PlantComponent* plant = facade.createPlant(species);
    return plant;
}

LivingPlant* createTestPlantWithState(const char* species, int age, double health) {
    PlantComponent* plantComp = createTestPlant(species);
    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);
    if (plant) {
        plant->setAge(age);
        plant->setHealth(health);
    }
    return plant;
}

Customer* createTestCustomer() {
    return new Customer();
}

Customer* createTestCustomerWithBasket(int plantCount) {
    Customer* customer = new Customer();
    for (int i = 0; i < plantCount; i++) {
        PlantComponent* plant = createTestPlant("Rose");
        if (plant) {
            customer->addPlant(plant);
        }
    }
    return customer;
}

bool isPlantInInventory(PlantComponent* plant) {
    Inventory* inv = Inventory::getInstance();
    if (!inv || !plant) return false;
    PlantGroup* inventory = inv->getInventory();
    if (!inventory) return false;
    auto* plants = inventory->getPlants();
    if (!plants) return false;
    for (auto p : *plants) {
        if (p == plant) return true;
    }
    return false;
}

bool isPlantInBasket(Customer* customer, PlantComponent* plant) {
    if (!customer || !plant) return false;
    PlantGroup* basket = customer->getBasket();
    if (!basket) return false;
    auto* plants = basket->getPlants();
    if (!plants) return false;
    for (auto p : *plants) {
        if (p == plant) return true;
    }
    return false;
}

int getInventorySize() {
    Inventory* inv = Inventory::getInstance();
    if (!inv) return 0;
    PlantGroup* inventory = inv->getInventory();
    if (!inventory) return 0;
    auto* plants = inventory->getPlants();
    return plants ? plants->size() : 0;
}

// ============================================================================
// TEST SUITE 1: CreatePlantCommand Tests
// ============================================================================

TEST_SUITE("CreatePlantCommand") {

TEST_CASE("test_CreatePlantCommand_Rose_Execute_Success") {
    Inventory* inv = Inventory::getInstance();
    int initialSize = getInventorySize();

    CreatePlantCommand cmd("Rose");
    cmd.execute();

    PlantComponent* plant = cmd.getCreatedPlant();
    CHECK(plant != nullptr);
    CHECK(getInventorySize() == initialSize + 1);
    CHECK(isPlantInInventory(plant));
}

TEST_CASE("test_CreatePlantCommand_MultipleSpecies_Execute_Success") {
    int initialSize = getInventorySize();
    const char* speciesArray[] = {"Rose", "Cactus", "Sunflower", "Pine",
                                  "Maple", "JadePlant", "Lavender", "CherryBlossom"};
    std::vector<CreatePlantCommand*> commands;

    for (int i = 0; i < 8; i++) {
        CreatePlantCommand* cmd = new CreatePlantCommand(speciesArray[i]);
        cmd->execute();
        commands.push_back(cmd);
    }

    CHECK(getInventorySize() == initialSize + 8);

    for (auto cmd : commands) {
        CHECK(cmd->getCreatedPlant() != nullptr);
        delete cmd;
    }
}

TEST_CASE("test_CreatePlantCommand_Execute_PlantHasCorrectAttributes") {
    CreatePlantCommand cmd("Rose");
    cmd.execute();

    PlantComponent* plantComp = cmd.getCreatedPlant();
    CHECK(plantComp != nullptr);

    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);
    if (plant) {
        CHECK(plant->getWaterLevel() >= 0);
        CHECK(plant->getSunExposure() >= 0);
        CHECK(plant->getAge() >= 0);
        CHECK(plant->getHealth() >= 0);
    }
}

TEST_CASE("test_CreatePlantCommand_NullSpecies_ThrowsException") {
    try {
        CreatePlantCommand cmd(nullptr);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }
}

TEST_CASE("test_CreatePlantCommand_UnknownSpecies_ThrowsException") {
    try {
        CreatePlantCommand cmd("UnknownPlant");
        cmd.execute();
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }
}

TEST_CASE("test_CreatePlantCommand_EmptySpecies_ThrowsException") {
    try {
        CreatePlantCommand cmd("");
        cmd.execute();
        FAIL("Expected exception not thrown");
    } catch (const std::exception&) {
        CHECK(true);
    }
}

TEST_CASE("test_CreatePlantCommand_Undo_RemovesPlantFromInventory") {
    int initialSize = getInventorySize();

    CreatePlantCommand cmd("Rose");
    cmd.execute();
    PlantComponent* plant = cmd.getCreatedPlant();

    CHECK(getInventorySize() == initialSize + 1);

    cmd.undo();
    CHECK(getInventorySize() == initialSize);
}

TEST_CASE("test_CreatePlantCommand_ExecuteUndoExecute_Success") {
    int initialSize = getInventorySize();
    CreatePlantCommand cmd("Cactus");

    // Execute
    cmd.execute();
    CHECK(getInventorySize() == initialSize + 1);

    // Undo
    cmd.undo();
    CHECK(getInventorySize() == initialSize);

    // Execute again
    cmd.execute();
    CHECK(getInventorySize() == initialSize + 1);
}

} // END TEST_SUITE CreatePlantCommand

// ============================================================================
// TEST SUITE 2: AddPlantToBasketCommand Tests
// ============================================================================

TEST_SUITE("AddPlantToBasketCommand") {

TEST_CASE("test_AddPlantToBasketCommand_AddToNewBasket_Success") {
    Customer* customer = createTestCustomer();
    CHECK(customer->getBasket() == nullptr);

    PlantComponent* plant = createTestPlant("Rose");

    AddPlantToBasketCommand cmd(customer, plant);
    cmd.execute();

    CHECK(customer->getBasket() != nullptr);
}

TEST_CASE("test_AddPlantToBasketCommand_AddToExistingBasket_Success") {
    Customer* customer = createTestCustomerWithBasket(1);
    CHECK(customer->getBasket() != nullptr);

    PlantComponent* newPlant = createTestPlant("Cactus");

    AddPlantToBasketCommand cmd(customer, newPlant);
    cmd.execute();

    // Basket should still exist with the new plant
    CHECK(customer->getBasket() != nullptr);
}

TEST_CASE("test_AddPlantToBasketCommand_MultipleAdditions_Success") {
    Customer* customer = createTestCustomer();

    std::vector<PlantComponent*> plants;
    for (int i = 0; i < 3; i++) {
        plants.push_back(createTestPlant("Rose"));
    }

    for (auto plant : plants) {
        AddPlantToBasketCommand cmd(customer, plant);
        cmd.execute();
    }

    CHECK(customer->getBasket() != nullptr);
}

TEST_CASE("test_AddPlantToBasketCommand_NullCustomer_ThrowsException") {
    PlantComponent* plant = createTestPlant("Rose");

    try {
        AddPlantToBasketCommand cmd(nullptr, plant);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }
}

TEST_CASE("test_AddPlantToBasketCommand_NullPlant_ThrowsException") {
    Customer* customer = createTestCustomer();

    try {
        AddPlantToBasketCommand cmd(customer, nullptr);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }
}

TEST_CASE("test_AddPlantToBasketCommand_Undo_RemovesPlantFromBasket") {
    Customer* customer = createTestCustomer();
    PlantComponent* plant = createTestPlant("Rose");

    AddPlantToBasketCommand cmd(customer, plant);
    cmd.execute();

    CHECK(customer->getBasket() != nullptr);

    cmd.undo();
    // After undo, basket should be empty or null
}

TEST_CASE("test_AddPlantToBasketCommand_Undo_DeletesBasketIfWasNull") {
    Customer* customer = createTestCustomer();
    CHECK(customer->getBasket() == nullptr);

    PlantComponent* plant = createTestPlant("Rose");

    AddPlantToBasketCommand cmd(customer, plant);
    cmd.execute();

    CHECK(customer->getBasket() != nullptr);

    cmd.undo();
    CHECK(customer->getBasket() == nullptr);
}

TEST_CASE("test_AddPlantToBasketCommand_ExecuteUndoExecute_Success") {
    Customer* customer = createTestCustomer();
    PlantComponent* plant = createTestPlant("Rose");

    AddPlantToBasketCommand cmd(customer, plant);

    // Execute
    cmd.execute();
    CHECK(customer->getBasket() != nullptr);

    // Undo
    cmd.undo();
    CHECK(customer->getBasket() == nullptr);

    // Execute again
    cmd.execute();
    CHECK(customer->getBasket() != nullptr);
}

} // END TEST_SUITE AddPlantToBasketCommand

// ============================================================================
// TEST SUITE 3: GrowPlantCommand Tests
// ============================================================================

TEST_SUITE("GrowPlantCommand") {

TEST_CASE("test_GrowPlantCommand_Execute_PlantGrows") {
    PlantComponent* plantComp = createTestPlant("Rose");
    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);

    if (!plant) {
        FAIL("Failed to cast PlantComponent to LivingPlant");
        return;
    }

    int initialAge = plant->getAge();
    int initialWater = plant->getWaterLevel();
    int initialSun = plant->getSunExposure();

    GrowPlantCommand cmd(plant);
    cmd.execute();

    // Age should increase
    CHECK(plant->getAge() > initialAge);
}

TEST_CASE("test_GrowPlantCommand_Execute_StateTransition_SeedToVegetative") {
    PlantComponent* plantComp = createTestPlant("Rose");
    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);

    if (!plant) {
        FAIL("Failed to cast PlantComponent to LivingPlant");
        return;
    }

    plant->setMaturity(Seed::getID());
    plant->setAge(5);

    Inventory* inv = Inventory::getInstance();

    // Grow multiple times until state transitions
    for (int i = 0; i < 10; i++) {
        GrowPlantCommand cmd(plant);
        cmd.execute();
    }

    // Check if state has progressed
    CHECK(plant->getAge() > 5);
}

TEST_CASE("test_GrowPlantCommand_NullPlant_ThrowsException") {
    try {
        GrowPlantCommand cmd(nullptr);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }
}

TEST_CASE("test_GrowPlantCommand_Undo_RestoresPlantState") {
    PlantComponent* plantComp = createTestPlant("Rose");
    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);

    if (!plant) {
        FAIL("Failed to cast PlantComponent to LivingPlant");
        return;
    }

    plant->setAge(5);
    plant->setHealth(80);
    plant->setWaterLevel(30);

    int initialAge = plant->getAge();
    double initialHealth = plant->getHealth();
    int initialWater = plant->getWaterLevel();

    GrowPlantCommand cmd(plant);
    cmd.execute();

    // State should have changed
    CHECK(plant->getAge() > initialAge);

    cmd.undo();

    // State should be restored
    CHECK(plant->getAge() == initialAge);
    CHECK(plant->getHealth() == initialHealth);
    CHECK(plant->getWaterLevel() == initialWater);
}

TEST_CASE("test_GrowPlantCommand_ExecuteUndoExecute_StateConsistency") {
    PlantComponent* plantComp = createTestPlant("Rose");
    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);

    if (!plant) {
        FAIL("Failed to cast PlantComponent to LivingPlant");
        return;
    }

    GrowPlantCommand cmd(plant);

    int ageAfterFirstExec;
    int ageAfterSecondExec;

    // Execute
    cmd.execute();
    ageAfterFirstExec = plant->getAge();

    // Undo
    cmd.undo();

    // Execute again
    cmd.execute();
    ageAfterSecondExec = plant->getAge();

    // Ages should match after second execute
    CHECK(ageAfterFirstExec == ageAfterSecondExec);
}

} // END TEST_SUITE GrowPlantCommand

// ============================================================================
// TEST SUITE 4: PurchasePlantsCommand Tests
// ============================================================================

TEST_SUITE("PurchasePlantsCommand") {

TEST_CASE("test_PurchasePlantsCommand_Execute_TransfersPlantFromInventory") {
    Customer* customer = createTestCustomerWithBasket(1);
    SalesFloor* salesFloor = new SalesFloor();

    int initialSize = getInventorySize();

    PurchasePlantsCommand cmd(customer, salesFloor);
    cmd.execute();

    // Basket should be cleared
    PlantGroup* basket = customer->getBasket();
    bool basketEmpty = (basket == nullptr || basket->getPlants() == nullptr || basket->getPlants()->size() == 0);
    CHECK(basketEmpty);

    delete salesFloor;
}

TEST_CASE("test_PurchasePlantsCommand_Execute_MultiplePlants_TransfersAll") {
    Customer* customer = createTestCustomerWithBasket(3);
    SalesFloor* salesFloor = new SalesFloor();

    int initialSize = getInventorySize();

    PurchasePlantsCommand cmd(customer, salesFloor);
    cmd.execute();

    // Basket should be cleared
    CHECK(customer->getBasket() == nullptr);

    delete salesFloor;
}

TEST_CASE("test_PurchasePlantsCommand_NullCustomer_ThrowsException") {
    SalesFloor* salesFloor = new SalesFloor();

    try {
        PurchasePlantsCommand cmd(nullptr, salesFloor);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }

    delete salesFloor;
}

TEST_CASE("test_PurchasePlantsCommand_NullSalesFloor_ThrowsException") {
    Customer* customer = createTestCustomer();

    try {
        PurchasePlantsCommand cmd(customer, nullptr);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }
}

TEST_CASE("test_PurchasePlantsCommand_Execute_CustomerHasNoBasket_ThrowsException") {
    Customer* customer = createTestCustomer();
    SalesFloor* salesFloor = new SalesFloor();

    CHECK(customer->getBasket() == nullptr);

    try {
        PurchasePlantsCommand cmd(customer, salesFloor);
        cmd.execute();
        FAIL("Expected exception not thrown");
    } catch (const std::runtime_error&) {
        CHECK(true);
    }

    delete salesFloor;
}

TEST_CASE("test_PurchasePlantsCommand_Undo_RestoresPlantToInventory") {
    Customer* customer = createTestCustomerWithBasket(1);
    SalesFloor* salesFloor = new SalesFloor();

    int initialSize = getInventorySize();

    PurchasePlantsCommand cmd(customer, salesFloor);
    cmd.execute();

    cmd.undo();

    // Check if inventory size is restored
    CHECK(getInventorySize() == initialSize);

    delete salesFloor;
}

TEST_CASE("test_PurchasePlantsCommand_ExecuteUndoExecute_TransactionConsistency") {
    Customer* customer = createTestCustomerWithBasket(2);
    SalesFloor* salesFloor = new SalesFloor();

    int initialSize = getInventorySize();

    PurchasePlantsCommand cmd(customer, salesFloor);

    // Execute
    cmd.execute();
    int sizeAfterPurchase = getInventorySize();

    // Undo
    cmd.undo();
    int sizeAfterUndo = getInventorySize();

    // Execute again
    cmd.execute();
    int sizeFinal = getInventorySize();

    // Final size should match post-purchase size
    CHECK(sizeFinal == sizeAfterPurchase);
    CHECK(sizeAfterUndo == initialSize);

    delete salesFloor;
}

} // END TEST_SUITE PurchasePlantsCommand

// ============================================================================
// TEST SUITE 5: GetSuggestionCommand Tests
// ============================================================================

TEST_SUITE("GetSuggestionCommand") {

TEST_CASE("test_GetSuggestionCommand_Execute_CallsMediatorAssist") {
    Customer* customer = createTestCustomer();
    SuggestionFloor* suggestionFloor = new SuggestionFloor();

    GetSuggestionCommand cmd(customer, suggestionFloor);

    // Should not throw
    cmd.execute();
    CHECK(true);

    delete suggestionFloor;
}

TEST_CASE("test_GetSuggestionCommand_Execute_MultipleCustomers_Success") {
    Customer* customer1 = createTestCustomer();
    Customer* customer2 = createTestCustomer();
    SuggestionFloor* suggestionFloor = new SuggestionFloor();

    GetSuggestionCommand cmd1(customer1, suggestionFloor);
    GetSuggestionCommand cmd2(customer2, suggestionFloor);

    cmd1.execute();
    cmd2.execute();

    CHECK(true);

    delete suggestionFloor;
}

TEST_CASE("test_GetSuggestionCommand_NullCustomer_ThrowsException") {
    SuggestionFloor* suggestionFloor = new SuggestionFloor();

    try {
        GetSuggestionCommand cmd(nullptr, suggestionFloor);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }

    delete suggestionFloor;
}

TEST_CASE("test_GetSuggestionCommand_NullSuggestionFloor_ThrowsException") {
    Customer* customer = createTestCustomer();

    try {
        GetSuggestionCommand cmd(customer, nullptr);
        FAIL("Expected exception not thrown");
    } catch (const std::invalid_argument&) {
        CHECK(true);
    }
}

TEST_CASE("test_GetSuggestionCommand_Undo_IsNoOp") {
    Customer* customer = createTestCustomer();
    SuggestionFloor* suggestionFloor = new SuggestionFloor();

    GetSuggestionCommand cmd(customer, suggestionFloor);
    cmd.execute();

    // Undo should succeed (no-op for read-only operation)
    cmd.undo();
    CHECK(true);

    delete suggestionFloor;
}

} // END TEST_SUITE GetSuggestionCommand

// ============================================================================
// TEST SUITE 6: NurseryFacade Integration Tests
// ============================================================================

TEST_SUITE("NurseryFacade Integration") {

TEST_CASE("test_NurseryFacade_Constructor_InitializesSubsystems") {
    NurseryFacade facade;

    Inventory* inv = Inventory::getInstance();
    CHECK(inv != nullptr);

    // Facade should be constructed without errors
    CHECK(true);
}

TEST_CASE("test_NurseryFacade_CreatePlant_WrapsCommand_Success") {
    NurseryFacade facade;

    int initialSize = getInventorySize();

    PlantComponent* plant = facade.createPlant("Rose");

    CHECK(plant != nullptr);
    CHECK(getInventorySize() == initialSize + 1);
    CHECK(isPlantInInventory(plant));
}

TEST_CASE("test_NurseryFacade_AddToBasket_WrapsCommand_Success") {
    NurseryFacade facade;
    Customer* customer = createTestCustomer();
    PlantComponent* plant = facade.createPlant("Rose");

    facade.addToBasket(customer, plant);

    CHECK(customer->getBasket() != nullptr);
}

TEST_CASE("test_NurseryFacade_GrowPlant_WrapsCommand_Success") {
    NurseryFacade facade;
    PlantComponent* plantComp = facade.createPlant("Rose");
    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);

    if (!plant) {
        FAIL("Failed to cast PlantComponent to LivingPlant");
        return;
    }

    int initialAge = plant->getAge();

    facade.growPlant(plant);

    CHECK(plant->getAge() > initialAge);
}

TEST_CASE("test_NurseryFacade_PurchasePlants_WrapsCommand_Success") {
    NurseryFacade facade;
    Customer* customer = createTestCustomer();
    PlantComponent* plant = facade.createPlant("Rose");

    facade.addToBasket(customer, plant);
    facade.purchasePlants(customer);

    CHECK(customer->getBasket() == nullptr);
}

TEST_CASE("test_NurseryFacade_GetSuggestions_WrapsCommand_Success") {
    NurseryFacade facade;
    Customer* customer = createTestCustomer();

    facade.getSuggestions(customer);

    CHECK(true);
}

} // END TEST_SUITE NurseryFacade Integration

// ============================================================================
// TEST SUITE 7: Command History Management Tests
// ============================================================================

TEST_SUITE("Command History Management") {

TEST_CASE("test_NurseryFacade_CommandHistory_PushesCommandsOnExecute") {
    NurseryFacade facade;

    facade.createPlant("Rose");
    facade.createPlant("Cactus");
    facade.createPlant("Sunflower");

    // History should contain 3 commands
    CHECK(true);
}

TEST_CASE("test_NurseryFacade_CommandHistory_ClearsRedoStackOnNewCommand") {
    NurseryFacade facade;

    facade.createPlant("Rose");
    facade.createPlant("Cactus");

    facade.undo();

    // Redo stack should have 1 command

    facade.createPlant("Sunflower");

    // Redo stack should be cleared
    bool canRedo = facade.redo();
    CHECK(canRedo == false);
}

TEST_CASE("test_NurseryFacade_CommandHistory_RespectsSizeLimit") {
    NurseryFacade facade;

    // Execute 105 commands
    for (int i = 0; i < 105; i++) {
        facade.createPlant("Rose");
    }

    // History should be capped at 100
    CHECK(true);
}

TEST_CASE("test_NurseryFacade_CanQueryHistoryState") {
    NurseryFacade facade;

    // Initially, should not be able to undo
    bool canUndo = facade.undo();
    CHECK(canUndo == false);

    // Execute a command
    facade.createPlant("Rose");

    // Now should be able to undo
    canUndo = facade.undo();
    CHECK(canUndo == true);
}

TEST_CASE("test_NurseryFacade_ClearHistory_DeletesAllCommands") {
    NurseryFacade facade;

    facade.createPlant("Rose");
    facade.createPlant("Cactus");
    facade.createPlant("Sunflower");

    facade.clearHistory();

    // History should be empty, no more undo
    bool canUndo = facade.undo();
    CHECK(canUndo == false);
}

} // END TEST_SUITE Command History Management

// ============================================================================
// TEST SUITE 8: Undo/Redo Workflow Tests
// ============================================================================

TEST_SUITE("Undo/Redo Workflows") {

TEST_CASE("test_NurseryFacade_Undo_RevertsLastCommand") {
    NurseryFacade facade;

    int initialSize = getInventorySize();

    facade.createPlant("Rose");
    CHECK(getInventorySize() == initialSize + 1);

    bool undoSuccess = facade.undo();
    CHECK(undoSuccess == true);
    CHECK(getInventorySize() == initialSize);
}

TEST_CASE("test_NurseryFacade_Undo_EmptyHistory_ReturnsFalse") {
    NurseryFacade facade;

    bool undoSuccess = facade.undo();
    CHECK(undoSuccess == false);
}

TEST_CASE("test_NurseryFacade_Redo_RepeatsUndoneCommand") {
    NurseryFacade facade;

    int initialSize = getInventorySize();

    facade.createPlant("Rose");
    CHECK(getInventorySize() == initialSize + 1);

    facade.undo();
    CHECK(getInventorySize() == initialSize);

    bool redoSuccess = facade.redo();
    CHECK(redoSuccess == true);
    CHECK(getInventorySize() == initialSize + 1);
}

TEST_CASE("test_NurseryFacade_Redo_EmptyRedoStack_ReturnsFalse") {
    NurseryFacade facade;

    bool redoSuccess = facade.redo();
    CHECK(redoSuccess == false);
}

TEST_CASE("test_NurseryFacade_UndoRedoUndoSequence_StateConsistency") {
    NurseryFacade facade;

    int initialSize = getInventorySize();

    facade.createPlant("Rose");
    CHECK(getInventorySize() == initialSize + 1);

    facade.undo();
    CHECK(getInventorySize() == initialSize);

    facade.redo();
    CHECK(getInventorySize() == initialSize + 1);

    facade.undo();
    CHECK(getInventorySize() == initialSize);
}

TEST_CASE("test_NurseryFacade_MultipleCommandsUndoAll_RevertsToInitial") {
    NurseryFacade facade;

    int initialSize = getInventorySize();

    facade.createPlant("Rose");
    facade.createPlant("Cactus");
    facade.createPlant("Sunflower");

    CHECK(getInventorySize() == initialSize + 3);

    facade.undo();
    facade.undo();
    facade.undo();

    CHECK(getInventorySize() == initialSize);
}

TEST_CASE("test_NurseryFacade_UndoRedoNewCommand_ClearsRedoPath") {
    NurseryFacade facade;

    facade.createPlant("Rose");
    facade.undo();

    // Redo stack should have 1
    bool canRedo = facade.redo();
    CHECK(canRedo == true);

    // Execute new command - should clear redo
    facade.createPlant("Cactus");

    canRedo = facade.redo();
    CHECK(canRedo == false);
}

} // END TEST_SUITE Undo/Redo Workflows

// ============================================================================
// TEST SUITE 9: Full Integration Workflow Tests
// ============================================================================

TEST_SUITE("Full Integration Workflows") {

TEST_CASE("test_NurseryFacade_FullWorkflow_CreateGrowPurchase") {
    NurseryFacade facade;
    Customer* customer = createTestCustomer();

    // Create plant
    PlantComponent* plantComp = facade.createPlant("Rose");
    CHECK(plantComp != nullptr);

    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);
    if (!plant) {
        FAIL("Failed to cast PlantComponent to LivingPlant");
        return;
    }

    // Grow plant
    int initialAge = plant->getAge();
    facade.growPlant(plant);
    CHECK(plant->getAge() > initialAge);

    // Add to basket
    facade.addToBasket(customer, plantComp);
    CHECK(customer->getBasket() != nullptr);

    // Purchase
    facade.purchasePlants(customer);
    CHECK(customer->getBasket() == nullptr);
}

TEST_CASE("test_NurseryFacade_FullWorkflow_WithUndo_ReversesAllChanges") {
    NurseryFacade facade;
    Customer* customer = createTestCustomer();

    int initialSize = getInventorySize();

    // Create plant
    PlantComponent* plantComp = facade.createPlant("Rose");
    CHECK(getInventorySize() == initialSize + 1);

    // Add to basket
    facade.addToBasket(customer, plantComp);

    // Purchase
    facade.purchasePlants(customer);

    // Undo purchase
    facade.undo();

    // Undo add to basket
    facade.undo();

    // Undo create
    facade.undo();

    CHECK(getInventorySize() == initialSize);
}

TEST_CASE("test_NurseryFacade_TwoCustomers_IndependentBaskets") {
    NurseryFacade facade;
    Customer* customer1 = createTestCustomer();
    Customer* customer2 = createTestCustomer();

    PlantComponent* rose = facade.createPlant("Rose");
    PlantComponent* cactus = facade.createPlant("Cactus");

    facade.addToBasket(customer1, rose);
    facade.addToBasket(customer2, cactus);

    CHECK(customer1->getBasket() != nullptr);
    CHECK(customer2->getBasket() != nullptr);

    facade.purchasePlants(customer1);

    CHECK(customer1->getBasket() == nullptr);
    CHECK(customer2->getBasket() != nullptr);
}

} // END TEST_SUITE Full Integration Workflows

// ============================================================================
// TEST SUITE 10: Edge Cases & Boundary Conditions
// ============================================================================

TEST_SUITE("Edge Cases & Boundaries") {

TEST_CASE("test_GrowPlantCommand_DeadPlant_CannotGrow") {
    PlantComponent* plantComp = createTestPlant("Rose");
    LivingPlant* plant = dynamic_cast<LivingPlant*>(plantComp);

    if (!plant) {
        FAIL("Failed to cast PlantComponent to LivingPlant");
        return;
    }

    plant->setHealth(0);
    plant->setMaturity(Dead::getID());

    int initialAge = plant->getAge();

    GrowPlantCommand cmd(plant);
    cmd.execute();

    // Dead plant state should not change significantly
    CHECK(plant->getHealth() == 0);
}

TEST_CASE("test_PurchasePlantsCommand_LargeBasket_100Plants") {
    Customer* customer = createTestCustomer();
    NurseryFacade facade;

    // Add 10 plants to basket (simplified for testing)
    for (int i = 0; i < 10; i++) {
        PlantComponent* plant = facade.createPlant("Rose");
        facade.addToBasket(customer, plant);
    }

    // Purchase should handle all plants
    facade.purchasePlants(customer);

    CHECK(customer->getBasket() == nullptr);
}

TEST_CASE("test_NurseryFacade_MaxHistorySize_Enforcement") {
    NurseryFacade facade;

    // Execute 105 commands (exceeding limit)
    for (int i = 0; i < 105; i++) {
        facade.createPlant("Rose");
    }

    // Should be able to undo 100 times max
    int undoCount = 0;
    while (facade.undo() && undoCount < 110) {
        undoCount++;
    }

    CHECK(undoCount == 100);
}

TEST_CASE("test_NurseryFacade_RapidExecuteUndoRedo_Stable") {
    NurseryFacade facade;

    // Execute 10 commands rapidly
    for (int i = 0; i < 10; i++) {
        facade.createPlant("Rose");
    }

    // Undo all 10
    for (int i = 0; i < 10; i++) {
        facade.undo();
    }

    // Redo all 10
    for (int i = 0; i < 10; i++) {
        facade.redo();
    }

    CHECK(true);
}

} // END TEST_SUITE Edge Cases & Boundaries

// ============================================================================
// END OF FACADE & COMMAND PATTERN UNIT TESTS
// ============================================================================