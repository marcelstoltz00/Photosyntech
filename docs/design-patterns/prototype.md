# Prototype Pattern

## Responsibility

Enables creation of new plant instances by cloning existing configured plants, preserving all attributes including strategies, states, and decorators without coupling to concrete classes. Supports efficient mass production of identical plants for inventory distribution.

## Participant Mapping

|Pattern Role|Photosyntech Class(es)|Responsibility|
|---|---|---|
|Prototype|`PlantComponent`|Declares clone() interface for all plant components, defining the contract for creating copies of plant objects|
|ConcretePrototype|`LivingPlant` `Herb` `Shrub` `Succulent` `Tree`|Implements clone() method to create deep copies of plant instances with member-wise shallow copy for flyweights and independent decorator chains|
|Client|`Inventory` `Builder` `Customer`|Uses clone() to create new plant instances without knowing concrete classes, requesting copies from configured plants for mass production|

## Functional Requirements

**Primary Requirements**

- **FR-2: Plant Type Cloning** - Enables creation of new plant instances by copying existing plant types with all attributes, decorations, strategies, and states preserved; multiple identical copies can be created from a single configured plant

**Supporting Requirements**

- **NFR-4: Scalability/Memory Efficiency** - Supports efficient cloning while maintaining shallow copies of shared flyweight objects (strategies, seasons) for memory efficiency when handling up to 5,000 plant instances
- **FR-3: Plant Lifecycle Management** - Cloned plants preserve maturity state references, enabling proper lifecycle management across all copies while sharing immutable state objects
- **NFR-2: Maintainability/Extensibility** - Adding new plant species requires only creating a new concrete prototype class inheriting from LivingPlant (≤2 file modification requirement)

## System Role & Integration

### Pattern Integration

The Prototype pattern serves as the inventory multiplication mechanism in Photosyntech, enabling efficient plant replication through these key interactions:

- **Builder Pattern**: Builder creates the initial configured plant prototype that serves as the template for cloning operations
- **Flyweight Pattern**: Prototype performs shallow copy of shared immutable objects (name, season, waterStrategy, sunStrategy, maturityState) to maintain memory efficiency across clones
- **Decorator Pattern**: Clone operation preserves decorator chain structure, requiring separate deep copy of decorators to ensure independence between cloned plants
- **Composite Pattern**: Cloned plants can be added to PlantGroup hierarchies, enabling bulk operations on identical plant collections
- **Strategy Pattern**: Cloned plants share strategy flyweight references, ensuring consistent behavior across all copies without memory duplication
- **State Pattern**: Cloned plants reference the same maturity state flyweights, enabling synchronized lifecycle transitions across plant batches
- **Singleton Pattern**: Inventory singleton manages cloned plant instances, coordinating distribution and tracking

### System Dependencies

- **Primary Consumer**: Inventory system uses clone() for mass production when fulfilling large customer orders
- **Integration Point**: Builder creates initial prototypes; clone() replicates them for distribution
- **Data Flow**: Builder → Prototype creation → clone() invocation → Inventory addition → Customer distribution

## Design Rationale

The Prototype pattern was chosen for plant replication because:

1. **Performance**: Cloning configured plants is significantly faster than rebuilding through Builder pattern repeatedly, especially for complex decorator chains
2. **Memory Efficiency**: Shallow copy of flyweight objects (strategies, states, seasons) ensures minimal memory overhead while creating thousands of plant instances
3. **Separation of Concerns**: Cloning logic isolated in concrete prototypes, allowing independent evolution of plant types and cloning behavior
4. **Configuration Preservation**: Enables exact replication of fully configured plants including all strategies, states, and decorations without reconstruction
5. **Scalability**: Supports NFR-4 requirement for 5,000+ plant instances through efficient flyweight sharing and targeted deep copying

## Implementation Details

### Key Methods

**`clone()`** - Creates a copy of the plant instance; each concrete prototype overrides this to return a new instance of its specific type using the copy constructor

**`PlantComponent(const PlantComponent& other)`** - Base copy constructor that copies price, affectWaterValue, and affectSunValue attributes

**`LivingPlant(const LivingPlant& other)`** - Copy constructor performing member-wise shallow copy of flyweight pointers (name, season, strategies, states); sets decorator to nullptr for independent decorator management

**`Herb(const Herb& other), Shrub(const Shrub& other), Succulent(const Succulent& other), Tree(const Tree& other)`** - Concrete copy constructors delegating to LivingPlant, preserving all parent attributes for specific plant types

### Implementation Challenges

**Shallow vs Deep Copy**: Determined which attributes required shallow copy (flyweights) versus deep copy (decorators). Resolved by implementing shallow copy for all shared immutable objects in copy constructor, leaving decorator as nullptr for separate deep copy management.

**Decorator Chain Independence**: Ensuring cloned plants have independent decorator chains while preserving structure. Resolved by setting decorator to nullptr in LivingPlant copy constructor, allowing client to manage decorator deep copying through `correctShape()`.

**Type-Specific Cloning**: Each concrete prototype returns correct type without code duplication. Resolved by having each concrete class override clone() to call its own copy constructor, delegating shared logic to LivingPlant.

### Usage Example

```cpp
// Create and configure a prototype plant
Herb* prototypeHerb = new Herb();
prototypeHerb->setWaterStrategy(MODERATE_WATER);
prototypeHerb->setSunStrategy(MODERATE_SUN);
prototypeHerb->setMaturity(SEEDLING);
prototypeHerb->setSeason(Inventory::getInstance()->getString("Spring"));

// Add decorative pot
PlantAttributes* pot = new DecorativePot();
prototypeHerb->addAttribute(pot);

// Clone for inventory - creates 100 identical herbs
std::vector<PlantComponent*> inventory;
for (int i = 0; i < 100; i++) {
    PlantComponent* clone = prototypeHerb->clone();
    
    // Deep copy decorator chain independently
    if (prototypeHerb->getDecorator() != nullptr) {
        PlantComponent* decoratorCopy = prototypeHerb->getDecorator()->clone();
        clone->correctShape(decoratorCopy);
    }
    
    inventory.push_back(clone);
}

// All clones share flyweight strategies/states but have independent decorators
// Memory efficient: strategies and seasons reused across all 100 instances
```

### Flow Example

**Scenario**: Customer orders 50 identical Rose plants for an event

1. Staff creates a Rose plant using Builder, configuring it with decorative pot, watering strategy, and maturity state
2. Customer places order for 50 identical Rose plants through NurseryFacade
3. Inventory calls `clone()` on the configured Rose instance: `PlantComponent* copy = rosePrototype->clone();`
4. `clone()` invokes Herb copy constructor (Rose is an Herb type): `return new Herb(*this);`
5. Herb copy constructor delegates to LivingPlant copy constructor, performing shallow copy of flyweights
6. LivingPlant copy constructor preserves name, season, waterStrategy, sunStrategy, maturityState pointers; sets decorator to nullptr
7. Client code deep copies decorator chain through `correctShape()` for independent customization
8. New cloned plant added to inventory with all strategies and states preserved
9. Process repeats 49 more times to fulfill order efficiently without rebuilding configuration
