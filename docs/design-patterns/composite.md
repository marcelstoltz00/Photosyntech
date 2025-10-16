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
