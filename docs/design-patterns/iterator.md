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
