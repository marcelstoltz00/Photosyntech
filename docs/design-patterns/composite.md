# Composite Pattern

## Responsibility
Organizes plants into hierarchical tree structures where individual plants and groups of plants are treated uniformly, enabling operations to traverse and manipulate entire plant collections.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Component** | `PlantComponent` (abstract) | Declares the common interface for both individual plants (`Leaf`) and plant groups (`Composite`). It includes a `getType()` method to allow for efficient type checking without `dynamic_cast`. |
| **Leaf** | `LivingPlant` and subclasses<br>(Succulent, Shrub, Tree, Herb) | Represents individual plants with no children. Implements the `PlantComponent` interface for leaf-level behavior. |
| **Composite** | `PlantGroup` | Represents groups of plants. It stores child `PlantComponent` objects and implements the `PlantComponent` interface, typically by delegating to its children. |
| **Client** | Any code that interacts with the plant hierarchy | Works with `PlantComponent` objects through the common interface, without needing to distinguish between individual plants (`Leaf`) and groups of plants (`Composite`). Examples include the `NurseryFacade`, `Iterator` classes, and `Staff`. |

## Functional Requirements

### Primary Requirements
- **FR-7: Hierarchical Plant Organization** - Organizes plants into hierarchical structures where plants can be individual items or groups; handles plants and groups uniformly; enables traversal across all levels.

### Supporting Requirements
- **FR-9: Seasonal Plant Filtering** - Enables traversal through plant collections for filtering operations.
- **NFR-4: Scalability** - Hierarchical organization supports efficient management of large plant collections.
- **FR-17: Unified System Interface** - Provides a consistent interface for operations on both individual plants and groups.

## System Role & Integration

### Pattern Integration
The **Composite** pattern enables **hierarchical plant organization** through these key relationships:

- **Observer Pattern**: `PlantGroup` acts as a `Subject`, notifying registered `Observer`s (e.g., `Staff`) of significant events occurring within the group, such as a plant needing water or sunlight.
- **Iterator Pattern**: Iterators are used to traverse the `PlantComponent` structures, allowing for filtering by season or other criteria.
- **Singleton Pattern**: The root of the plant inventory is a `PlantGroup` that is managed as a `Singleton`.
- **Decorator Pattern**: Decorators can wrap `PlantComponent` objects, adding new functionality while preserving the common interface.
- **Prototype Pattern**: The `clone()` method on `PlantComponent` allows for the deep copying of the composite structure.
- **Facade Pattern**: The `NurseryFacade` provides a simplified interface for interacting with the plant hierarchy, hiding the complexity of the composite structure from the client, and operations on `PlantGroup` objects are managed through the facade.

### System Dependencies
- **Primary Structure**: Forms the core hierarchical inventory representation.
- **Notification Flow**: Changes within a `PlantGroup` can trigger notifications to `Observer`s.
- **Traversal Base**: The composite structure is the foundation for `Iterator`-based filtering and traversal.
- **Mass Operations**: Operations on a `PlantGroup` are applied uniformly to all its child components.

## Design Rationale

The Composite pattern was chosen because:
1. **Flexibility**: It allows clients to treat individual plants and groups of plants uniformly through a common interface.
2. **Hierarchy**: It enables the creation of complex, tree-like structures of plants.
3. **Scalability**: It provides an efficient way to represent and manage large collections of plants.
4. **Mass Operations**: It simplifies the application of operations to entire groups of plants.
5. **Observer Integration**: It allows for group-level notifications, which can be more efficient than observing every single plant.

## Extension Points

**Creating Plant Hierarchies:**
1. Use the `PlantComponent` interface for all plant and group operations.
2. Build the hierarchy by adding `PlantComponent` objects to a `PlantGroup` using the `addComponent()` method.
3. All operations (e.g., `water()`, `getInfo()`) will work uniformly on both individual plants and plant groups.
