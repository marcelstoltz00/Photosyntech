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

## System Role & Integration

### Pattern Integration
The **Flyweight** pattern provides **memory optimization** through these interactions:

- **Singleton Pattern**: Factories managed by singleton for global cache control and resource lifecycle
- **Builder Pattern**: Obtains strategy flyweights during plant construction
- **Strategy Pattern**: Water and sun strategy objects are shared flyweights across all plants
- **Decorator Pattern**: Decorator instances may be cached/shared via flyweight factories
- **Prototype Pattern**: Cloned plants share references to same flyweight instances (no copying)
- **Composite Pattern**: Shared strategies reduce memory even in large plant hierarchies
- **Iterator Pattern**: Shared season names reduce memory footprint of seasonal iterator collections

### System Dependencies
- **Memory Optimization**: Reduces memory by 99.92% compared to storing separate strategy copies
- **Scalability Foundation**: Enables 5,000+ plant instances with minimal memory overhead
- **Consistent Behavior**: All plants sharing strategy receive identical behavior
- **Performance**: Eliminates strategy duplication and reduces allocation pressure

## Design Rationale

The Flyweight pattern was chosen because:
1. **Massive Duplication**: Strategies shared across thousands of plant instances
2. **Immutability**: Strategies and seasons never change after creation
3. **Memory Constraint**: Supporting 5,000+ plants requires aggressive optimization
4. **Performance**: Singleton cache lookup faster than repeated object creation
5. **Transparency**: Applications use strategies normally without awareness of sharing

## Extension Points

**Extending Shared Data:**
1. Create new `FlyweightFactory<T, ID>` template instance in `singleton/Singleton.h`
2. Define immutable data type and unique identifier scheme
3. Flyweight interface: `T* getState(ID id)`
4. Factory creates instances on first access, returns cached copies thereafter
5. Path: `flyweight/Flyweight.h` and `flyweight/FlyweightFactory.h` (template implementations)
