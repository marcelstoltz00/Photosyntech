# Prototype Pattern

## Responsibility
Enables creation of new plant instances by cloning existing plants, preserving all attributes including base type, decorations, strategies, and states without repeating the complex initialization process.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Prototype** | `PlantComponent` (abstract) | Declares the clone interface for all plant objects |
| **ConcretePrototype** | `Succulent`<br>`Shrub`<br>`Tree`<br>`Herb`<br>Decorator classes (e.g., `SmallFlowers`, `LargeLeaf`) | Implement the clone operation to create copies of themselves with all current attributes |
| **Client** | `Builder` classes<br>`Inventory` system | Uses the clone operation to create new plant instances from prototypes |

## Functional Requirements

### Primary Requirements
- **FR-2: Plant Type Cloning** - Allows new plant instances to be created by copying existing plant types and decorations; maintains all properties including strategies and states

### Supporting Requirements
- **NFR-1: Performance** - Cloning is more efficient than building plants from scratch for mass production
- **NFR-4: Scalability** - Enables rapid creation of multiple plant instances without repeated initialization overhead
