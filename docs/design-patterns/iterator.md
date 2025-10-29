# Iterator Pattern

## Responsibility
Provides sequential access to plant collections with filtering capabilities based on seasons or other criteria, without exposing the underlying collection structure. Handles nested composite hierarchies by recursively traversing `PlantGroup` structures to find matching `LivingPlant` instances.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|---|---|---|
| **Iterator** | `Iterator` (abstract) | Defines the interface for traversing plant collections (`first()`, `next()`, `isDone()`, `currentItem()`). |
| **ConcreteIterator** | `PlantIterator`<br>`SeasonIterator` | Implements the traversal algorithm. `PlantIterator` provides unfiltered access, while `SeasonIterator` filters by season. Both handle composite structures. |
| **Aggregate** | `Aggregate` (abstract) | Declares the interface for creating iterator objects. |
| **ConcreteAggregate** | `AggPlant`<br>`AggSeason` | Implements the factory method to create a concrete iterator. `AggSeason` is configured with a specific season to filter by. |
| **Collection** | `PlantGroup`<br>`list<PlantComponent*>` | The plant collections being traversed. The composite structure is handled by the iterators. |

## Functional Requirements

### Primary Requirements
- **FR-9: Seasonal Plant Filtering** - Provides the ability to traverse and filter plants based on their assigned growing season, enabling season-specific inventory views.

### Supporting Requirements
- **NFR-3: Usability** - Simplifies browsing plants by category or season.
- **FR-7: Hierarchical Plant Organization** - Iterators work with composite structures to traverse plant hierarchies.
- **FR-17: Unified System Interface** - Provides a consistent interface for accessing plant collections.

## System Role & Integration

### Pattern Integration
The **Iterator** pattern enables **filtered plant collection traversal** through these interactions:

- **Composite Pattern**: Iterators traverse `PlantGroup` hierarchies without exposing the underlying structure.
- **Decorator Pattern**: The `SeasonIterator` uses seasonal decorators to identify plants for filtering.
- **Singleton Pattern**: Iterator factories obtain a reference to the plant collection from the `Singleton` inventory.
- **Flyweight Pattern**: The `AggSeason` aggregate uses a `Flyweight` for the season name to ensure efficient filtering.
- **Facade Pattern**: The `NurseryFacade` provides convenience methods for creating and using iterators, and browse operations use iterators to find and display filtered plant sets.

## Design Rationale

The Iterator pattern was chosen because:
1. **Encapsulation**: It hides the internal structure of the plant collection (a `list<PlantComponent*>`).
2. **Filtering**: It provides a flexible way to filter the collection without exposing the underlying data structure.
3. **Extensibility**: New filtering criteria can be added by creating new iterator and aggregate classes.
4. **Scalability**: The stack-based traversal is efficient and avoids deep recursion issues with large hierarchies.
5. **Consistency**: It provides a uniform interface for all collection access.
6. **Decoupling**: Clients are decoupled from the implementation details of the collection.
7. **Composite Integration**: It seamlessly handles nested `PlantGroup` hierarchies through an iterative, stack-based traversal.

## Implementation Details

### Core Mechanism

**Aggregate Construction:**
The base `Aggregate` class stores a pointer to the plant collection. The `AggSeason` concrete aggregate also stores a `targetSeason` flyweight for filtering.

**Iterator Interface:**
- `first()`: Positions the iterator at the first matching element.
- `next()`: Advances to the next matching element.
- `isDone()`: Returns `true` when there are no more elements.
- `currentItem()`: Returns the current `LivingPlant`.

**Traversal Algorithm:**
Both `PlantIterator` and `SeasonIterator` use a non-recursive, stack-based traversal algorithm to navigate the `PlantGroup` composite structure. This is implemented with a `std::stack<StackFrame>` where each `StackFrame` holds the state of iteration at one level of the hierarchy. This approach is more efficient and scalable than a recursive solution, as it avoids deep recursion and has an amortized O(1) complexity for `next()`.

To avoid expensive `dynamic_cast` operations, the iterators use the `getType()` method of the `PlantComponent` to differentiate between `LIVING_PLANT` and `PLANT_GROUP` components.

### Filtering Approaches

**`PlantIterator`:** Returns all `LivingPlant` instances without any filtering.

**`SeasonIterator`:** Compares the season of each plant (obtained via a decorator) to the `targetSeason` stored in the `AggSeason` aggregate. It only returns plants that match the target season.

## Extension Points

To add a new filtering iterator (e.g., by plant type or health status), you would create a new `Iterator` subclass with its own filtering logic and a corresponding `Aggregate` subclass to create it. This would follow the pattern established by `SeasonIterator` and `AggSeason`.

## Usage Patterns

**Unfiltered Traversal:**
Create an `AggPlant` aggregate with the plant collection, then call `createIterator()` to get a `PlantIterator`. Use the standard iteration loop: `for (iter->first(); !iter->isDone(); iter->next())` to traverse all plants.

**Seasonal Filtering:**
Create an `AggSeason` aggregate with the plant collection and the desired season string (e.g., "Spring"). The aggregate will create a `SeasonIterator` that will only return plants of that season.

## Implementation Files

### Core Interface Files
- [**`iterator/Iterator.h`**](../../iterator/Iterator.h) - Abstract iterator interface.
- [**`iterator/Aggregate.h`**](../../iterator/Aggregate.h) / [**`.cpp`**](../../iterator/Aggregate.cpp) - Abstract aggregate interface and base implementation.

### Concrete Iterator Files
| Iterator Type | Header | Implementation | Purpose |
|---|---|---|---|
| **`PlantIterator`** | [`iterator/PlantIterator.h`](../../iterator/PlantIterator.h) | [`iterator/PlantIterator.cpp`](../../iterator/PlantIterator.cpp) | Unfiltered traversal of all plants. |
| **`SeasonIterator`** | [`iterator/SeasonIterator.h`](../../iterator/SeasonIterator.h) | [`iterator/SeasonIterator.cpp`](../../iterator/SeasonIterator.cpp) | Filters plants by a specific season. |

### Concrete Aggregate Files
| Aggregate Type | Header | Implementation | Creates |
|---|---|---|---|
| **`AggPlant`** | [`iterator/AggPlant.h`](../../iterator/AggPlant.h) | [`iterator/AggPlant.cpp`](../../iterator/AggPlant.cpp) | `PlantIterator` |
| **`AggSeason`** | [`iterator/AggSeason.h`](../../iterator/AggSeason.h) | [`iterator/AggSeason.cpp`](../../iterator/AggSeason.cpp) | `SeasonIterator` |