# Strategy Pattern

## Responsibility
Defines interchangeable algorithms for plant care operations (watering and sunlight exposure) that can be selected and modified at runtime based on plant type and environmental needs.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Context** | `LivingPlant` | Maintains references to WaterStrategy and SunStrategy and delegates care operations to them |
| **Strategy** | `WaterStrategy` (abstract)<br>`SunStrategy` (abstract) | Define interfaces for care algorithm families |
| **ConcreteStrategy** | **Water:** `LowWater`, `MidWater`, `HighWater`, `AlternatingWater`<br>**Sun:** `LowSun`, `MidSun`, `HighSun` | Implement specific care algorithms that directly modify plant's waterLevel and sunExposure attributes with varying amounts, frequencies, intensity, and duration |

## Functional Requirements

### Primary Requirements
- **FR-4: Watering Management** - Implements different watering approaches defining water amount and frequency for different plant types; allows strategy changes based on plant lifecycle
- **FR-5: Sunlight Management** - Implements different sunlight exposure approaches defining intensity and duration for different plant types

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility** - New care strategies can be added without modifying plant classes
- **FR-13: Staff Action Execution** - Enables staff to execute watering and care routines through strategy execution

## System Role & Integration

### Pattern Integration
The **Strategy** pattern defines **interchangeable care algorithms** through these interactions:

- **Direct Plant Modification**: Strategies directly modify plant's waterLevel and sunExposure attributes
- **Flyweight Pattern**: Strategy instances shared via singleton-managed flyweight factories
- **Builder Pattern**: Builder selects and assigns appropriate strategies during plant construction
- **State Pattern**: State may inform strategy selection or modification
- **Singleton Pattern**: Strategies obtained from singleton flyweight factories
- **Command Pattern**: Staff watering/care commands execute selected strategies
- **Composite Pattern**: Group operations apply strategies to all children
- **Decorator Pattern**: Seasonal decorators may adjust strategy requirements

### System Dependencies
- **Algorithm Encapsulation**: Different watering and sunlight approaches isolated as strategy classes
- **Runtime Selection**: Plants use different strategies based on type and lifecycle
- **Interchangeability**: Strategies implement common interface, enabling swapping
- **Memory Efficiency**: Sharing through flyweight prevents memory duplication
- **Direct State Management**: Strategies directly modify plant's internal state

## Design Rationale

The Strategy pattern was chosen because:
1. **Multiple Algorithms**: Different plant types need different watering/sun approaches
2. **Runtime Selection**: Strategy choice based on plant type (Builder phase)
3. **Algorithm Independence**: Strategies encapsulated separately from plant logic
4. **Consistency**: All plants use same algorithm family (WaterStrategy or SunStrategy)
5. **Extensibility**: New strategies added without modifying plant or existing strategies
6. **Optimization**: Strategy sharing via flyweight critical for memory efficiency
7. **Direct State Management**: Strategies can directly manipulate plant attributes

