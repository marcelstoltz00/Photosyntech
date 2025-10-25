# Facade & Command Pattern Unit Tests Specification

**File**: `facade-command-unit-tests.cpp`

**Purpose**: Comprehensive testing of NurseryFacade and Command pattern implementations (CreatePlantCommand, AddPlantToBasketCommand, GrowPlantCommand, PurchasePlantsCommand, GetSuggestionCommand)

---

## Test Organization

Tests are organized into the following categories:

### 1. CreatePlantCommand Tests
### 2. AddPlantToBasketCommand Tests
### 3. GrowPlantCommand Tests
### 4. PurchasePlantsCommand Tests
### 5. GetSuggestionCommand Tests
### 6. NurseryFacade Integration Tests
### 7. Command History Management Tests
### 8. Undo/Redo Workflow Tests

---

## 1. CreatePlantCommand Tests

### 1.1 Valid Plant Creation

**Test**: `test_CreatePlantCommand_Rose_Execute_Success`
- Create CreatePlantCommand with species "Rose"
- Call execute()
- Assert: Plant created and added to inventory
- Assert: getCreatedPlant() returns non-null PlantComponent*
- Assert: Plant exists in Inventory::getInstance()->getInventory()

**Test**: `test_CreatePlantCommand_MultipleSpecies_Execute_Success`
- Create commands for all 8 species: Rose, Cactus, Sunflower, Pine, Maple, JadePlant, Lavender, CherryBlossom
- Execute each command
- Assert: All plants created successfully
- Assert: All plants added to inventory
- Assert: Inventory contains 8 plants

**Test**: `test_CreatePlantCommand_Execute_PlantHasCorrectAttributes`
- Create CreatePlantCommand("Rose")
- Execute command
- Get created plant via getCreatedPlant()
- Assert: Plant has valid water level (>= 0)
- Assert: Plant has valid sun exposure (>= 0)
- Assert: Plant has valid age
- Assert: Plant has valid health
- Assert: Plant is in initial state (Seed)

### 1.2 Invalid Plant Creation

**Test**: `test_CreatePlantCommand_NullSpecies_ThrowsException`
- Create CreatePlantCommand(nullptr)
- Assert: std::invalid_argument exception thrown

**Test**: `test_CreatePlantCommand_UnknownSpecies_ThrowsException`
- Create CreatePlantCommand("UnknownPlant")
- Call execute()
- Assert: std::invalid_argument exception thrown
- Assert: Exception message lists available species

**Test**: `test_CreatePlantCommand_EmptySpecies_ThrowsException`
- Create CreatePlantCommand("")
- Call execute()
- Assert: Exception thrown

### 1.3 CreatePlantCommand Undo

**Test**: `test_CreatePlantCommand_Undo_RemovesPlantFromInventory`
- Create and execute CreatePlantCommand("Rose")
- Store created plant pointer
- Verify plant in inventory
- Call undo()
- Assert: Plant removed from inventory
- Assert: Inventory size decreased by 1

**Test**: `test_CreatePlantCommand_Undo_DeletesPlant`
- Create and execute CreatePlantCommand("Cactus")
- Get plant pointer
- Call undo()
- Assert: Plant pointer no longer valid (cleanup occurred)
- Assert: Creating new plant still works

**Test**: `test_CreatePlantCommand_ExecuteUndoExecute_Success`
- Create command
- Execute → verify in inventory
- Undo → verify removed
- Execute → verify back in inventory
- Assert: All states correct after each operation

### 1.4 CreatePlantCommand Memory Management

**Test**: `test_CreatePlantCommand_Destructor_NoMemoryLeak`
- Create CreatePlantCommand
- Execute (plant ownership transfers to inventory)
- Destroy command object
- Assert: No crash or memory errors
- Verify inventory still contains plant

---

## 2. AddPlantToBasketCommand Tests

### 2.1 Valid Basket Operations

**Test**: `test_AddPlantToBasketCommand_AddToNewBasket_Success`
- Create customer with null basket
- Create plant and add to inventory
- Create AddPlantToBasketCommand(customer, plant)
- Call execute()
- Assert: Customer has basket (not null)
- Assert: Plant in customer's basket
- Assert: basketWasNull flag true

