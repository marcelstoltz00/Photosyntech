# Builder Pattern

## Responsibility
Separates the construction of complex plant objects from their representation, allowing the same construction process to create different plant species with varying configurations (water strategies, sun strategies, and maturity states).

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Director** | `Director` | Orchestrates the plant construction process by calling builder methods in sequence |
| **Builder** | `Builder` (abstract) | Defines the interface for creating plant components (water strategy, sun strategy, maturity state) |
| **ConcreteBuilder** | `Plant3Builder`<br>`SunflowerBuilder`<br>`RoseBuilder` | Implements specific construction steps for creating different plant species with their unique configurations |
| **Product** | `LivingPlant` and subclasses<br>(Succulent, Shrub, Tree, Herb) | The complex plant object being constructed with all necessary strategies and states |

## Functional Requirements

### Primary Requirements
- **FR-1: Plant Species Creation and Configuration** - Provides systematic plant creation from base types, ensures all required attributes are initialized, validates configuration options, and supports complex plant compositions

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility** - Adding new plant species requires only creating a new builder class
- **NFR-5: Reliability** - Ensures plants are always in a valid state after construction
