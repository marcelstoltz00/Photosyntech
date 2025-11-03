# Strategy Pattern

## 1. Responsibility
Defines a family of interchangeable algorithms for plant care operations—specifically watering and sunlight exposure. This allows the algorithm to be selected and swapped at runtime based on the plant's species, its current state, or environmental needs.

## 2. File Structure
```
strategy/
├── WaterStrategy.h       # Abstract interface for all watering strategies
├── SunStrategy.h         # Abstract interface for all sunlight strategies
├── LowWater.h/.cpp       # Concrete strategy for minimal watering
├── MidWater.h/.cpp       # Concrete strategy for moderate watering
├── HighWater.h/.cpp      # Concrete strategy for abundant watering
├── AlternatingWater.h/.cpp # Concrete strategy for cyclical watering
├── LowSun.h/.cpp         # Concrete strategy for low sunlight
├── MidSun.h/.cpp         # Concrete strategy for medium sunlight
├── HighSun.h/.cpp        # Concrete strategy for high sunlight
└── AlternatingSun.h/.cpp # Concrete strategy for alternating sunlight
```

## 3. Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Context** | `LivingPlant` | Maintains references to `WaterStrategy` and `SunStrategy` objects and delegates care operations to them. |
| **Strategy** | `WaterStrategy` (abstract)<br>`SunStrategy` (abstract) | Define the common interface for their respective algorithm families. |
| **ConcreteStrategy** | **Water:** `LowWater`, `MidWater`, `HighWater`, `AlternatingWater`<br>**Sun:** `LowSun`, `MidSun`, `HighSun`, `AlternatingSun` | Implement specific care algorithms. Each contains a `static int getID()` for identification within the Flyweight factory. |

## 4. Functional Requirements

### Primary Requirements
- **FR-4: Watering Management**: Implements different watering approaches (e.g., `LowWater`, `HighWater`) that define the water amount and frequency for various plant types.
- **FR-5: Sunlight Management**: Implements different sunlight exposure approaches (e.g., `LowSun`, `HighSun`) that a define the intensity and duration of sun needed.

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility**: New care routines can be added by creating new strategy classes without modifying the `LivingPlant` context or other existing strategies.
- **FR-10: Shared Data Memory Optimisation**: Strategy objects are shared as Flyweights to reduce memory consumption.

## 5. System Role & Integration

### Pattern Integration
The **Strategy** pattern defines **interchangeable care algorithms** through these interactions:

- **Direct Plant Modification**: Strategy objects receive a pointer to the `LivingPlant` context and directly modify its attributes (e.g., `waterLevel`, `sunExposure`).
- **Flyweight Pattern**: To conserve memory (NFR-4), individual strategy instances are not created for each plant. Instead, they are shared as Flyweights, managed by a `FlyweightFactory`. The `static int getID()` method in each concrete strategy provides a unique key for the factory to retrieve the shared instance.
- **Builder Pattern**: The appropriate `WaterStrategy` and `SunStrategy` are selected and assigned to a `LivingPlant` during its construction by a concrete `Builder`.
- **State Pattern**: A plant's maturity state can influence which strategy is most effective, though the core implementation does not automatically swap strategies based on state changes.
- **Facade Pattern**: Staff care operations, initiated through the `NurseryFacade`, trigger the execution of the currently assigned strategies.

### Algorithm Details
- **`AlternatingWater`**: Implements a cyclical watering pattern where the amount of water progressively increases over subsequent calls before resetting, simulating a wet/dry cycle.
- **`AlternatingSun`**: Implements a sun exposure pattern that toggles between two distinct levels of intensity and duration with each application.

## 6. Design Rationale

The Strategy pattern was chosen because:
1. **Multiple Algorithms**: The system needed to support many different algorithms for watering and sunlight exposure to suit a wide variety of plants.
2. **Runtime Flexibility**: Although strategies are typically set at construction by the Builder, the pattern allows for the possibility of changing them at runtime.
3. **Decoupling**: It decouples the algorithm logic from the `LivingPlant` class, which simplifies the `LivingPlant` and makes the strategies easier to maintain.
4. **Extensibility**: New care routines can be added by simply creating a new strategy class, without touching the context.
5. **Optimization**: The pattern works seamlessly with the Flyweight pattern to allow for the sharing of strategy objects, which is critical for memory efficiency when simulating millions of plants.

![Strategy Diagram](https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/Strategies.jpg)