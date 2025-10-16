# Flyweight Pattern

## Responsibility
Minimizes memory consumption by sharing immutable data objects (season names, water strategies, sun strategies) across multiple plant instances through a centralized factory cache.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Flyweight** | `Flyweight<T>` | Stores shared immutable data and provides access through `getState()` |
| **FlyweightFactory** | `FlyweightFactory<T, ID>` | Creates and manages flyweight objects using a cache; returns existing instances or creates new ones as needed |
| **Client** | `LivingPlant`<br>`Singleton` | Uses flyweights for shared data (seasons, strategies) instead of storing copies |
| **Shared Data** | `string` (season names)<br>`WaterStrategy`<br>`SunStrategy` | Immutable data objects that are shared across multiple plants |

## Functional Requirements

### Primary Requirements
- **FR-10: Shared Data Memory Optimization** - Minimizes memory usage by sharing immutable data objects across multiple plant instances; reduces memory footprint for large inventories; maintains performance while reducing consumption

### Supporting Requirements
- **NFR-4: Scalability** - Enables system to handle 5,000+ plant instances without memory exhaustion; memory footprint scales sub-linearly with number of plants
- **NFR-1: Performance** - Reduces memory allocation overhead, improving overall system performance
- **FR-6: Centralized Inventory** - Works with Singleton to manage shared resources efficiently
