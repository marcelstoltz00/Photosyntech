# Strategy Pattern

## Responsibility
Defines interchangeable algorithms for plant care operations (watering and sunlight exposure) that can be selected and modified at runtime based on plant type and environmental needs.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Context** | `LivingPlant` | Maintains references to WaterStrategy and SunStrategy and delegates care operations to them |
| **Strategy** | `WaterStrategy` (abstract)<br>`SunStrategy` (abstract) | Define interfaces for care algorithm families |
| **ConcreteStrategy** | **Water:** `LowWater`, `MidWater`, `HighWater`, `AlternatingWater`<br>**Sun:** `LowSun`, `MidSun`, `HighSun` | Implement specific care algorithms with varying water amounts, frequencies, sun intensity, and duration |

## Functional Requirements

### Primary Requirements
- **FR-4: Watering Management** - Implements different watering approaches defining water amount and frequency for different plant types; allows strategy changes based on plant lifecycle
- **FR-5: Sunlight Management** - Implements different sunlight exposure approaches defining intensity and duration for different plant types

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility** - New care strategies can be added without modifying plant classes
- **FR-13: Staff Action Execution** - Enables staff to execute watering and care routines through strategy execution
