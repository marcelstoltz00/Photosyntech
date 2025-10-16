# Facade Pattern

## Responsibility
Provides a simplified, unified interface to the complex nursery subsystems (plant creation, inventory management, sales, commands), hiding system complexity from user interfaces and external clients.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Facade** | `NurseryFacade` | Provides high-level methods for common operations; delegates to appropriate subsystems; coordinates complex multi-step processes |
| **Subsystems** | `Director` (plant creation)<br>`Singleton` (inventory)<br>`Mediator` classes (staff/customer interaction)<br>`Command` classes (operations)<br>`Iterator` factories (filtering) | Implement detailed subsystem functionality; work together through facade coordination |
| **Client** | `GUI`<br>External interfaces | Uses the facade to interact with the system through simple method calls |

## Functional Requirements

### Primary Requirements
- **FR-17: Unified System Interface** - Provides simplified interface layer handling all business logic and coordinating subsystem interactions; enables GUI and CLI to interact through simple function calls; decouples business logic from presentation layer

### Supporting Requirements
- **NFR-3: Usability** - Simplifies complex operations into easy-to-understand methods
- **NFR-5: Reliability** - Centralizes coordination logic, reducing coupling between subsystems
- **NFR-2: Maintainability/Extensibility** - Changes to subsystem implementation hidden behind stable facade interface
- **All FRs** - Facade provides access to all functional requirements through unified interface
