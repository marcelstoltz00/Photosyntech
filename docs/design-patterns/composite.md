# Composite Pattern

## Responsibility
Organizes plants into hierarchical tree structures where individual plants and groups of plants are treated uniformly, enabling operations to traverse and manipulate entire plant collections.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Component** | `PlantComponent` (abstract) | Declares common interface for both individual plants and plant groups |
| **Leaf** | `LivingPlant` and subclasses<br>(Succulent, Shrub, Tree, Herb) | Represents individual plants with no children; implements leaf behavior |
| **Composite** | `PlantGroup` | Represents groups of plants; stores child components and implements operations for adding/removing children |
| **Client** | `Singleton` (inventory)<br>`Iterator` classes<br>`Staff` | Works with components through the common interface without distinguishing between leaves and composites |

## Functional Requirements

### Primary Requirements
- **FR-7: Hierarchical Plant Organization** - Organizes plants into hierarchical structures where plants can be individual items or groups; handles plants and groups uniformly; enables traversal across all levels

### Supporting Requirements
- **FR-9: Seasonal Plant Filtering** - Enables traversal through plant collections for filtering operations
- **NFR-4: Scalability** - Hierarchical organization supports efficient management of large plant collections
- **FR-17: Unified System Interface** - Provides consistent interface for operations on both individual plants and groups

## System Role & Integration

### Pattern Integration
The **Composite** pattern enables **hierarchical plant organization** through these key relationships:

- **Observer Pattern**: `PlantGroup` implements `Subject` interface to notify staff of group-level changes
- **Iterator Pattern**: Iterators traverse composite plant structures to filter by season or criteria
- **Singleton Pattern**: Root inventory is a `PlantGroup` managed by singleton
- **Decorator Pattern**: Decorators wrap plant components, preserving composite structure
- **Prototype Pattern**: Clone operations work with composite hierarchy for group duplication
- **Command Pattern**: Commands operate on plant groups, affecting all children uniformly
- **Facade Pattern**: Facade provides high-level group operations through composite interface

### System Dependencies
- **Primary Structure**: Forms the core hierarchical inventory representation
- **Notification Flow**: Plant group changes trigger observer notifications to staff
- **Traversal Base**: Enables iterator-based filtering across plant hierarchies
- **Mass Operations**: Group operations apply uniformly to all child components

## Design Rationale

The Composite pattern was chosen because:
1. **Flexibility**: Treats individual plants and groups uniformly through common interface
2. **Hierarchy**: Enables arbitrary nesting of plant collections (room → shelf → pot groups)
3. **Scalability**: Efficient representation of large collections without flat array limitations
4. **Mass Operations**: Single operation on group affects all children uniformly
5. **Observer Integration**: Group-level notifications reduce observer notification overhead

## Extension Points

**Creating Plant Hierarchies:**
1. Use `PlantComponent` interface for all plant and group operations
2. Build hierarchy by adding components to `PlantGroup` via internal list management
3. All operations (water, getInfo, etc.) work uniformly on leaves and composites
4. Path: Hierarchy built dynamically using existing `CompositePattern` classes in `composite/` directory
