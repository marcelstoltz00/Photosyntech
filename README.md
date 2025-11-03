<p align="center">
  <img src="https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/photosyntech_logo.JPG" alt="PhotoSyntech Logo" width="200"/>
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

<div align="center">

**[View the Project Wiki](https://github.com/marcelstoltz00/Photosyntech/wiki) | [Full Documentation (Doxygen)](https://marcelstoltz00.github.io/Photosyntech/) | [Read the Report](docs/report.pdf)**

</div>

<h2 align="center">🌱 Key Features 🌱</h2>

*   **Plant Management:** Track and manage a virtual collection of plants.
*   **Growth Simulation:** Watch your plants grow, change and react based on care routines.
*   **Design Pattern Showcase:** A practical C++ demonstration of 12 different GoF design patterns.

#### Manage a plant inventory
![Inventory](https://github.com/user-attachments/assets/e7107b02-9bfe-4141-ad53-5ca5b247a42a)

#### Simulate plant life cycles
![simulatePlants](https://github.com/user-attachments/assets/c3296be3-70af-4171-b8df-5c8c294de7cf)

#### Manage Staff
![manageStaff](https://github.com/user-attachments/assets/788b012d-0932-41f5-a538-710f0ee9ec54)


#### Handle customer interactions
![customerInteractions](https://github.com/user-attachments/assets/4155c72b-de44-4647-b325-42759f9ee365)


#### Watch your plants grow
![growth](https://github.com/user-attachments/assets/1aeb2f4d-c730-4523-86f4-dffa76cce5b8)

<h2 align="center">🚀 Quick Start 🚀</h2>

### Prerequisites

*   **Core:** A C++11 compliant compiler (e.g., `g++`, `clang`), `make`, `git`, and `curl`.
*   **For the TUI (with image support):** `cmake` and **image loading libraries (e.g., libjpeg)** are also required.
*   **Optional Developer Tools:** `doxygen` (docs), `gcovr` (coverage), `valgrind` (memory checks).

### Installation & Running

```bash
# 1. Clone the Repository
git clone https://github.com/marcelstoltz00/Photosyntech.git
cd Photosyntech

# 2. Build and Run the Core Unit Tests
make test-run

# 3. (Optional) Build and Run the TUI
make tui-manager
```

<h2 align="center">🏛️ Design Patterns Used 🏛️</h2>

This project employs 12 different design patterns. For a detailed explanation of each, please see their individual pages on our project wiki.

| Category     | Patterns                                                                                                                                                                                                                                                                                       | 
| :----------- | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Creational** | [Builder](https://github.com/marcelstoltz00/Photosyntech/wiki/builder) · [Prototype](https://github.com/marcelstoltz00/Photosyntech/wiki/prototype) · [Singleton](https://github.com/marcelstoltz00/Photosyntech/wiki/singleton)                                                                                                                                                                                                  |
| **Structural** | [Composite](https://github.com/marcelstoltz00/Photosyntech/wiki/composite) · [Decorator](https://github.com/marcelstoltz00/Photosyntech/wiki/decorator) · [Facade](https://github.com/marcelstoltz00/Photosyntech/wiki/facade) · [Flyweight](https://github.com/marcelstoltz00/Photosyntech/wiki/flyweight)                                                                                                                                                                     |
| **Behavioral** | [Iterator](https://github.com/marcelstoltz00/Photosyntech/wiki/iterator) · [Mediator](https://github.com/marcelstoltz00/Photosyntech/wiki/mediator) · [Observer](https://github.com/marcelstoltz00/Photosyntech/wiki/observer) · [State](https://github.com/marcelstoltz00/Photosyntech/wiki/state) · [Strategy](https://github.com/marcelstoltz00/Photosyntech/wiki/strategy)                                                                                                                                               |


<h2 align="center">🛠️ Technologies & Tools 🛠️</h2>
<div align="center">
  <img src="https://skillicons.dev/icons?i=cpp,git,github,githubactions,cmake,latex"/>
</div>

<h2 align="center">🤝 Photosyntech Team 🤝</h2>

<p align="center">
  <img src="https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/Team.jpg" alt="Photosyntech Team" width="600"/>
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

<h2 align="center">📊 UML Diagrams 📊</h2>

<div align="center">

| Diagram Type         | Link                                                                                             |
| :------------------- | :----------------------------------------------------------------------------------------------- |
| Activity Diagram     | [View Diagram](https://github.com/marcelstoltz00/Photosyntech/wiki/Activity-Diagram)             |
| Communication Diagram| [View Diagram](https://github.com/marcelstoltz00/Photosyntech/wiki/Communication-Diagram)          |
| Object Diagram       | [View Diagram](https://github.com/marcelstoltz00/Photosyntech/wiki/Object-Diagram)               |
| Sequence Diagram     | [View Diagram](https://github.com/marcelstoltz00/Photosyntech/wiki/Sequence-Diagram)             |
| State Diagram        | [View Diagram](https://github.com/marcelstoltz00/Photosyntech/wiki/State-Diagram)                |
| System Class Diagram | [View Diagram](https://github.com/marcelstoltz00/Photosyntech/wiki/System-Class-Diagram)         |

</div>
