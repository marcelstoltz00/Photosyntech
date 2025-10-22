# Builder Pattern

## Responsibility
Separates the construction of complex plant objects from their representation, allowing the same construction process to create different plant species with varying configurations (water strategies, sun strategies, and maturity states).

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Director** | `Director` | Orchestrates the plant construction process by calling builder methods in sequence |
| **Builder** | `Builder` (abstract) | Defines the interface for creating plant components (water strategy, sun strategy, maturity state) |
| **ConcreteBuilder** | `CactusBuilder`<br>`CherryBlossomBuilder`<br>`JadePlantBuilder`<br>`LavenderBuilder`<br>`MapleBuilder`<br>`PineBuilder`<br>`RoseBuilder`<br>`SunflowerBuilder` | Implements specific construction steps for creating different plant species with their unique configurations |
| **Product** | `LivingPlant` and subclasses<br>(Succulent, Shrub, Tree, Herb) | The complex plant object being constructed with all necessary strategies and states |

## Functional Requirements

### Primary Requirements
- **FR-1: Plant Species Creation and Configuration** - Provides systematic plant creation from base types, ensures all required attributes are initialized, validates configuration options, and supports complex plant compositions

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility** - Adding new plant species requires only creating a new builder class
- **NFR-5: Reliability** - Ensures plants are always in a valid state after construction

## System Role & Integration

### Pattern Integration
The **Builder** pattern serves as the primary **plant creation engine** in Photosyntech, orchestrating construction through these key interactions:

- **Strategy Pattern**: Builder assigns appropriate `WaterStrategy` and `SunStrategy` instances based on plant requirements (e.g., HighSun/LowWater for Cactus, MidSun/MidWater for Rose)
- **State Pattern**: Builder initializes the plant with its starting maturity state (Seed) before inventory adoption
- **Decorator Pattern**: After construction, plants are decorated with specific attributes (e.g., flower size, leaf size, stem size, thorns)
- **Prototype Pattern**: Builder creates base plant types (Tree, Herb, Shrub, Succulent) that serve as foundations
- **Singleton Pattern**: Director manages the construction process ensuring consistent plant creation
- **Composite Pattern**: Built plants can be organized into seasonal groups (Spring, Summer, Autumn, Winter)
- **Facade Pattern**: NurseryFacade delegates plant creation requests to Director, abstracting complexity

### System Dependencies
- **Primary Consumer**: Inventory system uses Builder for creating new plant species during initialization
- **Integration Point**: Director class acts as bridge between UI commands and plant creation logic
- **Data Flow**: Builder → Plant creation → Singleton inventory → Composite hierarchies

## Design Rationale

The Builder pattern was chosen for plant creation because:
1. **Complexity**: Plants require initialization of multiple attributes (species type, water strategy, sun strategy, maturity state)
2. **Flexibility**: Different plant species follow same construction sequence but with different strategy assignments
3. **Separation of Concerns**: Construction logic isolated from plant classes, enabling independent evolution
4. **Extensibility**: New plant species require only new builder classes, not modifications to existing plant code
