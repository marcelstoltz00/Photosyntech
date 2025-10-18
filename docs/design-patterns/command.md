# Command Pattern

## Responsibility
Encapsulates nursery operations (adding inventory, browsing plants, watering, purchasing) as objects, enabling operation queuing, logging, and undo functionality while decoupling user interface actions from business logic.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Command** | `Command` (abstract) | Declares the interface for executing and undoing operations |
| **ConcreteCommand** | `AddToInventoryCommand`<br>`BrowsePlantsCommand`<br>`WaterPlantCommand`<br>`PurchasePlantCommand` | Implement specific nursery operations; store necessary parameters and state for execution and undo |
| **Invoker** | `NurseryFacade`<br>`GUI` | Stores and executes commands; maintains command history for undo operations |
| **Receiver** | `Singleton` (inventory)<br>`PlantGroup`<br>`LivingPlant` | The objects that perform the actual work when commands are executed |

## Functional Requirements

### Primary Requirements
- **FR-13: Staff Action Execution** - Allows staff to execute actions (watering, inventory management, care routines); encapsulates complex multi-step actions to support undo/redo functionality; decouples UI actions from business logic

### Supporting Requirements
- **FR-15: Plant Sales Transactions** - Purchase commands encapsulate transaction logic
- **NFR-3: Usability** - Commands provide clear action abstractions for the user interface
- **NFR-5: Reliability** - Undo functionality prevents errors from becoming permanent
- **FR-17: Unified System Interface** - Commands provide consistent interface for all system operations

## System Role & Integration

### Pattern Integration
The **Command** pattern enables **operation encapsulation and reversibility** through these interactions:

- **Facade Pattern**: NurseryFacade invokes commands and manages command history
- **Singleton Pattern**: Commands modify inventory and resources accessed through singleton
- **Composite Pattern**: Commands operate on plant components and groups uniformly
- **Observer Pattern**: Command execution may trigger observer notifications (e.g., state changes)
- **Mediator Pattern**: Sales transactions encapsulated as purchase commands
- **Builder Pattern**: Plant creation wrapped as command with undo capability
- **GUI/CLI**: User interactions translated to commands for consistent processing

### System Dependencies
- **Action Abstraction**: All user actions encapsulated as reusable command objects
- **History Tracking**: Commands stored for undo/redo functionality
- **Delayed Execution**: Commands can be queued and executed later
- **Logging Foundation**: Command object structure enables operation audit trails

## Design Rationale

The Command pattern was chosen because:
1. **Separation**: Decouples UI actions from business logic
2. **Flexibility**: Operations treated as first-class objects (queued, logged, replayed)
3. **Undo/Redo**: Command structure naturally supports action reversal
4. **Consistency**: All user actions follow same command execution path
5. **Extensibility**: New operations added as new command classes without modifying invokers

## Extension Points

**Adding New Operations:**
1. Create concrete command class inheriting from `Command` in `command/` directory
2. Implement `execute()` to perform the operation
3. Implement `undo()` to reverse effects (store state if needed)
4. Example commands: `WaterPlantCommand`, `AddToInventoryCommand`, `PurchasePlantCommand`
5. Path: `command/NewOperationCommand.h` (follow naming convention)
6. Register command in Facade for unified access
