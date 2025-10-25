# Composite Pattern

## Responsibility

Composes plant objects into tree structures to represent part-whole hierarchies, allowing clients to treat individual plants and groups of plants uniformly through a common interface. Enables hierarchical organization of inventory with operations that traverse and manipulate entire collections transparently.

## Participant Mapping

|Pattern Role|Photosyntech Class(es)|Responsibility|
|---|---|---|
|Component|`PlantComponent`|Declares common interface for both individual plants and plant groups; defines operations like water(), getInfo(), getPrice(), and clone() that work uniformly on leaves and composites|
|Leaf|`LivingPlant` `Herb` `Shrub` `Succulent` `Tree`|Represents individual plant objects with no children; implements component operations for single plants; forms the leaf nodes of the plant hierarchy|
|Composite|`PlantGroup`|Manages collection of PlantComponent children (both leaves and other composites); implements component operations by delegating to all children; provides methods to add/remove components|
|Client|`Inventory` `Iterator` `Customer` `Staff`|Works with plant hierarchies through PlantComponent interface without distinguishing between individual plants and groups; performs operations uniformly across entire structures|

## Functional Requirements

**Primary Requirements**

- **FR-7: Hierarchical Plant Organization** - Organizes plants into hierarchical structures where plants can be individual items or groups; individual plants and groups handled uniformly; operations traverse entire structure; total counts calculated across all levels

**Supporting Requirements**

- **FR-6: Centralized Inventory** - PlantGroup serves as root composite in singleton inventory, containing all plants and nested groups in unified hierarchy
- **FR-9: Seasonal Plant Filtering** - Composite structure enables traversal and filtering of plants by season through nested groups
- **FR-11: Plant Decoration** - Decorator pattern wraps both leaves and composites uniformly, with PlantGroup delegating decorator operations to all children
- **NFR-1: Performance** - Composite structure enables batch operations on thousands of plants by delegating through hierarchy efficiently
- **NFR-5: Reliability** - Modular composite design ensures changes to individual plant classes don't affect group management logic

## System Role & Integration

### Pattern Integration

The Composite pattern serves as the structural foundation for plant organization in Photosyntech, enabling hierarchical management through these key interactions:

- **Iterator Pattern**: Iterators traverse composite hierarchies using stack-based algorithm, accessing nested PlantGroups through getPlants() to enable depth-first traversal of entire plant tree
- **Observer Pattern**: PlantGroup acts as Subject, notifying observers when any plant in the composite hierarchy needs care; operations propagate down to all leaf nodes
- **Decorator Pattern**: PlantGroup.addAttribute() clones decorators and applies them to all children uniformly, maintaining composite transparency
- **Prototype Pattern**: PlantGroup.clone() recursively clones entire hierarchy, creating deep copies of all contained plants and nested groups
- **Singleton Pattern**: Inventory singleton maintains root PlantGroup containing all plant collections organized hierarchically
- **Strategy Pattern**: water() and setOutside() operations delegate through composite, applying strategies to all leaf plants in hierarchy
- **State Pattern**: update() propagates state changes through composite, triggering maturity transitions for all contained plants
- **Facade Pattern**: NurseryFacade delegates operations to root PlantGroup, which recursively applies them throughout hierarchy

### System Dependencies

- **Primary Consumer**: Inventory system uses PlantGroup as root container for organizing all plants into seasonal and categorical groups
- **Integration Point**: PlantComponent interface enables uniform treatment; PlantGroup delegates all operations to children recursively
- **Data Flow**: Client → PlantGroup operation → Recursive delegation to all children → Leaf execution

## Design Rationale

The Composite pattern was chosen for plant organization because:

1. **Uniform Treatment**: Clients interact with individual plants and plant groups through identical PlantComponent interface, eliminating need for type checking
2. **Hierarchical Organization**: Enables natural representation of inventory structure (seasonal groups, categorical groups, individual plants) as tree hierarchy
3. **Scalable Operations**: Batch operations (water all, get total price, update all) automatically propagate through hierarchy without explicit iteration logic
4. **Flexible Grouping**: Plants can be dynamically organized into arbitrary nested structures (Spring plants → Herbs → Individual roses)
5. **Transparent Decoration**: Decorators can be applied to entire groups uniformly, with PlantGroup cloning decorators for each child
6. **Recursive Traversal**: Iterator pattern leverages composite structure for efficient depth-first traversal of thousands of plants

