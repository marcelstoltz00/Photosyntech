# Iterator Pattern

## Responsibility
Provides sequential access to plant collections with filtering capabilities based on seasons or other criteria, without exposing the underlying collection structure. Handles nested composite hierarchies by recursively traversing PlantGroup structures to find matching LivingPlant instances.

## Participant Mapping

| Pattern Role          | Photosyntech Class(es)                                                                          | Responsibility                                                                                                                                    |
| --------------------- | ----------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Iterator**          | `Iterator` (abstract)                                                                           | Defines interface for traversing plant collections (`first()`, `next()`, `isDone()`, `currentItem()`); stores reference to aggregate              |
| **ConcreteIterator**  | `PlantIterator`<br>`SpringIterator`<br>`SummerIterator`<br>`AutumnIterator`<br>`WinterIterator` | Implement traversal algorithms with recursive composite support; cache current plant position; apply filtering logic via `findNextMatch()` helper |
| **Aggregate**         | `Aggregate` (abstract)                                                                          | Declares interface for creating iterator objects; stores plant collection pointer                                                                 |
| **ConcreteAggregate** | `AggPlant`<br>`AggSpring`<br>`AggSummer`<br>`AggAutumn`<br>`AggWinter`                          | Create appropriate iterator instances; seasonal aggregates store `targetSeason` for filtering                                                     |
| **Collection**        | `PlantGroup`<br>`list<PlantComponent*>`                                                         | The plant collections being traversed; composite structure handled recursively                                                                    |

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

## Design Rationale

The Iterator pattern was chosen because:
1. **Encapsulation**: Hide collection structure (internal `list<PlantComponent*>`)
2. **Filtering**: Enable flexible filtering without multiple accessor methods
3. **Extensibility**: Add new filtering criteria as new iterator types
4. **Scalability**: Efficient traversal without loading entire collection
5. **Consistency**: Uniform interface for all collection access patterns
6. **Decoupling**: Clients unaware of collection implementation details
7. **Composite Integration**: Seamlessly handles nested PlantGroup hierarchies through recursive traversal

## Implementation Details

### Core Mechanism

**Aggregate Construction:**
The base `Aggregate` class stores a pointer to the plant collection. Seasonal aggregates (like `AggSpring`) extend this by also storing a `targetSeason` string for filtering. See `iterator/Aggregate.cpp` and seasonal aggregate implementations for details.

**Iterator Interface:**
- `first()` - Positions iterator at first matching element
- `next()` - Advances to next matching element
- `isDone()` - Returns `true` when `currentPlant == nullptr`
- `currentItem()` - Returns cached `currentPlant` pointer

**Traversal Algorithm:**
All concrete iterators implement a private `findNextMatch()` helper method that iterates through the plant collection, uses `dynamic_cast<LivingPlant*>` to identify actual plants versus groups, applies filtering logic (seasonal iterators check `getSeason()` against `targetSeason`), and recursively descends into `PlantGroup` hierarchies to handle nested structures. The method returns the next matching plant or `nullptr` when iteration is complete. See `iterator/SpringIterator.cpp` for the canonical implementation pattern.

### Key Implementation Patterns

1. **Automatic Initialization**: Iterator constructors call `first()` automatically to position at the first matching element
2. **Position Caching**: `currentPlant` member variable stores the current position for efficient `currentItem()` access
3. **Dual-Mode Traversal**: `findFirst` boolean parameter enables a single method to handle both "find first" and "find next" logic
4. **Type Differentiation**: `dynamic_cast` distinguishes `LivingPlant` instances from `PlantGroup` containers
5. **Recursive Descent**: Handles arbitrary nesting depths in composite structures by recursively calling `findNextMatch()` on group contents

### Filtering Approaches

**PlantIterator:** Returns all `LivingPlant` instances without filtering (see `iterator/PlantIterator.cpp`)

**Seasonal Iterators:** Compare `plant->getSeason()` to `aggregate->targetSeason` and only return matching plants. All four seasonal iterators (Spring/Summer/Autumn/Winter) share this implementation pattern with different target seasons.

## Extension Points

