<p align="center">
  <img src="docs/images/photosyntech_logo.JPG" alt="PhotoSyntech Logo" width="200"/>
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

<h1 align="center">🏛️ Design Patterns Used 🏛️</h1>

PhotoSyntech employs 13 different design patterns to create a modular, extensible, and efficient system. Below is a summary of the patterns used. For a more detailed explanation, please see the individual documentation files.

| Category     | Pattern                                                    | Responsibility                                                                                             |
| :----------- | :--------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------- |
| **Creational** | [**Builder**](docs/design-patterns/builder.md)             | Constructs complex plant objects step by step, separating construction from representation.                |
|              | [**Prototype**](docs/design-patterns/prototype.md)           | Creates new plant objects by cloning existing instances, avoiding costly creation.                         |
|              | [**Singleton**](docs/design-patterns/singleton.md)           | Ensures a single, global instance for shared resources like the main inventory and flyweight factories.    |
| **Structural** | [**Composite**](docs/design-patterns/composite.md)           | Treats individual plants and groups of plants uniformly in a hierarchical structure.                       |
|              | [**Decorator**](docs/design-patterns/decorator.md)           | Dynamically adds new attributes and behaviors to plant objects without altering their structure.           |
|              | [**Facade**](docs/design-patterns/facade.md)                 | Provides a simplified, unified interface to the complex subsystems of the nursery.                         |
|              | [**Flyweight**](docs/design-patterns/flyweight.md)           | Minimizes memory usage by sharing common, immutable data (like strategies and seasons) among many objects. |
| **Behavioral** | [**Command**](docs/design-patterns/command.md)               | Encapsulates user actions (e.g., water, purchase) as objects, enabling undo, queuing, and logging.         |
|              | [**Iterator**](docs/design-patterns/iterator.md)             | Provides a standard way to traverse plant collections, with support for filtering (e.g., by season).       |
|              | [**Mediator**](docs/design-patterns/mediator.md)             | Centralizes communication between staff and customers, reducing direct dependencies between them.          |
|              | [**Observer**](docs/design-patterns/observer.md)             | Notifies staff automatically when plants change state or require care.                                     |
|              | [**State**](docs/design-patterns/state.md)                   | Manages a plant's lifecycle (Seed, Vegetative, Mature, Dead) by altering its behavior as its state changes.|
|              | [**Strategy**](docs/design-patterns/strategy.md)             | Defines a family of interchangeable algorithms for plant care (e.g., watering, sun exposure).              |

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