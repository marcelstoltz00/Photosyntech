# Singleton Pattern

## Responsibility
Ensures a single, globally accessible instance of the inventory and flyweight factories exists, providing centralized access to shared plant data and preventing inconsistent state across the system.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Singleton** | `Singleton` | Ensures only one instance exists; provides global access point through `getInstance()`; manages inventory and flyweight factories |
| **Managed Resources** | `PlantGroup* _inventory`<br>`FlyweightFactory<string, string>* _string`<br>`FlyweightFactory<int, WaterStrategy>* _waterStrategies`<br>`FlyweightFactory<int, SunStrategy>* _sunStrategies` | Centralized resources managed by the Singleton instance |

## Functional Requirements

### Primary Requirements
- **FR-6: Centralized Inventory** - Maintains a single, shared inventory accessible to both customers and staff to ensure consistency; ensures no duplicate or conflicting inventory records
- **FR-10: Shared Data Memory Optimization** - Manages flyweight factories that minimize memory usage by sharing immutable data objects across multiple plant instances

### Supporting Requirements
- **NFR-4: Scalability** - Central management of shared objects reduces memory footprint for large inventories
- **NFR-5: Reliability** - Single source of truth prevents data inconsistencies
- **FR-17: Unified System Interface** - Provides centralized access point for system-wide resources

## System Role & Integration

### Pattern Integration
The **Singleton** pattern serves as the **central resource hub** of Photosyntech, managing these critical interactions:

- **Flyweight Pattern**: Manages three flyweight factories for water strategies, sun strategies, and season names
- **Composite Pattern**: Owns and manages the root `PlantGroup` representing the centralized inventory
- **Builder Pattern**: Director accesses singleton to obtain strategy instances during plant construction
- **Facade Pattern**: NurseryFacade accesses singleton for inventory operations and resource management
- **Command Pattern**: Commands modify inventory state through singleton's managed plant group
- **Observer Pattern**: Plant group (managed by singleton) acts as subject for staff notifications
- **Iterator Pattern**: Iterator factories obtain collection reference from singleton inventory

### System Dependencies
- **Global Access Point**: All subsystems access singleton instance for shared resources
- **Resource Consistency**: Prevents multiple inventory instances or duplicate strategy caches
- **System Initialization**: Singleton must be initialized before other patterns can be used
- **Lifecycle Management**: Manages lifetime of flyweight factories and central inventory

## Design Rationale

The Singleton pattern was chosen because:
1. **Single Source of Truth**: One inventory prevents inconsistent plant data across application
2. **Resource Sharing**: Centralized management of expensive resources (flyweight factories)
3. **Global Access**: Simplifies access to system-wide resources without parameter passing
4. **Initialization Control**: Ensures resources are created in correct order and only once

## Extension Points

**Adding New Shared Resources:**
1. Add new flyweight factory member to `Singleton` class in `singleton/Singleton.h`
2. Initialize factory in singleton constructor
3. Provide getter method following existing pattern
4. Example: Adding shared immutable data for new plant attributes
