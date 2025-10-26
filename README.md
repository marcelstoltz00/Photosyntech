<p align="center">
  <br>
  <h1 align="center">PhotoSyntech</h1>
  <h3 align="center">A C++ Plant Management System Demonstrating Design Patterns</h3>
</p>

<div align="center">

![Unit Tests](https://github.com/marcelstoltz00/Photosyntech/actions/workflows/cpp-tests.yml/badge.svg)
![Code Coverage](https://img.shields.io/badge/coverage-dynamic-brightgreen)

![GitHub issues](https://img.shields.io/github/issues/marcelstoltz00/Photosyntech)
![GitHub pull requests](https://img.shields.io/github/issues-pr/marcelstoltz00/Photosyntech)
![GitHub last commit](https://img.shields.io/github/last-commit/marcelstoltz00/Photosyntech)
![GitHub repo size](https://img.shields.io/github/repo-size/marcelstoltz00/Photosyntech)

</div>

<h3 align="center">
PhotoSyntech is a C++ plant management system demonstrating multiple design patterns, including growth and care simulation for various plant types.
</h3>

<p align="center">
[Project Website](https://github.com/marcelstoltz00/Photosyntech) |
[Full Documentation](https://github.com/marcelstoltz00/Photosyntech) |
[View Design Patterns](https://github.com/marcelstoltz00/Photosyntech/tree/main/docs/design-patterns)
</p>

<h1 align="center">🪴 Features 🪴</h1>

- 🌱 **Plant Management:** Track and manage a virtual collection of plants.
- ☀️ **Growth Simulation:** Watch your plants grow, change, and react based on care routines.
- 🎨 **Design Pattern Showcase:** A practical C++ demonstration of multiple GoF design patterns:
  -   Builder & Prototype
  -   Iterator & Composite
  -   Observer & Mediator
  -   Strategy
  -   Decorator
  -   State
  -   Command
  -   Singleton
  -   ...and more!

<h1 align="center">🏛️ Design Patterns In-Depth 🏛️</h1>

This document maps functional requirements to their corresponding design patterns and implementation locations.

## 2.1 Creational Patterns

### Builder (Plant Species Creation)
**Pattern Documentation:** [builder.md](docs/design-patterns/builder.md)

**Functional Requirements (FR-1):**
- The system will provide builder classes that create plant species (e.g., Rose, Sunflower) as combinations of base plant types with decorative attributes, water strategy, sun strategy and maturity state.
- Director will be used to coordinate the construction of complex plant species through ConcreteBuilders (e.g., Rose = Shrub + thorns + flowers + summer + large flowers), ensuring all required attributes are initialized.
- Enables creation of complex compositions where a species combines a base type with multiple decorations.

**Implementation:** See [builder.md](docs/design-patterns/builder.md) for file structure and implementation details.

---

### Prototype (Plant Type Cloning)
**Pattern Documentation:** [prototype.md](docs/design-patterns/prototype.md)

**Functional Requirements (FR-2):**
- Cloning will allow new instances of plant types (Succulent, Shrub, Tree, Herb) to be created with copied attributes through the clone() method.
- Will be used to recreate very specific versions of plants multiple times, preserving both the base plant type and any applied decorations.
- Base types serve as prototypes that can be cloned and then decorated to create plant species.

**Implementation:** See [prototype.md](docs/design-patterns/prototype.md) for file structure and implementation details.

---

### Singleton (Inventory)
**Pattern Documentation:** [singleton.md](docs/design-patterns/singleton.md)

**Functional Requirements (FR-6):**
- A single global inventory will be shared to ensure that customers and staff access the same inventory.
- The creation of multiple inventories will be prohibited.
- Singleton also manages FlyweightFactory instances for shared data optimization.

**Implementation:** See [singleton.md](docs/design-patterns/singleton.md) for file structure and implementation details.

---

## 2.2 Structural Patterns

### Composite (Inventory Structure)
**Pattern Documentation:** [composite.md](docs/design-patterns/composite.md)

**Functional Requirements (FR-7):**
- Plants will be organised into a hierarchical structure using Composite, where these structures can be individual plants or groups of plants.
- The system will implement operations that travel through the structure and get the total amount of the contained plants.
- Plants will be grouped by categories but will ensure that individual plants will be handled in the same manner.

**Implementation:** See [composite.md](docs/design-patterns/composite.md) for file structure and implementation details.

---

### Decorator (Plant Customisation)
**Pattern Documentation:** [decorator.md](docs/design-patterns/decorator.md)

**Functional Requirements (FR-11):**
- Plants will be customisable, such as adding a charm or decorating the pot.
- Multiple decorators on a single plant will be possible, allowing wrapping on Plant objects.
- The Plant interface will be maintained such that decorated plants are treated the same as regular plants.
- Used by Builder to create complex plant species from base types plus decorations.

**Implementation:** See [decorator.md](docs/design-patterns/decorator.md) for file structure and implementation details.

---

### Facade (Unified System Interface)
**Pattern Documentation:** [facade.md](docs/design-patterns/facade.md)

**Functional Requirements (FR-17):**
- The system will provide a NurseryFacade class that handles all business logic and coordinates subsystem interactions.
- Facade enables both GUI and CLI interfaces to interact with the system through simple function calls (one per button/menu option).
- Decouples presentation layer from business logic, allowing UI changes without affecting core system.
- Manages complex operations involving multiple subsystems (Director, Singleton, Mediator, Command patterns).
- Provides methods for plant creation, inventory display, sales processing, command execution, and seasonal filtering.

**Implementation:** See [facade.md](docs/design-patterns/facade.md) for file structure and implementation details.

---

### Flyweight (Shared Data Optimization)
**Pattern Documentation:** [flyweight.md](docs/design-patterns/flyweight.md)

**Functional Requirements (FR-10):**
- The system will minimize memory usage by sharing immutable data objects across multiple plant instances.
- Shared objects include season names ("Spring", "Summer", "Autumn", "Winter"), WaterStrategy instances, and SunStrategy instances.
- FlyweightFactory manages pools of shared objects to prevent duplication.
- Supports NFR-4 (Scalability/Memory Efficiency) by ensuring memory footprint scales sub-linearly with plant count.

**Implementation:** See [flyweight.md](docs/design-patterns/flyweight.md) for file structure and implementation details.

---

## 2.3 Behavioral Patterns

### State (Plant Lifecycle)
**Pattern Documentation:** [state.md](docs/design-patterns/state.md)

**Functional Requirements (FR-3):**
- The system will manage maturity states (Seed, Vegetative, Mature, Dead), which in turn specifies minimum ages, growth rates and price increases/decreases.
- Automatic transitions between states based on the age of the plant will be implemented.
- State transitions trigger Observer notifications to staff.

**Implementation:** See [state.md](docs/design-patterns/state.md) for file structure and implementation details.

---

### Strategy (Watering Strategy)
**Pattern Documentation:** [strategy.md](docs/design-patterns/strategy.md)

**Functional Requirements (FR-4):**
- Different watering strategies (LowWater, MidWater, HighWater, AlternatingWater) will be implemented that define the water amount and frequency for different types of plants.
- Watering strategies will change based on the lifecycle of the plant.
- Strategy objects are shared via Flyweight pattern for memory efficiency.

**Implementation:** See [strategy.md](docs/design-patterns/strategy.md) for file structure and implementation details.

---

### Strategy (Sun Strategy)
**Pattern Documentation:** [strategy.md](docs/design-patterns/strategy.md)

**Functional Requirements (FR-5):**
- Different sun strategies (LowSun, MidSun, HighSun) will be implemented that define the intensity and hours of sun needed for different types of plants.
- Strategy objects are shared via Flyweight pattern for memory efficiency.

**Implementation:** See [strategy.md](docs/design-patterns/strategy.md) for file structure and implementation details.

---

### Observer (Staff Monitoring)
**Pattern Documentation:** [observer.md](docs/design-patterns/observer.md)

**Functional Requirements (FR-12):**
- Staff members will observe assigned plants' states to receive notifications about the health changes and lifecycle changes of the observed plant.
- The system will notify the assigned staff of state changes.
- PlantGroup acts as Subject, Staff acts as Observer.

**Implementation:** See [observer.md](docs/design-patterns/observer.md) for file structure and implementation details.

---

### Observer (Inventory Tracking)
**Pattern Documentation:** [observer.md](docs/design-patterns/observer.md)

**Functional Requirements (FR-8):**
- Staff and customers will be notified of inventory changes from sales and stock increases and decreases.
- Multiple staff will be able to observe the same inventory, ensuring awareness of stock levels.
- Supports real-time updates for all stakeholders.

**Implementation:** See [observer.md](docs/design-patterns/observer.md) for file structure and implementation details.

---

### Mediator (Interactions Between Staff and Customers)
**Pattern Documentation:** [mediator.md](docs/design-patterns/mediator.md)

**Functional Requirements (FR-14):**
- A mediator will coordinate communication between staff and customers on the sales floor, allowing decoupling of staff and customers.
- SalesFloor and SuggestionFloor mediators handle different interaction types.
- Staff and Customer remain loosely coupled through the mediator.

**Implementation:** See [mediator.md](docs/design-patterns/mediator.md) for file structure and implementation details.

---

### Iterator (Traversal for Seasonal Plants)
**Pattern Documentation:** [iterator.md](docs/design-patterns/iterator.md)

**Functional Requirements (FR-9):**
- The Iterator will traverse through the Composite Plant structure based on the season the plant is assigned to.
- Seasonal iterators (SpringIterator, SummerIterator, AutumnIterator, WinterIterator) filter plants by season.
- PlantIterator provides general traversal of all plants.

**Implementation:** See [iterator.md](docs/design-patterns/iterator.md) for file structure and implementation details.

---

### Command (User Actions)
**Pattern Documentation:** [command.md](docs/design-patterns/command.md)

**Functional Requirements (FR-13):**
- Actions such as watering plants, browsing inventory, purchasing plants, and adding to inventory will be executed through Command objects.
- Command pattern encapsulates complex multi-step user interface operations, enabling undo/redo functionality.
- Used by the Facade to handle user actions from GUI/CLI interfaces.
- Decouples user interface actions from business logic execution.
- Commands include: AddToInventoryCommand, BrowsePlantsCommand, WaterPlantCommand, PurchasePlantCommand.

**Implementation:** See [command.md](docs/design-patterns/command.md) for file structure and implementation details.

---

## Pattern Summary

### Implemented Patterns (13 total)

**Creational (3):**
- Builder
- Prototype
- Singleton

**Structural (4):**
- Composite
- Decorator
- Facade
- Flyweight

**Behavioral (6):**
- Command
- Iterator
- Mediator
- Observer
- State
- Strategy

<h1 align="center">🛠️ Technologies & Tools 🛠️</h1>
<div align="center">
  <img src="https://skillicons.dev/icons?i=cpp,git,github,githubactions,cmake,latex"/>
</div>

<h1 align="center">🚀 Getting Started 🚀</h1>

## Prerequisites

- C++ compiler supporting C++11
- Make build system
- CMake 

## Building
To build the project, run:
```bash
make all
````

<h1 align="center">🤝 PhotosynTech 🤝</h1>


| Name                 | Student ID | 
| -------------------- | ---------- |
| Wilmar Smit          | u24584216  |
| Johan Coetzer        | u24564584  |
| Marcel Stoltz        | u24566552  |
| Michael Tomlinson    | u24569705  |
| Zamokuhle Zwane      | u23533413  |