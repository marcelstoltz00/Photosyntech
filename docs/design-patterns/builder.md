# Builder Pattern

## Responsibility
Separates the construction of complex plant objects from their representation, allowing the same construction process to create different plant species with varying configurations (water strategies, sun strategies, and maturity states).

The construction sequence is:
1. Create base plant object (Tree, Shrub, Herb, etc.)
2. Assign water strategy
3. Assign sun strategy
4. Assign maturity state
5. Add decorators (season and plant attributes)
6. Set up initial health, water, and sun levels

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Director** | `Director` | Orchestrates the plant construction process by calling builder methods in sequence. |
| **Builder** | `Builder` (abstract) | Defines the interface for creating plant components (water strategy, sun strategy, maturity state, decorators). |
| **ConcreteBuilder** | `CactusBuilder`<br>`CherryBlossomBuilder`<br>`JadePlantBuilder`<br>`LavenderBuilder`<br>`MapleBuilder`<br>`PineBuilder`<br>`RoseBuilder`<br>`SunflowerBuilder` | Implements specific construction steps for creating different plant species with their unique configurations. |
| **Product** | `PlantComponent` (`LivingPlant` and its subclasses) | The complex plant object being constructed, returned as a `PlantComponent`. |

## Functional Requirements

### Primary Requirements
- **FR-1: Plant Species Creation and Configuration** - Provides systematic plant creation from base types, ensures all required attributes are initialized, validates configuration options, and supports complex plant compositions.

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility** - Adding new plant species requires only creating a new builder class.
- **NFR-5: Reliability** - Ensures plants are always in a valid state after construction.

## System Role & Integration

### Pattern Integration
The **Builder** pattern serves as the primary **plant creation engine** in Photosyntech, orchestrating construction through these key interactions:

- **Strategy Pattern**: The builder assigns appropriate `WaterStrategy` and `SunStrategy` instances (retrieved as flyweights) to the plant.
- **State Pattern**: The builder initializes the plant with its starting `MaturityState` (typically `Seed`).
- **Decorator Pattern**: The builder applies decorators to the plant for seasonal attributes and physical characteristics (e.g., `Summer`, `LargeFlowers`).
- **Prototype Pattern**: The builder often starts with a prototypical `LivingPlant` instance which it then configures.
- **Singleton Pattern**: Builders obtain shared `Strategy` objects from a `FlyweightFactory` which is managed as a Singleton.
- **Composite Pattern**: The final product is a `PlantComponent`, which can be treated uniformly with other components or groups in the composite structure (`PlantGroup`).
- **Facade Pattern**: The `NurseryFacade` simplifies the creation of plants by providing a simple interface that internally uses a `Director` and a `Builder`.

### System Dependencies
- **Primary Consumer**: The inventory system, which uses the `NurseryFacade` to create new plants.
- **Integration Point**: The `Director` class, which encapsulates the construction logic.
- **Data Flow**: A client requests a plant from the `NurseryFacade`, which uses a `Director` and a concrete `Builder` to create the `PlantComponent`.

## Design Rationale

The Builder pattern was chosen for plant creation because:
1. **Complexity**: Plants require initialization of multiple attributes (species type, water strategy, sun strategy, maturity state, decorators, and initial levels).
2. **Flexibility**: Different plant species follow the same construction sequence but with different implementations for each step.
3. **Separation of Concerns**: The complex construction logic is isolated from the `PlantComponent`'s own logic.
4. **Extensibility**: Adding new plant species is simplified to creating a new `ConcreteBuilder` class.