To add new filtering iterators (e.g., by plant type or health status), create an iterator class inheriting from `Iterator` with a `findNextMatch()` method applying custom filtering logic, and a corresponding aggregate class inheriting from `Aggregate` that stores the filter criteria and creates the iterator. Follow the pattern established in `iterator/SpringIterator.h/cpp` and `iterator/AggSpring.h/cpp`.

## Usage Patterns

**Unfiltered Traversal:**
Create an `AggPlant` aggregate with the plant collection, then call `createIterator()` to get a `PlantIterator`. Use the standard iteration loop: `for (iter->first(); !iter->isDone(); iter->next())` to traverse all plants.

**Seasonal Filtering:**
Create a seasonal aggregate (e.g., `AggSpring`) with the collection and target season string, then create and use the iterator as above. Only plants matching the season will be returned.

**Composite Integration:**
Iterators automatically handle nested `PlantGroup` hierarchies through recursive traversal, transparently descending into groups to find matching plants at any depth.

## Implementation Files

### Core Interface Files
- [**`iterator/Iterator.h`**](../../iterator/Iterator.h) - Abstract iterator interface (first, next, isDone, currentItem)
- [**`iterator/Aggregate.h`**](../../iterator/Aggregate.h) / [**`.cpp`**](../../iterator/Aggregate.cpp) - Abstract aggregate interface and base implementation

### Concrete Iterator Files
| Iterator Type | Header | Implementation | Purpose |
|--------------|--------|----------------|---------|
| **PlantIterator** | [`iterator/PlantIterator.h`](../../iterator/PlantIterator.h) | [`iterator/PlantIterator.cpp`](../../iterator/PlantIterator.cpp) | Unfiltered traversal (all plants) |
| **SpringIterator** | [`iterator/SpringIterator.h`](../../iterator/SpringIterator.h) | [`iterator/SpringIterator.cpp`](../../iterator/SpringIterator.cpp) | Filter plants with Spring season |
| **SummerIterator** | [`iterator/SummerIterator.h`](../../iterator/SummerIterator.h) | [`iterator/SummerIterator.cpp`](../../iterator/SummerIterator.cpp) | Filter plants with Summer season |
| **AutumnIterator** | [`iterator/AutumnIterator.h`](../../iterator/AutumnIterator.h) | [`iterator/AutumnIterator.cpp`](../../iterator/AutumnIterator.cpp) | Filter plants with Autumn season |
| **WinterIterator** | [`iterator/WinterIterator.h`](../../iterator/WinterIterator.h) | [`iterator/WinterIterator.cpp`](../../iterator/WinterIterator.cpp) | Filter plants with Winter season |

### Concrete Aggregate Files
| Aggregate Type | Header | Implementation | Creates |
|---------------|--------|----------------|---------|
| **AggPlant** | [`iterator/AggPlant.h`](../../iterator/AggPlant.h) | [`iterator/AggPlant.cpp`](../../iterator/AggPlant.cpp) | PlantIterator |
| **AggSpring** | [`iterator/AggSpring.h`](../../iterator/AggSpring.h) | [`iterator/AggSpring.cpp`](../../iterator/AggSpring.cpp) | SpringIterator |
| **AggSummer** | [`iterator/AggSummer.h`](../../iterator/AggSummer.h) | [`iterator/AggSummer.cpp`](../../iterator/AggSummer.cpp) | SummerIterator |
| **AggAutumn** | [`iterator/AggAutumn.h`](../../iterator/AggAutumn.h) | [`iterator/AggAutumn.cpp`](../../iterator/AggAutumn.cpp) | AutumnIterator |
| **AggWinter** | [`iterator/AggWinter.h`](../../iterator/AggWinter.h) | [`iterator/AggWinter.cpp`](../../iterator/AggWinter.cpp) | WinterIterator |

### Dependencies
- **Composite**: [`composite/PlantComponent.h`](../../composite/PlantComponent.h), [`composite/PlantGroup.h`](../../composite/PlantGroup.h)
- **Prototype**: [`prototype/LivingPlant.h`](../../prototype/LivingPlant.h)
- **Decorator**: Seasonal decorators (Spring, Summer, Autumn, Winter)