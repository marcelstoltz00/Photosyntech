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
