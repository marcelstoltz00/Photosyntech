# Builder Pattern

## 1. Responsibility
Separates the construction of complex plant objects from their representation. This allows the same construction process, orchestrated by a `Director`, to create different and complex plant species, each with its own unique set of strategies, decorators, and initial states.

## 2. File Structure
```
builder/
├── Director.h/.cpp               # Orchestrates the build process
├── Builder.h/.cpp                # Abstract builder interface
├── RoseBuilder.h/.cpp            # Concrete builder for Roses
├── SunflowerBuilder.h/.cpp     # Concrete builder for Sunflowers
├── CactusBuilder.h/.cpp          # Concrete builder for Cacti
├── CherryBlossomBuilder.h/.cpp # Concrete builder for Cherry Blossoms
├── JadePlantBuilder.h/.cpp       # Concrete builder for Jade Plants
├── LavenderBuilder.h/.cpp      # Concrete builder for Lavender
├── MapleBuilder.h/.cpp           # Concrete builder for Maple Trees
└── PineBuilder.h/.cpp            # Concrete builder for Pine Trees
```

## 3. Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Director** | `Director` | Orchestrates the plant construction by calling the abstract builder's methods in a predefined sequence. |
| **Builder** | `Builder` (abstract) | Defines the abstract interface for the construction steps (e.g., `createObject`, `assignWaterStrategy`, `addDecorators`). |
| **ConcreteBuilder** | `CactusBuilder`, `RoseBuilder`, etc. | Implement the builder interface to construct a specific plant species with its unique configuration of prototype, strategies, and decorators. |
| **Product** | `PlantComponent` | The complex object being constructed. The builder's `getResult()` method returns a clone of the fully configured plant. |

## 4. Functional Requirements

### Primary Requirements
- **FR-1: Plant Species Creation and Configuration**: Directly addressed by providing a controlled, step-by-step process for creating complex plant compositions from a base type and ensuring all required attributes are initialized.

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility**: New plant species can be introduced by simply adding a new `ConcreteBuilder` class, without altering the Director or existing builders.
- **NFR-5: Reliability**: The pattern ensures that plants are only returned to the client after being fully constructed, preventing partially-initialized objects.

## 5. System Role & Integration

The **Builder** pattern is the cornerstone of plant creation, orchestrating several other patterns:

- **Director-Driven Construction**: The `Director` dictates a fixed construction sequence, ensuring every plant is built consistently:
  1. `createObject()`
  2. `assignWaterStrategy()`
  3. `assignSunStrategy()`
  4. `assignMaturityState()`
  5. `addDecorators()`
  6. `setUp()` (for initial health/water/sun levels)

- **Prototype & Cloning**: The builder first creates a base `LivingPlant` object (e.g., `Tree`, `Shrub`), which acts as a prototype. After the director process is complete, the `getResult()` method returns a `clone()` of the finished product. This allows the same builder instance to be reused to efficiently produce multiple identical plants.

- **Pattern Integration**:
  - **Strategy Pattern**: The builder assigns `WaterStrategy` and `SunStrategy` objects to the plant.
  - **State Pattern**: The builder sets the plant's initial `MaturityState` (usually `Seed`).
  - **Decorator Pattern**: The builder applies seasonal and physical decorators (`Summer`, `Thorns`, etc.).
  - **Singleton & Flyweight**: Builders fetch shared `Strategy` instances from the `FlyweightFactory`, which is managed by the `Inventory` Singleton, to conserve memory.
  - **Facade Pattern**: The `NurseryFacade` provides a simplified `createPlant()` method to the client, hiding the complexity of initializing the Director and a specific ConcreteBuilder.

## 6. Design Rationale

The Builder pattern was chosen because:
1. **Complex Construction**: Creating a plant is a multi-step process involving a base type, strategies, state, decorators, and initial values. Builder manages this complexity effectively.
2. **Separation of Concerns**: It separates the high-level construction logic (the `Director`) from the specific details of creating a particular plant (the `ConcreteBuilder`).
3. **Extensibility**: The system can be extended with new plant types with minimal changes to existing code.
4. **Controlled Process**: The `Director` ensures that every plant is constructed in the correct order and is always in a valid, complete state when it is retrieved.

![Builder Diagram](https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/Builder.jpg)