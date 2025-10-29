# Mediator Pattern

## Responsibility
Coordinates interactions between staff and customers on different floors (sales and suggestions) without direct coupling, centralizing communication logic and preventing complex interdependencies.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Mediator** | `Mediator` (abstract) | Defines interface for communicating with colleagues |
| **ConcreteMediator** | `SalesFloor`<br>`SuggestionFloor` | Implements coordination logic; maintains references to staff and customers; routes requests appropriately |
| **Colleague** | `User` (abstract)<br>`Customer`<br>`Staff` | Communicate with each other through the mediator instead of directly |

## Functional Requirements

### Primary Requirements
- **FR-14: Staff-Customer Communication** - Coordinates communication between staff and customers on the sales floor; keeps staff and customers independent; enables central communication coordination

### Supporting Requirements
- **NFR-5: Reliability** - Decouples staff and customers, allowing changes to one without affecting the other
- **FR-15: Plant Sales Transactions** - Sales floor mediates purchase interactions
- **NFR-2: Maintainability/Extensibility** - New interaction types can be added to mediator without modifying staff or customer classes

## System Role & Integration

### Pattern Integration
The **Mediator** pattern enables **staff-customer coordination** through these interactions:

- **Observer Pattern**: Staff (observers) execute actions coordinated by mediator
- **Facade Pattern**: Facade coordinates mediator actions and purchase operations
- **Composite Pattern**: Mediator routes requests involving plant groups (customer baskets)
- **Singleton Pattern**: Mediator accesses singleton inventory during transactions
- **Facade Pattern**: Facade coordinates mediator setup and initial interactions
- **Builder Pattern**: Mediator may request new plant creation through facade/builder
- **Decorator Pattern**: Mediator handles decorated plant transactions

### System Dependencies
- **SalesFloor**: Mediates customer purchases and staff processing
- **SuggestionFloor**: Mediates customer suggestions and staff recommendations
- **Communication Hub**: Central coordination point for all staff-customer interactions
- **Request Routing**: Routes different request types to appropriate staff

## Design Rationale

The Mediator pattern was chosen because:
1. **Complex Interactions**: Multiple staff and customers with varying interaction types
2. **Loose Coupling**: Staff and customers don't need to know each other directly
3. **Centralized Logic**: All interaction rules in one place (mediator)
4. **Scalability**: Adding new staff/customer types doesn't complicate interactions
5. **Multiple Mediators**: Different floors can have different coordination strategies
6. **Flexibility**: Interaction rules modified in mediator without changing participants

## Extension Points

**Adding New Interaction Types:**
1. Create new `Mediator` subclass in `mediator/` directory
2. Define specialized staff and customer roles if needed
3. Implement coordination logic for new interaction pattern
4. Path: `mediator/NewFloor.h` (e.g., `mediator/ConsultationFloor.h`)
5. Register mediator with system through Facade
6. Extend `User` base class if new participant type needed
