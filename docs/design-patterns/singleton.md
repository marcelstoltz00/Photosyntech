# Singleton Pattern

## Responsibility
Ensures a single, globally accessible instance of the `Inventory` class exists, providing centralized access to shared plant data, flyweight factories, and a thread-safe ticking mechanism for inventory updates.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|---|---|---|
| **Singleton** | `Inventory` | Ensures only one instance exists; provides a global access point through `getInstance()`; manages the inventory, flyweight factories, staff/customer lists, and a background ticker thread. |
| **Managed Resources** | `PlantGroup* inventory`<br>`FlyweightFactory<string, string*>* stringFactory`<br>`FlyweightFactory<int, WaterStrategy*>* waterStrategies`<br>`FlyweightFactory<int, SunStrategy*>* sunStrategies`<br>`FlyweightFactory<int, MaturityState*>* states`<br>`vector<Staff*>* staffList`<br>`vector<Customer*>* customerList` | Centralized resources managed by the `Inventory` singleton instance. |

## Functional Requirements

### Primary Requirements
- **FR-6: Centralized Inventory** - Maintains a single, shared inventory accessible to both customers and staff to ensure consistency.
- **FR-10: Shared Data Memory Optimization** - Manages flyweight factories that minimize memory usage by sharing immutable data objects.

### Supporting Requirements
- **NFR-4: Scalability** - Central management of shared objects reduces the memory footprint for large inventories.
- **NFR-5: Reliability** - A single source of truth prevents data inconsistencies.
- **FR-17: Unified System Interface** - Provides a centralized access point for system-wide resources.

## System Role & Integration

### Pattern Integration
The **Singleton** pattern serves as the **central resource hub** of Photosyntech, managing these critical interactions:

- **Flyweight Pattern**: Manages flyweight factories for water strategies, sun strategies, maturity states, and season names.
- **Composite Pattern**: Owns and manages the root `PlantGroup` representing the centralized inventory.
- **Builder Pattern**: The `Director` accesses the singleton to obtain strategy and state instances during plant construction.
- **Facade Pattern**: The `NurseryFacade` accesses the singleton for inventory operations and resource management, and modifies the inventory state through direct facade operations.
- **Observer Pattern**: The `PlantGroup` (managed by the singleton) acts as a `Subject` for staff notifications.
- **Iterator Pattern**: Iterator factories obtain a reference to the plant collection from the singleton inventory.

### Multithreading
The `Inventory` singleton also manages a background thread that periodically updates the state of all plants in the inventory. This is handled by:

- A `TickerThread` that runs in the background.
- An `on` flag to safely start and stop the thread.
- A `TickInventory()` method that is called by the thread to update each plant.

This ensures that the plants' states (e.g., water level, sun exposure, maturity) are updated over time without blocking the main application thread.

## Design Rationale

The Singleton pattern was chosen because:
1. **Single Source of Truth**: One inventory prevents inconsistent plant data across the application.
2. **Resource Sharing**: It provides centralized management of expensive resources like flyweight factories.
3. **Global Access**: It simplifies access to system-wide resources without needing to pass them as parameters.
4. **Initialization Control**: It ensures that resources are created in the correct order and only once.
5. **Thread-Safe Updates**: It provides a centralized mechanism for updating the inventory in a thread-safe manner.

## Extension Points

**Adding New Shared Resources:**
1. Add a new member variable for the resource to the `Inventory` class in `singleton/Singleton.h`.
2. Initialize the resource in the `Inventory` constructor.
3. Provide a getter method to allow other parts of the system to access the resource.
