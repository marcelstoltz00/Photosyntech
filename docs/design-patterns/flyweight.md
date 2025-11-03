# Flyweight Pattern

## Responsibility
Minimizes memory consumption by sharing immutable data objects (season names, water strategies, sun strategies) across multiple plant instances through a centralized factory cache.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Flyweight** | `Flyweight<T>` | Stores shared immutable data and provides access through `getState()` |
| **FlyweightFactory** | `FlyweightFactory<T, ID>` | Creates and manages flyweight objects using a cache; returns existing instances or creates new ones as needed |
| **Client** | `LivingPlant`<br>`Singleton` | Uses flyweights for shared data (seasons, strategies) instead of storing copies |
| **Shared Data** | `string` (season names)<br>`WaterStrategy`<br>`SunStrategy` | Immutable data objects that are shared across multiple plants |

## Functional Requirements

### Primary Requirements
- **FR-10: Shared Data Memory Optimization** - Minimizes memory usage by sharing immutable data objects across multiple plant instances; reduces memory footprint for large inventories; maintains performance while reducing consumption

### Supporting Requirements

- **NFR-4: Scalability** - Enables system to handle 10 000 000+ plant instances of the same plant with much less overhead
- **NFR-1: Performance** - Reduces memory allocation overhead, improving overall system performance
- **FR-6: Centralized Inventory** - Works with Singleton to manage shared resources efficiently
## System Role & Integration

### Pattern Integration
The **Flyweight** pattern provides **memory optimization** through these interactions:

- **Singleton Pattern**: Factories managed by singleton for global cache control and resource lifecycle
- **Builder Pattern**: Obtains strategy flyweights during plant construction
- **Strategy Pattern**: Water and sun strategy objects are shared flyweights across all plants
- **Decorator Pattern**: Decorator instances may be cached/shared via flyweight factories
- **Prototype Pattern**: Cloned plants share references to same flyweight instances (no copying)
- **Composite Pattern**: Shared strategies reduce memory even in large plant hierarchies
- **Iterator Pattern**: Shared season names reduce memory footprint of seasonal iterator collections

### System Dependencies
- **Memory Optimization**: Reduces memory by 75% compared to storing separate strategy copies
- **Scalability Foundation**: Enables 10 000 000+ plant instances with relatively minimal memory overhead
- **Consistent Behavior**: All plants sharing strategy receive identical behavior
- **Performance**: Eliminates strategy duplication and reduces allocation pressure

## Design Rationale

The Flyweight pattern was chosen because:
1. **Massive Duplication**: Strategies shared across thousands of plant instances
2. **Immutability**: Strategies and seasons never change after creation
3. **Memory Constraint**: Supporting 10 000 000+ plants requires aggressive optimization
4. **Performance**: Singleton cache lookup faster than repeated object creation
5. **Transparency**: Applications use strategies normally without awareness of sharing

## Extension Points

**Extending Shared Data:**
1. Create new `FlyweightFactory<T, ID>` template instance in `singleton/Singleton.h`
2. Define immutable data type and unique identifier scheme
3. Flyweight interface: `T* getState(ID id)`
4. Factory creates instances on first access, returns cached copies thereafter
5. Path: `flyweight/Flyweight.h` and `flyweight/FlyweightFactory.h` (template implementations)



## Math
- String memory optimization.

- Assumptions 
	- Assume a Living plant object has 
		- 5 attributes 
			- each storing a name
		- 1 name attribute
			- storing a name
		- Each of these names can be stored in either a flyweight or a string itself. However the data remains identical in both ways.
- Sizes 
	- Strings are 32 Bytes 
		- Based off of size_of() in c++
	- Object pointers are 8 bytes 
		- Based off of size_of() in c++
### Proof 
- Internally stored strings 
Assume a living plant is made to the above assumptions, where there is a plant that stores all its strings internally without the use of flyweight, as strings are 32 bytes this would be 6 x 32 pointers accumulating in 192 bytes per plant. Let this plant be **X**

- Externally stored strings in flyweight 
Assume a living plant is made to the above assumptions, where there is a plant that stores all its strings externally with the use of flyweights, as strings are 32 bytes this would be 6 x 32 pointers accumulating in 192 bytes stored in 6 flyweights as well as 6 x 8 pointers to those flyweights in each attribute accumulating to 48 bytes and in total 240. let the plant itself with 48 bytes of pointers be called **Y** and let the group of flyweights be called **F**

- In a one to one comparison 
**X** has 48 less bytes than **Y + F**

- To scale however 

#### 2 of X and Y 
- `2X = 2(192) =  384 Bytes`
- `2Y + F =2(48) + 192 = 288 Bytes`
- Saving = 96 Bytes
#### 1000 of X and Y 
- `1000X = 1000(192) = 192 000 Bytes`
- `1000(Y) + F = 1000(48) + 192 = 48 192 Bytes`
- Saving = 143 808 Bytes = 143 KB
#### 1 000 000 of X and Y 
- `1 000 000X = 1 000 000(192) = 192 000 000 Bytes`
- `1 000 000(Y) + F = 1 000 000(48) + 192 = 48 000 000 192 Bytes`
- Saving = 143 999 808 = 143 .9 MB
#### 100 000 000 of X and Y 
- `100 000 000X = 100 000 000(192) = 19 200 000 000 Bytes`
- `100 000 000(Y) + F = 100 000 000(48) + 192 = 4 800 192 Bytes`
- Saving = 14 399 999 808 = 14.4 GB
- Which is the extent of our stress testing. 
#### Efficiency calculation 
- (4 800 000 192 Bytes  / 19 200 000 000 Bytes) x 100  = 25% 
- Thus 75% less memory is used.

