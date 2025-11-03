# Singleton Pattern

## 1. Responsibility
Ensures that a single, globally accessible instance of the `Inventory` class exists. This instance serves as the central authority for managing shared resources, including the main plant hierarchy, all flyweight factories, entity lists (staff and customers), and the global simulation clock (ticker).

## 2. File Structure
```
singleton/
├── Singleton.h     # Header for the Inventory class
└── Singleton.cpp   # Implementation of the Inventory class
```

## 3. Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Singleton** | `Inventory` | Guarantees only one instance of itself can be created via a private constructor and a static `getInstance()` method. It provides a global access point to all the resources it manages. |
| **Managed Resources** | `PlantGroup* inventory`<br>`FlyweightFactory<>* ...Factories`<br>`vector<Staff*>* staffList`<br>`vector<Customer*>* customerList` | The collection of system-wide resources owned and managed by the `Inventory` singleton. |

## 4. Functional Requirements

### Primary Requirements
- **FR-6: Centralised Inventory**: Directly implemented by providing a single, shared `PlantGroup` instance accessible system-wide.
- **FR-10: Shared Data Memory Optimisation**: Fulfilled by creating, managing, and providing access to all `FlyweightFactory` instances for strategies, states, and strings.

### Supporting Requirements
- **NFR-4: Scalability**: Centralizing shared flyweight objects is critical to reducing the memory footprint, allowing the system to scale to millions of plants.
- **NFR-5: Reliability**: By providing a single source of truth for the inventory and shared objects, the singleton prevents data inconsistencies.

## 5. System Role & Integration

The `Inventory` singleton acts as the **central nervous system** of the application.

- **Global Access Point**: The `static Inventory* getInstance()` method provides lazy initialization and global access to the single instance.

- **Flyweight Factory Hub**: It is the only place where `FlyweightFactory` objects are created. Any code that needs a shared object (like a `WaterStrategy` or `MaturityState`) must request it from the `Inventory` singleton. This centralizes and controls the creation of all flyweights.

- **Simulation Clock (Ticker)**: The singleton manages a background `thread` that drives the entire simulation. 
  - `startTicker()` and `stopTicker()` control the thread's lifecycle.
  - The thread periodically calls `tick()` on the entire inventory, causing plants to age and consume resources.
  - It also manages the progression of seasons (`changeSeason()`), making it the master clock for the application.

- **Pattern Integration**:
  - **Composite**: It holds the root `PlantGroup` of the entire plant inventory.
  - **Flyweight**: It creates and manages all `FlyweightFactory` instances.
  - **Builder**: Builders query the singleton to get flyweight objects (strategies, states) during plant construction.
  - **Facade**: The `NurseryFacade` relies on the singleton to access the inventory and other shared resources to fulfill its operations.

## 6. Design Rationale

The Singleton pattern was essential for this system because:
1. **Single Source of Truth**: A single inventory is mandatory to prevent data duplication and inconsistencies between what a customer sees and what a staff member manages.
2. **Centralized Resource Management**: The flyweight factories are critical for performance and must be shared globally. The singleton is the natural owner for these factories.
3. **Global Coordination**: The simulation ticker needs a single, authoritative owner to ensure time progresses consistently for all objects in the system.
4. **Controlled Initialization**: It guarantees that expensive resources (like the flyweight factories) are initialized only once and in the correct order.

![Singleton Diagram](https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/Singleton.jpg)