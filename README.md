<p align="center">
  <img src="docs/images/photosyntech_logo.JPG" alt="PhotoSyntech Logo" width="200"/>
  <br>
  <h1 align="center">Photosyntech</h1>
  <h3 align="center">A C++ Plant Management System Demonstrating Design Patterns</h3>
</p>

<div align="center">

![Unit Tests](https://github.com/marcelstoltz00/Photosyntech/actions/workflows/cpp-tests.yml/badge.svg)
![Code Coverage](https://img.shields.io/badge/dynamic/json?url=https://gist.githubusercontent.com/marcelstoltz00/0498d898440eb443f768fdfd73d46c47/raw/coverage.json&query=message&label=coverage&color=brightgreen)

![GitHub issues](https://img.shields.io/github/issues/marcelstoltz00/Photosyntech)
![GitHub pull requests](https://img.shields.io/github/issues-pr/marcelstoltz00/Photosyntech)
![GitHub last commit](https://img.shields.io/github/last-commit/marcelstoltz00/Photosyntech)
![GitHub repo size](https://img.shields.io/github/repo-size/marcelstoltz00/Photosyntech)

</div>

<h3 align="center">
PhotoSyntech is a C++ plant management system demonstrating multiple design patterns, including growth and care simulation for various plant types.
</h3>

<div align="center">

[Project Website](https://github.com/marcelstoltz00/Photosyntech) | [Full Documentation](https://marcelstoltz00.github.io/Photosyntech/) | [View Design Patterns](https://github.com/marcelstoltz00/Photosyntech/tree/main/docs/design-patterns)

</div>

<h1 align="center">🪴 Features 🪴</h1>

- 🌱 **Plant Management:** Track and manage a virtual collection of plants.
- ☀️ **Growth Simulation:** Watch your plants grow, change, and react based on care routines.
- 🎨 **Design Pattern Showcase:** A practical C++ demonstration of multiple GoF design patterns.

<h1 align="center">🏛️ Design Patterns Used 🏛️</h1>

PhotoSyntech employs 12 different design patterns to create a modular, extensible, and efficient system. Below is a summary of the patterns used. For a more detailed explanation, please see the individual documentation files.

| Category     | Pattern                                                    | Responsibility                                                                                             |
| :----------- | :--------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------- |
| **Creational** | [**Builder**](docs/design-patterns/builder.md)             | Constructs complex plant objects step by step, separating construction from representation.                |
|              | [**Prototype**](docs/design-patterns/prototype.md)           | Creates new plant objects by cloning existing instances, avoiding costly creation.                         |
|              | [**Singleton**](docs/design-patterns/singleton.md)           | Ensures a single, global instance for shared resources like the main inventory and flyweight factories.    |
| **Structural** | [**Composite**](docs/design-patterns/composite.md)           | Treats individual plants and groups of plants uniformly in a hierarchical structure.                       |
|              | [**Decorator**](docs/design-patterns/decorator.md)           | Dynamically adds new attributes and behaviors to plant objects without altering their structure.           |
|              | [**Facade**](docs/design-patterns/facade.md)                 | Provides a simplified, unified interface to the complex subsystems of the nursery.                         |
|              | [**Flyweight**](docs/design-patterns/flyweight.md)           | Minimizes memory usage by sharing common, immutable data (like strategies and seasons) among many objects. |
| **Behavioral** | [**Iterator**](docs/design-patterns/iterator.md)             | Provides a standard way to traverse plant collections, with support for filtering (e.g., by season).       |
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

- **C++ Compiler**: Supporting C++11 or later (g++/clang)
- **Make**: Build system
- **CMake**: Version 3.10+ (for TUI components)
- **Git**: For cloning dependencies
- **Optional Tools**:
  - `doxygen` - For generating documentation
  - `gcovr` - For code coverage reports
  - `valgrind` (Linux) or `leaks` (macOS) - For memory leak detection

## Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/marcelstoltz00/Photosyntech.git
cd Photosyntech
```

### 2. Build and Run Tests
```bash
make test-run
```

This will automatically:
- Download the doctest framework
- Build the project using all available CPU cores
- Run all unit tests (117 tests with 748 assertions)

## 📋 Available Make Commands

### Build Commands
| Command | Description |
|---------|-------------|
| `make test-run` | Build and run tests in one command |
| `make clean` or `make c` | Remove all build artifacts |
| `make info` | Display build configuration and available commands |

### Documentation Commands
| Command | Description |
|---------|-------------|
| `make docs` or `make doxygen` | Generate Doxygen documentation |

### Code Quality Commands
| Command | Description |
|---------|-------------|
| `make cov` | Generate code coverage report (requires `gcovr`) |
| `make leaks` | Run memory leak detection (macOS) |
| `make valgrind` or `make v` | Run Valgrind memory check (Linux) |

### TUI Commands
| Command | Description |
|---------|-------------|
| `make tui-manager` | Build and launch the TUI plant manager |
| `make tui` | Full TUI build (clone, configure, compile) |
| `make tui-clean` | Clean TUI build directory |
| `make tui-full` | Complete TUI setup from scratch |

## 🎯 Usage Examples

### Run All Tests
```bash
make test-run
```

### Generate Documentation
```bash
make docs
# Documentation will be available at: docs/doxygen/html/index.html
```

### Launch TUI Plant Manager
```bash
make tui-manager
```

### Generate Coverage Report
```bash
make cov
cat coverage.txt
```

### Clean Build Artifacts
```bash
make clean
```

### Check Build Information
```bash
make info
```



<h1 align="center">🤝 Photosyntech Team 🤝</h1>

<p align="center">
  <img src="docs/images/Team.jpg" alt="Photosyntech Team" width="600"/>
</p>

<div align="center">

| Name                 | Student ID | Role                        | 
| :------------------- | :--------- | :-------------------------- |
| Wilmar Smit          | u24584216  | TaskMaster                  |
| Johan Coetzer        | u24564584  | Thing One                   |
| Marcel Stoltz        | u24566552  | Thing Two                   |
| Michael Tomlinson    | u24569705  | The Brains And The Brawn    |
| Zamokuhle Zwane      | u23533413  | The Architect               |

</div>