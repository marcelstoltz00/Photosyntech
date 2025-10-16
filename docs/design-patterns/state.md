# State Pattern

## Responsibility
Manages plant lifecycle transitions by allowing plants to change their behavior based on their current maturity state (Seed, Vegetative, Mature, Dead), with each state defining its own growth rate and age boundaries.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Context** | `LivingPlant` | Maintains a reference to the current MaturityState and delegates state-dependent behavior |
| **State** | `MaturityState` (abstract) | Defines the interface for encapsulating behavior associated with a particular maturity stage |
| **ConcreteState** | `Seed`<br>`Vegetative`<br>`Mature`<br>`Dead` | Implements specific growth behavior and handles state transitions based on plant age |

## Functional Requirements

### Primary Requirements
- **FR-3: Plant Lifecycle Management** - Manages plant maturity states with minimum ages, growth rates, and price adjustments; enables automatic transitions between states based on age

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility** - New maturity states can be added without modifying existing states or the plant class
- **FR-8: Inventory Tracking and Notifications** - State changes trigger observer notifications to alert staff of lifecycle transitions
