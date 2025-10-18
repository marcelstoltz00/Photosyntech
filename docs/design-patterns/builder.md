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

## System Role & Integration

### Pattern Integration
The **Builder** pattern serves as the primary **plant creation engine** in Photosyntech, orchestrating construction through these key interactions:

- **Strategy Pattern**: Builder assigns appropriate `WaterStrategy` and `SunStrategy` instances (obtained from flyweight factories) during construction phase
- **State Pattern**: Builder initializes the plant with its starting maturity state (Seed) before inventory adoption
- **Decorator Pattern**: After construction, the base plant can be wrapped with visual/functional decorators in inventory
- **Prototype Pattern**: Builder creates initial plant templates that are then cloned for mass production
- **Singleton Pattern**: Director receives strategies from singleton-managed flyweight factories
- **Composite Pattern**: Built plants are added to plant groups in the centralized inventory
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

## Extension Points

**Adding New Plant Species:**
1. Create `NewPlantBuilder` class inheriting from `Builder`
2. Implement construction steps specific to the new plant type
3. Register builder in system factory/facade if needed
4. Example path: `builder/NewPlantBuilder.h` (following pattern in `builder/` directory)