**Test**: `test_AddPlantToBasketCommand_AddToExistingBasket_Success`
- Create customer with existing basket containing 1 plant
- Create new plant
- Create AddPlantToBasketCommand(customer, newPlant)
- Call execute()
- Assert: Both plants in basket
- Assert: basketWasNull flag false

**Test**: `test_AddPlantToBasketCommand_MultipleAdditions_Success`
- Create customer
- Create 3 plants
- Add each to basket via separate commands
- Assert: All 3 plants in basket
- Assert: Basket size = 3

### 2.2 Invalid Basket Operations

**Test**: `test_AddPlantToBasketCommand_NullCustomer_ThrowsException`
- Create AddPlantToBasketCommand(nullptr, plant)
- Assert: std::invalid_argument exception thrown

**Test**: `test_AddPlantToBasketCommand_NullPlant_ThrowsException`
- Create AddPlantToBasketCommand(customer, nullptr)
- Assert: std::invalid_argument exception thrown

### 2.3 AddPlantToBasketCommand Undo

**Test**: `test_AddPlantToBasketCommand_Undo_RemovesPlantFromBasket`
- Create customer and plant
- Create and execute AddPlantToBasketCommand
- Verify plant in basket
- Call undo()
- Assert: Plant removed from basket

**Test**: `test_AddPlantToBasketCommand_Undo_DeletesBasketIfWasNull`
- Create customer with null basket
- Create and execute AddPlantToBasketCommand
- Verify basket created with plant
- Call undo()
- Assert: Basket deleted (nullptr)

**Test**: `test_AddPlantToBasketCommand_Undo_KeepsBasketIfExisted`
- Create customer with existing basket (1 plant)
- Create and execute AddPlantToBasketCommand (add 2nd plant)
- Verify 2 plants in basket
- Call undo()
- Assert: Basket still exists with 1 plant

**Test**: `test_AddPlantToBasketCommand_ExecuteUndoExecute_Success`
- Create customer and plant
- Execute → plant in basket
- Undo → plant removed
- Execute → plant back in basket

---

## 3. GrowPlantCommand Tests

### 3.1 Valid Growth Operations

**Test**: `test_GrowPlantCommand_Execute_PlantGrows`
- Create plant (starts in Seed state)
- Record initial age and water level
- Create and execute GrowPlantCommand
- Assert: Plant age increased
- Assert: Water level changed (consumed)
- Assert: Sun exposure changed (consumed)

**Test**: `test_GrowPlantCommand_Execute_StateTransition_SeedToVegetative`
- Create plant in Seed state
- Execute growth until state should transition
- Call execute() multiple times
- Assert: Plant eventually transitions to Vegetative state
- Assert: State transition observable via getMaturityStateID()

**Test**: `test_GrowPlantCommand_Execute_StateTransition_VegetativeToMature`
- Create mature plant via growth progression
- Execute growth commands
- Assert: Plant transitions from Vegetative to Mature

**Test**: `test_GrowPlantCommand_Execute_StateTransition_MatureToDead`
- Create mature plant
- Reduce health to critical level
- Execute growth
- Assert: Plant transitions to Dead state

### 3.2 Invalid Growth Operations

**Test**: `test_GrowPlantCommand_NullPlant_ThrowsException`
- Create GrowPlantCommand(nullptr)
- Assert: std::invalid_argument exception thrown

**Test**: `test_GrowPlantCommand_Execute_InvalidPlantState_ThrowsException`
- Create command with valid plant
- Manually corrupt plant state
- Call execute()
- Assert: Appropriate exception thrown

### 3.3 GrowPlantCommand Memento Functionality

**Test**: `test_GrowPlantCommand_Undo_RestoresPlantState`
- Create plant with known state (age=5, health=80, water=30)
- Create and execute GrowPlantCommand
- Record new state (age=6, health=75, water=20)
- Call undo()
- Assert: age restored to 5
- Assert: health restored to 80
- Assert: water restored to 30

**Test**: `test_GrowPlantCommand_Undo_RestoresMaturityState`
- Create plant in Seed state
- Execute growth multiple times
- Record new state (now Vegetative)
- Call undo() to revert last growth
- Assert: State returns to previous state
- Assert: All attributes match pre-growth values

**Test**: `test_GrowPlantCommand_ExecuteUndoExecute_StateConsistency`
- Execute growth (Seed → Vegetative)
- Undo (back to Seed)
- Execute again (Seed → Vegetative)
- Assert: Final state matches second execution state
- Assert: All attributes consistent

