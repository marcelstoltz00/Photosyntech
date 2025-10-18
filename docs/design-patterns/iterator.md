# Iterator Pattern

## Responsibility
Provides sequential access to plant collections with filtering capabilities based on seasons or other criteria, without exposing the underlying collection structure.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Iterator** | `Iterator` (abstract) | Defines interface for traversing plant collections (`first()`, `next()`, `isDone()`, `currentItem()`) |
| **ConcreteIterator** | `PlantIterator`<br>`SpringIterator`<br>`SummerIterator`<br>`AutumnIterator`<br>`WinterIterator` | Implement traversal algorithms; apply filtering logic based on criteria (e.g., season) |
| **Aggregate** | `Aggregate` (abstract) | Declares interface for creating iterator objects |
| **ConcreteAggregate** | `AggPlant`<br>`AggSpring`<br>`AggSummer`<br>`AggAutumn`<br>`AggWinter` | Create appropriate iterator instances for different filtering needs |
| **Collection** | `PlantGroup`<br>`list<PlantComponent*>` | The plant collections being traversed |

## Functional Requirements

### Primary Requirements
- **FR-9: Seasonal Plant Filtering** - Provides ability to traverse and filter plants based on assigned growing season; enables season-specific inventory views

### Supporting Requirements
- **NFR-3: Usability** - Simplifies browsing plants by category or season
- **FR-7: Hierarchical Plant Organization** - Iterators work with composite structures to traverse plant hierarchies
- **FR-17: Unified System Interface** - Provides consistent interface for accessing plant collections

## System Role & Integration

### Pattern Integration
The **Iterator** pattern enables **filtered plant collection traversal** through these interactions:

- **Composite Pattern**: Iterators traverse `PlantGroup` hierarchies without exposing structure
- **Decorator Pattern**: Seasonal decorators used to identify plants for seasonal iterators
- **Singleton Pattern**: Iterator factories obtain collection reference from singleton inventory
- **Flyweight Pattern**: Season names (iterable criteria) are shared flyweights
- **Observer Pattern**: Iterators used to find plants matching notification criteria
- **Facade Pattern**: Facade provides convenience iterator creation methods
- **Command Pattern**: Commands use iterators to find and operate on filtered plant sets

### System Dependencies
- **Season-Based Filtering**: SpringIterator, SummerIterator, AutumnIterator, WinterIterator
- **Collection Traversal**: Sequential access to plants without exposing internal list structure
- **Filtering Logic**: Encapsulated in concrete iterator implementations
- **Flexible Criteria**: Easily extend with new iterator types for different filtering needs

## Design Rationale

The Iterator pattern was chosen because:
1. **Encapsulation**: Hide collection structure (internal `list<PlantComponent*>`)
2. **Filtering**: Enable flexible filtering without multiple accessor methods
3. **Extensibility**: Add new filtering criteria as new iterator types
4. **Scalability**: Efficient traversal without loading entire collection
5. **Consistency**: Uniform interface for all collection access patterns
6. **Decoupling**: Clients unaware of collection implementation details

## Extension Points

**Adding New Filtering Iterators:**
1. Create iterator class implementing `Iterator` interface in `iterator/` directory
2. Create corresponding aggregate class implementing `Aggregate` interface
3. Implement filtering logic in `next()` and `isDone()` methods
4. Path: `iterator/NewFilterIterator.h` and `iterator/AggNewFilter.h`
5. Example: `iterator/RareIterator.h` to filter plants with special decorators
6. Register iterator factory in singleton or facade for convenient access
