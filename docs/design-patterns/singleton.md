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