### 3.4 GrowPlantCommand Memory Management

**Test**: `test_GrowPlantCommand_MementoOwnership_ProperCleanup`
- Create and execute GrowPlantCommand
- Destroy command via delete
- Assert: No memory leaks
- Assert: Plant still valid (memento deleted, plant kept)

---

## 4. PurchasePlantsCommand Tests

### 4.1 Valid Purchase Operations

**Test**: `test_PurchasePlantsCommand_Execute_TransfersPlantFromInventory`
- Create customer with basket containing 1 plant
- Record inventory size before purchase
- Create and execute PurchasePlantsCommand
- Assert: Plant removed from inventory
- Assert: Inventory size decreased by 1
- Assert: Customer basket cleared

**Test**: `test_PurchasePlantsCommand_Execute_MultiplePlants_TransfersAll`
- Create customer with basket containing 3 plants
- Record inventory size and plant IDs
- Execute PurchasePlantsCommand
- Assert: All 3 plants removed from inventory
- Assert: Basket cleared
- Assert: Plants marked as purchased

**Test**: `test_PurchasePlantsCommand_Execute_MediatorCoordination`
- Create customer with basket
- Create PurchasePlantsCommand with SalesFloor mediator
- Execute command
- Assert: SalesFloor->assist() was called
- Assert: Staff-customer interaction occurred (per mediator design)

### 4.2 Invalid Purchase Operations

**Test**: `test_PurchasePlantsCommand_NullCustomer_ThrowsException`
- Create PurchasePlantsCommand(nullptr, salesFloor)
- Assert: std::invalid_argument exception thrown

**Test**: `test_PurchasePlantsCommand_NullSalesFloor_ThrowsException`
- Create PurchasePlantsCommand(customer, nullptr)
- Assert: std::invalid_argument exception thrown

**Test**: `test_PurchasePlantsCommand_Execute_CustomerHasNoBasket_ThrowsException`
- Create customer with nullptr basket
- Create PurchasePlantsCommand
- Call execute()
- Assert: std::runtime_error exception thrown

**Test**: `test_PurchasePlantsCommand_Execute_EmptyBasket_ThrowsException`
- Create customer with empty basket
- Create PurchasePlantsCommand
- Call execute()
- Assert: std::runtime_error exception thrown

### 4.3 PurchasePlantsCommand Undo

**Test**: `test_PurchasePlantsCommand_Undo_RestoresPlantToInventory`
- Create customer with basket (1 plant)
- Record inventory size before
- Execute purchase
- Verify plant removed from inventory
- Call undo()
- Assert: Plant back in inventory
- Assert: Inventory size matches before purchase

**Test**: `test_PurchasePlantsCommand_Undo_RestoresBasket`
- Create customer with basket (2 plants: Rose, Cactus)
- Record plant pointers
- Execute purchase (basket cleared, plants removed)
- Call undo()
- Assert: Basket restored with both plants
- Assert: Plant pointers match original
- Assert: Plant order preserved

**Test**: `test_PurchasePlantsCommand_Undo_FailsIfNotExecuted`
- Create PurchasePlantsCommand
- Call undo() without execute()
- Assert: std::runtime_error exception thrown

**Test**: `test_PurchasePlantsCommand_ExecuteUndoExecute_TransactionConsistency`
- Execute purchase
- Verify state changes
- Undo
- Verify state restored
- Execute again
- Assert: Final state matches original execution

### 4.4 PurchasePlantsCommand Memento Functionality

**Test**: `test_PurchasePlantsCommand_BasketMemento_CapturesAllPlants`
- Create customer with 3 plants in basket
- Create and execute PurchasePlantsCommand
- Verify memento captured all 3 plants
- Call undo()
- Assert: All 3 plants restored in same order