## Implementation Details

### Key Methods

**`PlantGroup()`** - Constructs empty plant group with zero attributes, ready to contain plant components

**`PlantGroup(const PlantGroup& other)`** - Deep copy constructor that recursively clones all contained plants and nested groups by calling clone() on each child

**`addComponent(PlantComponent* component)`** - Adds plant or nested group to this composite's children list

**`getPlants()`** - Returns pointer to internal plants list, enabling iterators to recursively traverse hierarchy without friend access

**`water()` / `setOutside()` / `update()`** - Composite operations that delegate to all children, applying strategies and state changes throughout hierarchy

**`getPrice()` / `affectWater()` / `affectSunlight()`** - Aggregation operations that accumulate values from all children recursively

**`getInfo()`** - Recursive information gathering that formats details of all contained plants with visual separators

**`addAttribute(PlantComponent* attribute)`** - Clones decorator for each child and applies uniformly, maintaining transparency

**`clone()`** - Creates deep copy of entire group hierarchy by invoking copy constructor

**`getType()`** - Returns ComponentType::PLANT_GROUP for efficient type identification without dynamic_cast

### Implementation Challenges

**Memory Management**: Ensuring proper cleanup of nested hierarchy without double-deletion. Resolved by having PlantGroup destructor delete all children, checking for decorators first to delete outermost wrapper.

**Recursive Cloning**: Deep copying entire hierarchies with decorators. Resolved by copy constructor calling clone() on each child component, which recursively clones nested groups and their contents.

**Observer Integration**: Propagating notifications through composite to all leaf plants. Resolved by PlantGroup implementing Subject interface and delegating observer notifications to all children with dynamic_cast to LivingPlant.

**Decorator Application**: Applying decorators uniformly across group. Resolved by cloning attribute for each child to ensure independent decorator instances while maintaining uniform application.

### Usage Example

```cpp
// Create seasonal plant groups in inventory
PlantGroup* springPlants = new PlantGroup();
PlantGroup* herbGroup = new PlantGroup();

// Add individual herbs to herb group
Herb* rose = new Herb();
rose->setWaterStrategy(MODERATE_WATER);
herbGroup->addComponent(rose);

Herb* lavender = new Herb();
lavender->setWaterStrategy(LOW_WATER);
herbGroup->addComponent(lavender);

// Add herb group to spring plants
springPlants->addComponent(herbGroup);

// Add individual tree to spring plants
Tree* cherry = new Tree();
cherry->setWaterStrategy(HIGH_WATER);
springPlants->addComponent(cherry);

// Operations work uniformly on entire hierarchy
springPlants->water();  // Waters all herbs and cherry tree
double totalPrice = springPlants->getPrice();  // Sums all plant prices
std::string info = springPlants->getInfo();  // Gets details of all plants

// Add decorators to entire group
PlantAttributes* springPot = new SeasonalPot("Spring");
springPlants->addAttribute(springPot);  // Clones pot for each plant

// Clone entire seasonal collection
PlantComponent* springCopy = springPlants->clone();  // Deep copies all plants
```

### Flow Example

**Scenario**: Staff waters all spring plants through inventory system

1. Inventory singleton contains root PlantGroup with nested seasonal groups (Spring, Summer, Autumn, Winter)
2. Staff selects "Water Spring Plants" action through NurseryFacade
3. Facade calls `springGroup->water()` on Spring PlantGroup composite
4. PlantGroup iterates through its children list: `[HerbGroup, TreeGroup, ShrubGroup]`
5. For each child, calls `component->water()` delegation
6. HerbGroup (also PlantGroup) receives water() call and recursively delegates to its children: `[Rose, Lavender, Basil]`
7. Each Herb (leaf) executes its WaterStrategy, updating waterLevel attribute
8. TreeGroup and ShrubGroup similarly delegate to their leaf plants
9. Observer notifications propagate: PlantGroup calls `waterNeeded()` which notifies all attached staff observers
10. Staff observers receive updates for each leaf plant via `getWaterUpdate(LivingPlant*)`
11. Entire spring inventory watered through single composite operation, demonstrating transparent hierarchical management
