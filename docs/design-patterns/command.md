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
