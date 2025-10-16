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
