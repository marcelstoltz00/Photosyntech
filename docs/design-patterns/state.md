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

## System Role & Integration

### Pattern Integration
The **State** pattern manages **plant lifecycle behavior** through these interactions:

- **Observer Pattern**: State changes trigger notifications to staff via subject interface
- **Builder Pattern**: Plants initialized in Seed state during construction
- **Strategy Pattern**: State may influence or modify strategy behavior
- **Command Pattern**: Staff actions may trigger state transitions
- **Composite Pattern**: Group state aggregates individual plant states
- **Decorator Pattern**: State affects decorated properties (e.g., mature plant pricing)
- **Prototype Pattern**: Cloned plants preserve their current state

### System Dependencies
- **Lifecycle Management**: Drives plant progression from Seed → Vegetative → Mature → Dead
- **Price Dynamics**: State transitions affect plant pricing (mature plants more valuable)
- **Care Requirements**: State may indicate different care needs and priorities
- **Observer Notifications**: Major lifecycle events trigger staff actions

## Design Rationale

The State pattern was chosen because:
1. **Behavior Variation**: Plant behavior changes dramatically across lifecycle stages
2. **Age-Based Transitions**: Automatic state transitions based on plant age
3. **Encapsulation**: Each state encapsulates its behavior and transition logic
4. **Extensibility**: New states added without modifying plant or existing states
5. **Clear Semantics**: State objects represent clear biological phases
6. **Observer Integration**: Natural fit with observer notifications on state changes

## Extension Points

**Adding New Lifecycle States:**
1. Create new `MaturityState` subclass in `state/` directory
2. Implement `update()` for age progression logic
3. Implement transition conditions to next state
4. Plant accesses state through abstract `MaturityState*` interface
5. Path: `state/NewLifecycleState.h` (e.g., `state/Blooming.h`)
6. Ensure minimum age and growth rate parameters defined
