# Command Pattern

## Responsibility
Encapsulates nursery operations (adding inventory, browsing plants, watering, purchasing) as objects, enabling operation queuing, logging, and undo functionality while decoupling user interface actions from business logic.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Command** | `Command` (abstract) | Declares the interface for executing and undoing operations. |
| **ConcreteCommand** | `AddToInventoryCommand`<br>`BrowsePlantsCommand`<br>`WaterPlantCommand`<br>`PurchasePlantCommand` | Implements specific nursery operations by binding a `Receiver` with an action. Stores the necessary parameters and state for execution and undo. |
| **Invoker** | `NurseryFacade` | Stores and executes commands, and maintains a history for undo operations. The `TUI` acts as a client that triggers the `Invoker`. |
| **Receiver** | `PlantGroup`, `LivingPlant`, `Singleton` (inventory) | The objects that perform the actual work when a command is executed. For example, a `LivingPlant` is the receiver of a `WaterPlantCommand`. |

## Functional Requirements

### Primary Requirements
- **FR-13: Staff Action Execution** - Allows staff to execute actions (watering, inventory management, care routines); encapsulates complex multi-step actions to support undo/redo functionality; decouples UI actions from business logic.

### Supporting Requirements
- **FR-15: Plant Sales Transactions** - Purchase commands encapsulate transaction logic.
- **NFR-3: Usability** - Commands provide clear action abstractions for the user interface.
- **NFR-5: Reliability** - Undo functionality prevents errors from becoming permanent.
- **FR-17: Unified System Interface** - Commands provide a consistent interface for all system operations.

## System Role & Integration

### Pattern Integration
The **Command** pattern enables **operation encapsulation and reversibility** through these interactions:

- **Facade Pattern**: The `NurseryFacade` acts as the primary `Invoker`, simplifying the execution of commands for the client (e.g., the `TUI`).
- **Singleton Pattern**: Commands often interact with the `Singleton` inventory to access and modify plant data.
- **Composite Pattern**: Commands can operate on individual `PlantComponent` objects or entire `PlantGroup` composites uniformly.
- **Observer Pattern**: The execution of a command can trigger notifications to `Observer`s (e.g., a change in a plant's state).
- **Mediator Pattern**: The `PurchasePlantCommand` uses the `SalesFloor` `Mediator` to coordinate the complex process of a plant sale.
- **Builder Pattern**: While not directly invoking the builder, the `AddToInventoryCommand` is used to add plants created by the `Builder` pattern to the inventory.

### System Dependencies
- **Action Abstraction**: All user actions are encapsulated as reusable command objects.
- **History Tracking**: The `NurseryFacade` can store a history of executed commands to support undo/redo functionality.
- **Delayed Execution**: Commands can be queued for later execution.
- **Logging Foundation**: The structure of command objects enables the creation of audit trails for operations.

## Design Rationale

The Command pattern was chosen because:
1. **Separation**: It decouples the object that invokes an operation from the one that knows how to perform it.
2. **Flexibility**: Operations are treated as first-class objects that can be stored, queued, and passed as parameters.
3. **Undo/Redo**: The pattern provides a straightforward mechanism for implementing undo and redo functionality.
4. **Consistency**: All user actions can be executed through the same command interface.
5. **Extensibility**: New operations can be added by creating new command classes without modifying existing code.

## Extension Points

**Adding New Operations:**
1. Create a new concrete command class inheriting from `Command` in the `command/` directory.
2. Implement the `execute()` method to perform the operation. This typically involves calling a method on a `Receiver` object.
3. Implement the `undo()` method to reverse the effects of the `execute()` method. This may require storing the state of the `Receiver` before the operation.
4. The new command can then be instantiated and executed by the `Invoker` (`NurseryFacade`).
