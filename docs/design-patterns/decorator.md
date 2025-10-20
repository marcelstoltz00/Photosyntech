# Decorator Pattern

## Responsibility
Dynamically adds visual and functional attributes to plants (pots, charms, physical features, seasonal characteristics) without modifying the plant's core structure, allowing multiple decorations to be stacked.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Component** | `PlantComponent` (abstract) | Defines the interface for objects that can have responsibilities added to them |
| **ConcreteComponent** | `LivingPlant` and subclasses | The base plant objects being decorated |
| **Decorator** | `PlantAttributes` (abstract) | Maintains a reference to a PlantComponent and defines an interface conforming to Component |
| **ConcreteDecorator** | **Pots:** `RedPot`, `LargePot`<br>**Charms:** `PlantCharm`, `ShopThemedCharm`<br>**Features:** `SmallFlowers`, `LargeFlowers`, `SmallStem`, `LargeStem`, `SmallLeaf`, `LargeLeaf`<br>**Seasons:** `Summer`, `Winter`, `Autumn`, `Spring` | Add specific visual attributes and modify plant characteristics (sunlight/water needs, price) |

## Functional Requirements

### Primary Requirements
- **FR-11: Plant Decoration** - Allows plants to be customized with pots, charms, and embellishments; supports multiple customizations applied incrementally; maintains core plant functionality

### Supporting Requirements
- **NFR-2: Maintainability/Extensibility** - New decorations can be added without modifying existing plant classes
- **FR-1: Plant Species Creation and Configuration** - Decorators contribute to the final plant configuration
- **FR-9: Seasonal Plant Filtering** - Seasonal decorators enable season-based plant categorization

## System Role & Integration

### Pattern Integration
The **Decorator** pattern enables **dynamic plant customization** through these interactions:

- **Composite Pattern**: Decorators wrap `PlantComponent` interface, preserving hierarchical structure
- **Prototype Pattern**: Clone operations preserve decorator layers when copying plants
- **Builder Pattern**: After construction, plants are decorated to create final product
- **Iterator Pattern**: Seasonal decorators enable classification for iterator filtering (SpringIterator, etc.)
- **Flyweight Pattern**: Decorator instances are shared via flyweight factories where applicable
- **Observer Pattern**: Decorators may modify plant characteristics that affect observer notifications
- **Facade Pattern**: Facade provides convenience methods for applying multiple decorations

### System Dependencies
- **Customization Layer**: Applied after plant creation but before inventory management
- **Price Adjustment**: Pots and charms affect final plant pricing
- **Care Requirement Changes**: Seasonal and feature decorators modify water/sun needs
- **Visual Presentation**: Decorators contribute to plant display information

## Design Rationale

The Decorator pattern was chosen because:
1. **Flexibility**: Apply any combination of decorations without explosion of plant subclasses
2. **Runtime Application**: Decorations can be added/removed during plant lifecycle
3. **Separation of Concerns**: Decoration logic isolated from core plant behavior
4. **Extensibility**: New decoration types added without modifying existing plant or decorator code
5. **Reusability**: Decorators can be combined and reused across different plant types

## Extension Points

**Adding New Decorations:**
1. **Customer Decorators** (pots, charms): Create class inheriting from `PlantAttributes` in `decorator/customerDecorator/`
2. **Plant Feature Decorators**: Create class in `decorator/plantDecorator/` for physical features
3. **Seasonal Decorators**: Create season subclasses in `decorator/plantDecorator/` for seasonal characteristics
4. Each decorator implements `getPrice()`, `getInfo()`, and property modifiers
5. Example path: `decorator/customerDecorator/GoldenPot.h` or `decorator/plantDecorator/Thorny.h`
