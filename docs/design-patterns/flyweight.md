# Flyweight Pattern

## 1. Responsibility
Minimizes memory consumption by sharing immutable data objects across multiple plant instances. It achieves this by externalizing a plant's extrinsic state and sharing its intrinsic state (e.g., season names, water strategies, sun strategies, maturity states) through a centralized caching mechanism.

## 2. File Structure
```
flyweight/
├── Flyweight.h/.cpp        # Wrapper for shared intrinsic state
└── FlyweightFactory.h/.cpp # Manages the cache of Flyweight objects
```

## 3. Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Flyweight** | `Flyweight<T>` | Wraps shared, immutable intrinsic state (`T data`) and provides access via `getState()`. Its destructor is responsible for deleting the wrapped raw pointer. |
| **FlyweightFactory** | `FlyweightFactory<ID, T>` | Creates and manages a cache (`std::unordered_map`) of `Flyweight<T>` objects, keyed by `ID`. It returns existing instances if available or creates new ones. |
| **Client** | `LivingPlant`, `Inventory` | `LivingPlant` holds pointers to `Flyweight<T>` instances for its intrinsic state. `Inventory` instantiates and manages the `FlyweightFactory` instances. |
| **Intrinsic State** | `std::string` (for season names, plant names), `WaterStrategy*`, `SunStrategy*`, `MaturityState*` | The shared, immutable data objects that are managed and reused by the Flyweight pattern. |

## 4. Functional Requirements

### Primary Requirements
- **FR-10: Shared Data Memory Optimization**: Directly addresses this by minimizing memory usage through aggressive sharing of immutable data, significantly reducing the memory footprint for large numbers of plants.

### Supporting Requirements
- **NFR-4: Scalability**: Essential for enabling the system to efficiently handle simulations with up to 100 million unique plant instances without memory exhaustion, ensuring memory scales sub-linearly with plant count.
- **NFR-1: Performance**: Reduces memory allocation overhead and improves cache locality, contributing to better overall system performance.
- **FR-6: Centralized Inventory**: Works in conjunction with the `Inventory` singleton to centralize the management and access of all shared resources.

## 5. System Role & Integration

The **Flyweight** pattern is fundamental for **memory optimization** and **scalability** within the Photosyntech system:

- **Managed by Singleton**: Three primary `FlyweightFactory` instances (for strings, strategies, and states) are instantiated and managed by the `Inventory` singleton, providing global, centralized access to shared objects.

- **Efficient Retrieval**: When a client (e.g., a `LivingPlant` instance) needs an intrinsic state object (like a watering strategy), it requests a `Flyweight<T>` from the appropriate `FlyweightFactory` via the `Inventory` singleton. The factory quickly returns a cached instance if available or creates a new one.

- **Immutable Sharing**: Flyweight objects are designed to be immutable once created, allowing them to be safely shared across thousands or millions of `LivingPlant` instances. Each `LivingPlant` holds only a pointer to its `Flyweight` instances, rather than a unique copy of the data.

- **Ownership and Lifetime**: The `FlyweightFactory` owns the `Flyweight<T>` objects it creates and manages their lifetime. Crucially, the `Flyweight<T>` object itself owns the raw pointer `T data` it wraps and `delete`s it in its destructor.

- **Pattern Integration**:
  - **Singleton Pattern**: The `Inventory` singleton owns and provides access to all `FlyweightFactory` instances.
  - **Builder Pattern**: Builders retrieve strategy and state flyweights from the `Inventory` during plant construction.
  - **Strategy Pattern**: `WaterStrategy` and `SunStrategy` objects are explicitly managed as flyweights.
  - **Prototype Pattern**: Cloned plants (via `LivingPlant`'s copy constructor) perform shallow copies of their `Flyweight<T>` pointers, further reinforcing memory efficiency across cloned instances.

## 6. Design Rationale

The Flyweight pattern was chosen for its critical role in addressing performance and scalability challenges:

1.  **Massive Duplication**: The system potentially handles millions of plants, each requiring references to the same limited set of strategies, states, and season names. Without Flyweight, this would lead to colossal memory consumption.
2.  **Immutability of Intrinsic State**: Data like strategies, states, and string names are immutable once defined, making them perfect candidates for sharing.
3.  **Memory Optimization Requirements**: The NFR-4 requirement for supporting 100 million plants necessitates aggressive memory optimization, which Flyweight provides by ensuring a sub-linear memory footprint.
4.  **Performance**: Reusing existing objects from the cache (`std::unordered_map`) is significantly faster than repeated allocation and deallocation for new objects.
5.  **Simplified Client Code**: Clients can use the objects as normal, unaware that they are shared instances, simplifying the application logic.

![Flyweight Diagram](https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/Flyweight.jpg)