# Prototype Pattern

## 1. Responsibility
Specifies the kinds of objects to create using a prototypical instance, and creates new objects by copying this prototype. In this system, it allows for the efficient creation of new, fully-configured plant instances by cloning an already-configured object, preserving its internal state, strategies, and decorators.

## 2. File Structure
```
prototype/
├── LivingPlant.h/.cpp  # Abstract prototype, defines the clone interface and base copy logic
├── Herb.h/.cpp         # Concrete prototype
├── Shrub.h/.cpp        # Concrete prototype
├── Succulent.h/.cpp    # Concrete prototype
└── Tree.h/.cpp         # Concrete prototype
```

## 3. Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Abstract Prototype** | `LivingPlant` | Defines the `clone()` interface and provides the core copy-constructor logic that handles the shallow copy of all shared flyweight objects (strategies, states, name, etc.). |
| **Concrete Prototype** | `Herb`, `Shrub`, `Succulent`, `Tree` | The four base plant types. They implement `clone()` by calling their own copy constructor, which in turn delegates the core copying work back to `LivingPlant`. |
| **Client** | `Builder` | The primary client. After configuring a complex plant object (a `LivingPlant` wrapped in decorators), the builder's `getResult()` method calls `clone()` on the final object to produce identical copies for the inventory. |

## 4. Functional Requirements

### Primary Requirements
- **FR-2: Plant Type Cloning**: Directly enables the creation of new plant instances by copying existing, fully-configured plant objects, ensuring all properties (base type, decorations, strategies, and state) are preserved.

### Supporting Requirements
- **NFR-4: Scalability/Memory Efficiency**: The prototype's copy mechanism is designed to be highly efficient. It performs a shallow copy of pointers to shared flyweight objects (strategies, states, seasons), ensuring that creating thousands of clones has a minimal memory footprint.

## 5. System Role & Integration

The Prototype pattern is the system's engine for mass-producing plants, integrating tightly with several other patterns:

- **Builder Pattern**: The Builder's primary role is to construct a single, complex, fully-configured plant object. The Prototype pattern then takes over; the builder calls `clone()` on this finished object to stamp out identical copies for the inventory.

- **Decorator Pattern**: The cloning process is a deep copy of the decorator chain. When `clone()` is called on the outermost decorator, it clones itself and then recursively calls `clone()` on the component it wraps, all the way down to the base `LivingPlant`. This ensures each cloned plant has a new, independent decorator chain.

- **Flyweight Pattern**: The `LivingPlant` copy constructor, which is at the heart of the clone operation, is designed to support the Flyweight pattern. It performs a **shallow copy** of all flyweight pointers (`name`, `season`, `waterStrategy`, `sunStrategy`, `maturityState`). This is critical for memory efficiency, as it ensures all cloned plants share the same immutable state and strategy objects.

### The Cloning Process in Detail

When a client needs a copy of a fully built plant (e.g., a Rose with decorators for thorns and flowers), the process is simple and powerful:

1.  The client calls `clone()` on the outermost object (e.g., the `Thorns` decorator instance).
2.  The `Thorns` decorator's `clone()` method creates a `new Thorns()` and, in its copy constructor, calls `clone()` on the object it wraps (the `Flowers` decorator).
3.  This process cascades downwards through the decorator chain until the `LivingPlant::clone()` method is called.
4.  `LivingPlant::clone()` calls its copy constructor, which performs a shallow copy of all its members, including the pointers to the shared flyweight objects.
5.  The result is a brand new, fully independent `PlantComponent` that is an exact replica of the original, with a deep-copied decorator chain and shallow-copied flyweight data.

## 6. Design Rationale

The Prototype pattern was chosen for plant replication because:

1.  **Performance**: Cloning a pre-configured plant is significantly faster than repeatedly using the Builder to construct each new plant from scratch.
2.  **Configuration Preservation**: It guarantees an exact, faithful copy of a complex object without needing to know the details of its construction.
3.  **Memory Efficiency**: The shallow-copy approach for flyweights is essential for scalability, preventing massive memory consumption when creating thousands of plant instances.
4.  **Simplicity for the Client**: The client (the `Builder`) does not need to know how to construct a complex object; it only needs a single `clone()` call to get a perfect copy.

![Prototype Diagram](https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/Prototype.jpg)