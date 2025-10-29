# State Pattern

## Responsibility
Manages plant lifecycle transitions by allowing plants to change their behavior based on their current maturity state (Seed, Vegetative, Mature, Dead). Each state defines its own growth parameters including age boundaries, health ranges, water requirements, sun exposure needs, and daily growth behaviors.

## Implementation Details

### State Parameters
Each state implements specific parameters as defined in the state transition documentation:

- **Seed**: 
  - Age: 0-6 days
  - Health: 30-100
  - Water: 40-100
  - Sun: 20-100
  - Water usage: 6 units/day
  - Health gain: +4/day when conditions met

- **Vegetative**:
  - Age: 7-29 days
  - Health: 40-100
  - Water: 25-100
  - Sun: 40-100
  - Water usage: 10 units/day
  - Health gain: +3/day when conditions met

- **Mature**:
  - Age: 30-119 days
  - Health: 30-100
  - Water: 30-100
  - Sun: 40-100
  - Water usage: 8 units/day
  - Health gain: +1/day when conditions met

- **Dead**:
  - Age: ≥120 days
  - Terminal state
  - All parameters set to 0

### Seasonal Influence
Water usage is modified by seasonal multipliers:
- Spring: 0.9x
- Summer: 1.3x
- Autumn: 1.0x
- Winter: 0.8x

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

### Growth Process Implementation
Each state implements a standard growth process following these steps:
1. Increment plant age by 1 day
2. Calculate water usage based on base rate × seasonal multiplier
3. Update water level (clamped to 0-100)
4. Check minimum requirements for health gain
   - If water and sun requirements met, apply health gain
   - Health clamped to 0-100
5. Check state transition conditions
   - If conditions met, transition to next state with parameter resets
   - No reverse transitions allowed
   - Dead state is terminal

### Pattern Integration
The **State** pattern manages **plant lifecycle behavior** through these interactions:

- **Observer Pattern**: State changes trigger notifications to staff via subject interface
- **Builder Pattern**: Plants initialized in Seed state during construction
- **Strategy Pattern**: State affects water and sun exposure strategies
- **Facade Pattern**: Care operations may trigger state transitions through plant lifecycle
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
1. **Behavior Variation**: Plant behavior changes dramatically across lifecycle stages with distinct parameter ranges and growth rates
2. **Complex Transitions**: Manages transitions based on multiple conditions (age, health, water, sun exposure)
3. **Encapsulation**: Each state encapsulates its specific growth parameters, behavior, and transition logic
4. **Seasonal Adaptation**: Supports seasonal modifications to water usage through multipliers
5. **Parameter Management**: Handles automatic clamping and reset of health, water, and sun exposure values
6. **Clear Boundaries**: Enforces well-defined age ranges and parameter limits for each growth stage
7. **Extensibility**: New states can be added without modifying plant or existing states
8. **Observer Integration**: Natural fit with observer notifications for state changes


