# Facade Pattern

## Responsibility
Provides a simplified, unified interface to the complex nursery subsystems (plant creation, inventory management, sales, operations), hiding system complexity from user interfaces and external clients.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Facade** | `NurseryFacade` | Provides high-level methods for common operations; delegates to appropriate subsystems; coordinates complex multi-step processes |
| **Subsystems** | `Director` (plant creation)<br>`Singleton` (inventory)<br>`Mediator` classes (staff/customer interaction)<br>`Iterator` factories (filtering) | Implement detailed subsystem functionality; work together through facade coordination |
| **Client** | `TUI`<br>External interfaces | Uses the facade to interact with the system through simple method calls |

## Functional Requirements

### Primary Requirements
- **FR-17: Unified System Interface** - Provides simplified interface layer handling all business logic and coordinating subsystem interactions; enables TUI and CLI to interact through simple function calls; decouples business logic from presentation layer

### Supporting Requirements
- **NFR-3: Usability** - Simplifies complex operations into easy-to-understand methods
- **NFR-5: Reliability** - Centralizes coordination logic, reducing coupling between subsystems
- **NFR-2: Maintainability/Extensibility** - Changes to subsystem implementation hidden behind stable facade interface
- **All FRs** - Facade provides access to all functional requirements through unified interface

## System Role & Integration

### Pattern Integration
The **Facade** pattern serves as the **unified system entry point**, coordinating all patterns:

- **All 11 Other Patterns**: Facade delegates to Director (Builder), Singleton (resources), Mediators (staff/customer), Iterators (filtering), etc.
- **Director & Builder**: Delegates plant creation requests
- **Singleton**: Accesses centralized inventory and resource management
- **Mediator**: Routes customer requests through appropriate floor mediators
- **Iterator & Composite**: Filters and accesses plant collections
- **Observer & Subject**: Coordinates staff monitoring setup
- **Decorator & Prototype**: Provides plant customization and cloning operations
- **Strategy & Flyweight**: Ensures strategy reuse and memory efficiency

### System Dependencies
- **Single Integration Point**: Only interface TUI and CLI need to know about
- **Business Logic Coordination**: Coordinates complex multi-step operations
- **Subsystem Isolation**: Changes to subsystems don't affect external interfaces
- **Operation Routing**: Routes different operation types to appropriate pattern implementations

## Design Rationale

The Facade pattern was chosen because:
1. **Complexity Hiding**: Shields TUI/CLI from 12 pattern interactions
2. **Integration Point**: Single place to coordinate cross-pattern workflows
3. **API Stability**: External interfaces remain stable despite internal changes
4. **Reduced Coupling**: TUI/CLI depend only on facade, not individual patterns
5. **Operation Composition**: Complex operations built from simpler pattern operations

## Extension Points

**Adding New System Operations:**
1. Add public method to `NurseryFacade` in `facade/NurseryFacade.h`
2. Method coordinates appropriate pattern operations internally
3. Return results through consistent interface
4. Example: `plantSeason(plant, season)` could compose Decorator and Observer patterns
5. Path: `facade/NurseryFacade.h` - single location for all new high-level operations
