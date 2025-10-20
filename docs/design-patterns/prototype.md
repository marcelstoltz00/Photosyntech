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

## System Role & Integration

### Pattern Integration
The **Prototype** pattern enables **efficient plant duplication** across the system through these interactions:

- **Builder Pattern**: Builder creates initial plant prototypes that are then cloned repeatedly
- **Composite Pattern**: Cloning works with PlantComponent hierarchy, deep-copying entire plant structures
- **Decorator Pattern**: Clone operation preserves all decorator layers, duplicating decorated plants with all customizations
- **Singleton Pattern**: Inventory system uses clone operations to populate stock from templates
- **Flyweight Pattern**: Cloned plants share references to flyweight-managed strategies and seasonal data
- **Facade Pattern**: Clone operations can be exposed through facade for convenient bulk duplication

### System Dependencies
- **Primary Use Case**: Mass-producing inventory plants from carefully constructed templates
- **Memory Efficiency**: Cloning is more efficient than re-executing full builder sequence
- **Data Consistency**: All plant attributes (decorations, strategies) copied together, maintaining integrity

## Design Rationale

The Prototype pattern was chosen because:
1. **Efficiency**: Cloning is faster than rebuilding complex plants through Builder
2. **Convenience**: Enables creation of plant variants by cloning and modifying base prototypes
3. **Attribute Preservation**: Deep cloning maintains all decorators, strategies, and states
4. **Scalability**: Supports rapid inventory expansion without repeated initialization overhead

## Extension Points

**Cloning New Plant Types:**
1. Each plant base type (Succulent, Shrub, Tree, Herb) implements `clone()` in `prototype/` directory
2. Custom decorators implement `clone()` to wrap the cloned component
3. Path: `prototype/NewPlantType.h` or `decorator/NewDecorator.h`
4. Ensure deep copying of all member pointers and complex attributes