**Test**: `test_PurchasePlantsCommand_BasketMemento_TracksBasketExistence`
- Create customer with existing basket
- Execute purchase
- Call undo()
- Assert: Basket still exists (wasn't null before)

**Test**: `test_PurchasePlantsCommand_BasketMemento_HandlesNullBasketCreation`
- Create customer with null basket
- Create and execute AddPlantToBasketCommand (creates basket)
- Create and execute PurchasePlantsCommand
- Call undo()
- Assert: Basket set back to nullptr

---

## 5. GetSuggestionCommand Tests

### 5.1 Valid Suggestion Operations

**Test**: `test_GetSuggestionCommand_Execute_CallsMediatorAssist`
- Create customer
- Create GetSuggestionCommand
- Execute command
- Assert: SuggestionFloor->assist() called
- Assert: No exception thrown

**Test**: `test_GetSuggestionCommand_Execute_MultipleCustomers_Success`
- Create 2 customers
- Create and execute GetSuggestionCommand for each
- Assert: Both executed successfully
- Assert: Each customer received suggestions via mediator

### 5.2 Invalid Suggestion Operations

**Test**: `test_GetSuggestionCommand_NullCustomer_ThrowsException`
- Create GetSuggestionCommand(nullptr, suggestionFloor)
- Assert: std::invalid_argument exception thrown

**Test**: `test_GetSuggestionCommand_NullSuggestionFloor_ThrowsException`
- Create GetSuggestionCommand(customer, nullptr)
- Assert: std::invalid_argument exception thrown

### 5.3 GetSuggestionCommand Undo (Read-Only)

**Test**: `test_GetSuggestionCommand_Undo_IsNoOp`
- Create and execute GetSuggestionCommand
- Call undo()
- Assert: No exception thrown
- Assert: No state changed (read-only operation)
- Assert: Command still in history

**Test**: `test_GetSuggestionCommand_Execute_ThenUndo_NoStateChange`
- Get customer suggestion count before
- Execute GetSuggestionCommand
- Call undo()
- Assert: Customer state unchanged (read-only)
- Assert: Undo succeeds (no-op)

---

## 6. NurseryFacade Integration Tests

### 6.1 Facade Constructor & Initialization

**Test**: `test_NurseryFacade_Constructor_InitializesSubsystems`
- Create NurseryFacade
- Assert: Inventory reference valid (not null)
- Assert: SalesFloor mediator created
- Assert: SuggestionFloor mediator created
- Assert: History and redo stacks empty

**Test**: `test_NurseryFacade_Constructor_InitializationFailure_ThrowsException`
- Mock Inventory::getInstance() to return nullptr
- Create NurseryFacade
- Assert: std::runtime_error thrown

### 6.2 Facade Command Execution Methods

**Test**: `test_NurseryFacade_CreatePlant_WrapsCommand_Success`
- Call facade->createPlant("Rose")
- Assert: Returns non-null PlantComponent*
- Assert: Plant in inventory
- Assert: Command in history

**Test**: `test_NurseryFacade_AddToBasket_WrapsCommand_Success`
- Create customer and plant
- Call facade->addToBasket(customer, plant)
- Assert: Plant in customer's basket
- Assert: Command in history

**Test**: `test_NurseryFacade_GrowPlant_WrapsCommand_Success`
- Create plant
- Call facade->growPlant(plant)
- Assert: Plant state changed
- Assert: Command in history

**Test**: `test_NurseryFacade_PurchasePlants_WrapsCommand_Success`
- Create customer with basket
- Call facade->purchasePlants(customer)
- Assert: Basket cleared
- Assert: Plants removed from inventory
- Assert: Command in history

**Test**: `test_NurseryFacade_GetSuggestions_WrapsCommand_Success`
- Create customer
- Call facade->getSuggestions(customer)
- Assert: No exception
- Assert: Command in history

### 6.3 Facade Delegation Methods

**Test**: `test_NurseryFacade_GetPlantInfo_Delegates_Success`
- Create plant
- Call facade->getPlantInfo(plant)
- Assert: Returns non-empty string with plant info

**Test**: `test_NurseryFacade_GetPlantPrice_Delegates_Success`
- Create decorated plant (with price-affecting decorators)
- Call facade->getPlantPrice(plant)
- Assert: Returns total price > 0

**Test**: `test_NurseryFacade_WaterPlant_Delegates_Success`
- Create plant, record water level
- Call facade->waterPlant(plant)
- Assert: Water level decreased

**Test**: `test_NurseryFacade_SetWaterLevel_Delegates_Success`
- Create plant
- Call facade->setWaterLevel(plant, 50)
- Assert: Plant's water level = 50

**Test**: `test_NurseryFacade_SetWaterStrategy_Delegates_Success`
- Create plant
- Call facade->setWaterStrategy(plant, 1)
- Assert: Water strategy updated

**Test**: `test_NurseryFacade_CreateAllPlantsIterator_Success`
- Add 3 plants to inventory
- Call facade->createAllPlantsIterator()
- Assert: Returns non-null Iterator*
- Assert: Iterator traverses all 3 plants

**Test**: `test_NurseryFacade_CreateSeasonIterator_Success`
- Add seasonal plants to inventory
- Call facade->createSeasonIterator("Spring")
- Assert: Returns non-null Iterator*
- Assert: Iterator filters by season

**Test**: `test_NurseryFacade_AddToInventory_Delegates_Success`
- Create plant (not in inventory)
- Call facade->addToInventory(plant)
- Assert: Plant in inventory

**Test**: `test_NurseryFacade_RemoveFromInventory_Delegates_Success`
- Create plant in inventory
- Call facade->removeFromInventory(plant)
- Assert: Plant removed from inventory

### 6.4 Facade Null Parameter Handling

**Test**: `test_NurseryFacade_Methods_HandlesNullParameters_Gracefully`
- Call facade->getPlantInfo(nullptr)
- Assert: Returns error string or empty string
- Call facade->waterPlant(nullptr)
- Assert: No crash, returns gracefully
- Call facade->setWaterLevel(nullptr, 10)
- Assert: No crash

---

## 7. Command History Management Tests

### 7.1 History Stack Operations

**Test**: `test_NurseryFacade_CommandHistory_PushesCommandsOnExecute`
- Create facade
- Execute 3 commands
- Assert: History size = 3
- Assert: History contains commands in order

**Test**: `test_NurseryFacade_CommandHistory_ClearsRedoStackOnNewCommand`
- Execute 2 commands
- Undo 1 command
- Assert: Redo stack size = 1
- Execute new command
- Assert: Redo stack cleared (size = 0)

**Test**: `test_NurseryFacade_CommandHistory_RespectsSizeLimit`
- Execute 105 commands
- Assert: History size = 100 (MAX_HISTORY_SIZE)
- Assert: Oldest commands removed/not accessible

### 7.2 History Queries

**Test**: `test_NurseryFacade_CanQueryHistoryState`
- Create facade (empty history)
- Assert: undo() returns false (empty history)
- Execute command
- Assert: undo() returns true
- Execute another command
- Assert: undo() returns true twice

### 7.3 History Cleanup

**Test**: `test_NurseryFacade_ClearHistory_DeletesAllCommands`
- Execute 5 commands
- Assert: History size = 5
- Call clearHistory()
- Assert: History size = 0
- Assert: No memory leaks

**Test**: `test_NurseryFacade_ClearHistory_AlsoClearsRedoStack`
- Execute 3 commands
- Undo 2 commands
- Assert: History size = 1, Redo stack size = 2
- Call clearHistory()
- Assert: History size = 0, Redo stack size = 0

---

## 8. Undo/Redo Workflow Tests

### 8.1 Simple Undo/Redo

**Test**: `test_NurseryFacade_Undo_RevertsLastCommand`
- Create plant (in inventory)
- Assert: Inventory contains plant
- Call undo()
- Assert: Plant removed from inventory
- Assert: undo() returns true

**Test**: `test_NurseryFacade_Undo_EmptyHistory_ReturnsFalse`
- Create facade (empty history)
- Call undo()
- Assert: Returns false
- Assert: No exception thrown

**Test**: `test_NurseryFacade_Redo_RepeatsUndoneCommand`
- Create plant
- Undo (plant removed)
- Assert: Plant not in inventory
- Call redo()
- Assert: Plant back in inventory
- Assert: redo() returns true

**Test**: `test_NurseryFacade_Redo_EmptyRedoStack_ReturnsFalse`
- Create facade
- Call redo() without undo
- Assert: Returns false
- Assert: No exception thrown

### 8.2 Complex Undo/Redo Sequences

**Test**: `test_NurseryFacade_UndoRedoUndoSequence_StateConsistency`
- Execute: CreatePlant("Rose")
- Undo: Plant removed
- Redo: Plant restored
- Undo: Plant removed again
- Assert: Final state = first undo state
- Assert: All intermediate states correct

**Test**: `test_NurseryFacade_MultipleCommandsUndoAll_RevertsToInitial`
- Execute: CreatePlant("Rose")
- Execute: CreatePlant("Cactus")
- Execute: CreatePlant("Sunflower")
- Assert: Inventory has 3 plants
- Undo, Undo, Undo
- Assert: Inventory empty
- Assert: All undos succeeded

**Test**: `test_NurseryFacade_UndoRedoNewCommand_ClearsRedoPath`
- Execute CreatePlant("Rose")
- Undo (plant removed, rose in redo)
- Execute AddPlant (different operation)
- Call redo()
- Assert: redo() returns false (redo stack cleared)

### 8.3 Mixed Command Undo/Redo

**Test**: `test_NurseryFacade_CreatePlantUndoSuccess`
- CreatePlant → Undo → Plant removed
- Assert: Undo successful

**Test**: `test_NurseryFacade_AddToBasketUndoSuccess`
- AddToBasket → Undo → Plant removed from basket
- Assert: Undo successful

**Test**: `test_NurseryFacade_GrowPlantUndoSuccess`
- GrowPlant → Undo → State restored to pre-growth
- Assert: Age, health, water, state all restored

**Test**: `test_NurseryFacade_PurchaseUndoSuccess`
- PurchasePlants → Undo → Plants back in inventory, basket restored
- Assert: Undo successful

**Test**: `test_NurseryFacade_SuggestionUndoSuccess`
- GetSuggestions → Undo → No-op, but succeeds
- Assert: undo() returns true

### 8.4 Undo/Redo Error Handling

**Test**: `test_NurseryFacade_UndoCommandFailure_LogsError_ReturnsFalse`
- Set up scenario where undo will fail (e.g., missing plant)
- Call undo()
- Assert: Returns false
- Assert: Error logged to stderr

**Test**: `test_NurseryFacade_RedoCommandFailure_LogsError_ReturnsFalse`
- Set up scenario where redo will fail
- Call redo()
- Assert: Returns false
- Assert: Error logged to stderr

---

## 9. Full Integration Workflow Tests

### 9.1 Plant Lifecycle Through Facade

**Test**: `test_NurseryFacade_FullWorkflow_CreateGrowPurchase`
- CreatePlant("Rose") → Add to inventory
- Assert: In inventory
- GrowPlant → State progresses
- Assert: State changed
- AddToBasket(customer, rose) → In basket
- Assert: In basket
- PurchasePlants(customer) → Rose moved from inventory to customer
- Assert: Not in inventory, customer has rose

**Test**: `test_NurseryFacade_FullWorkflow_WithUndo_ReversesAllChanges`
- CreatePlant("Rose")
- GrowPlant("Rose")
- AddToBasket(customer, rose)
- PurchasePlants(customer)
- Assert: Rose purchased
- Undo → PurchasePlants reversed
- Assert: Rose back in inventory, basket restored
- Undo → AddToBasket reversed
- Assert: Rose not in basket
- Undo → GrowPlant reversed
- Assert: Rose state restored
- Undo → CreatePlant reversed
- Assert: Rose not in inventory

**Test**: `test_NurseryFacade_FullWorkflow_RedoAfterUndo_RestoresAllChanges`
- Execute full workflow as above
- Undo 4 times
- Assert: Back to initial state
- Redo 4 times
- Assert: Back to final state

### 9.2 Multi-Customer Scenarios

**Test**: `test_NurseryFacade_TwoCustomers_IndependentBaskets`
- Create customer1, customer2
- AddToBasket(customer1, rose)
- AddToBasket(customer2, cactus)
- Assert: customer1 has rose, customer2 has cactus
- PurchasePlants(customer1)
- Assert: customer1 basket cleared, customer2 still has cactus

**Test**: `test_NurseryFacade_MultipleUndoAcrossCustomers_IsolatedUndo`
- Create multiple commands with different customers
- Undo specific command
- Assert: Only that customer affected
- Assert: Other customers unaffected

---

## 10. Edge Cases & Boundary Conditions

### 10.1 State Boundary Tests

**Test**: `test_GrowPlantCommand_DeadPlant_CannotGrow`
- Create dead plant
- Attempt to grow
- Assert: Stays dead (grow is no-op or throws)

**Test**: `test_PurchasePlantsCommand_LargeBasket_100Plants`
- Create customer with 100 plants in basket
- Execute purchase
- Assert: All 100 plants transferred
- Undo
- Assert: All 100 plants restored

**Test**: `test_NurseryFacade_MaxHistorySize_Enforcement`
- Execute 101 commands
- Assert: History size capped at 100
- Try to undo more than 100 times
- Assert: Can only undo 100 times

### 10.2 Rapid Operation Tests

**Test**: `test_NurseryFacade_RapidExecuteUndoRedo_Stable`
- Execute 10 commands in rapid succession
- Undo all 10 rapidly
- Redo all 10 rapidly
- Assert: All operations succeed
- Assert: Final state correct

### 10.3 Decorator Interaction Tests

**Test**: `test_GrowPlantCommand_WithDecorators_UndoPreserves`
- Create decorated plant (pot + charm + seasonal)
- Grow plant
- Undo
- Assert: Decorators preserved (not affected by growth undo)

**Test**: `test_CreatePlantCommand_CreatedPlantCanBeDecorated`
- Create plant via command
- Add decorators to created plant
- Verify decorators applied
- Undo creation
- Assert: Plant and decorators deleted

---

## Test Utilities & Helpers

### Setup Functions

```cpp
// Create test plants quickly
LivingPlant* createTestPlant(const std::string& species)
LivingPlant* createTestPlantWithState(const std::string& species, int age, double health)

// Create customers
Customer* createTestCustomer()
Customer* createTestCustomerWithBasket(int plantCount)

// Verify state helpers
bool isPlantInInventory(PlantComponent* plant)
bool isPlantInBasket(Customer* customer, PlantComponent* plant)
int getInventorySize()
int getBasketSize(Customer* customer)
```

### Assertion Helpers

```cpp
// Custom assertions for complex checks
void assertPlantStateMatches(LivingPlant* plant, int expectedAge, double expectedHealth, ...)
void assertBasketContains(Customer* customer, const std::vector<PlantComponent*>& expectedPlants)
void assertCommandHistorySize(NurseryFacade* facade, int expectedSize)
```

---

## Test File Structure

```cpp
#include <iostream>
#include "third_party/doctest/doctest.h"

// Includes for all command classes
#include "facade/NurseryFacade.h"
#include "command/CreatePlantCommand.h"
#include "command/AddPlantToBasketCommand.h"
#include "command/GrowPlantCommand.h"
#include "command/PurchasePlantsCommand.h"
#include "command/GetSuggestionCommand.h"

// Helper functions
LivingPlant* createTestPlant(...) { ... }
// ... other helpers

// Test contexts organized by command/feature
TEST_SUITE("CreatePlantCommand") { ... }
TEST_SUITE("AddPlantToBasketCommand") { ... }
TEST_SUITE("GrowPlantCommand") { ... }
TEST_SUITE("PurchasePlantsCommand") { ... }
TEST_SUITE("GetSuggestionCommand") { ... }
TEST_SUITE("NurseryFacade Integration") { ... }
TEST_SUITE("Command History Management") { ... }
TEST_SUITE("Undo/Redo Workflows") { ... }
TEST_SUITE("Full Integration Scenarios") { ... }
TEST_SUITE("Edge Cases & Boundaries") { ... }
```

---

## Expected Test Count

- CreatePlantCommand: ~15 tests
- AddPlantToBasketCommand: ~10 tests
- GrowPlantCommand: ~15 tests
- PurchasePlantsCommand: ~15 tests
- GetSuggestionCommand: ~5 tests
- NurseryFacade Integration: ~15 tests
- Command History Management: ~8 tests
- Undo/Redo Workflows: ~15 tests
- Full Integration Scenarios: ~8 tests
- Edge Cases & Boundaries: ~8 tests

**Total: ~114 unit tests**

---

## Implementation Notes

1. **Isolation**: Each test should be independent; use fresh instances of facades/commands
2. **Cleanup**: Use test destructors or cleanup functions to avoid memory leaks
3. **Mocking**: Consider mocking Mediators if needed to verify calls
4. **Error Messages**: Include descriptive failure messages for debugging
5. **Coverage**: Aim for 100% line coverage of facade and command code
6. **Performance**: Each test should run in <100ms
7. **Determinism**: Tests should produce consistent results (no random data)
