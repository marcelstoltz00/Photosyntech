# Non-Functional Requirements

## Overview
Non-functional requirements specify how well the system performs rather than what it does. They define quality attributes such as performance, maintainability, usability, scalability, and reliability.

---

## NFR-1: Performance
**Quality Attribute**: Performance

**Description**: The system must be able to execute all staff care routines for a simulation of up to 10,000 active plants within a single simulated day cycle to ensure smooth progression.

**Measurement Criteria**:
- All care routines complete within one day cycle
- No noticeable lag or delays during simulation
- Maximum plants supported: 10,000

**Priority**: High

---

## NFR-2: Maintainability/Extensibility
**Quality Attribute**: Maintainability, Extensibility

**Description**: The system must be implemented such that adding a new type of care routine or a new plant species requires modification to only a maximum of two existing classes or files.

**Measurement Criteria**:
- New plant species: ≤ 2 file modifications
- New care routine: ≤ 2 file modifications
- Changes are localized and do not ripple through the system

**Priority**: High

---

## NFR-3: Usability
**Quality Attribute**: Usability

**Description**: The system must utilize a clear, text-based or visual interface where all available actions and input parameters are displayed to the user upon request. A new user without any prior knowledge of the system should be able to navigate the system using only the interface prompts.

**Measurement Criteria**:
- All actions clearly labeled and accessible
- Help/instructions available on request
- No external documentation required for basic operation
- First-time users can complete basic tasks without assistance

**Priority**: Medium

---

## NFR-4: Scalability
**Quality Attribute**: Scalability, Memory Efficiency

**Description**: The system must be able to handle a simulation with an inventory of up to 5,000 unique plant instances without memory exhaustion or a noticeable decrease in simulation speed. The system shall achieve this through efficient memory management including sharing of immutable data objects across plant instances.

**Measurement Criteria**:
- Maximum unique plant instances: 5,000
- No memory exhaustion
- No significant performance degradation
- Simulation speed remains consistent
- Shared immutable objects (strategies, seasons) are reused across instances
- Memory footprint scales sub-linearly with number of plants

**Priority**: High

---

## NFR-5: Reliability
**Quality Attribute**: Reliability, Modularity

**Description**: The whole system must be designed with distinct modules for the staff, greenhouse, and customer interactions. This also needs to ensure that a change in one area does not break any functionality in any other area.

**Measurement Criteria**:
- Clear separation between modules
- Changes in one module do not affect others
- Module interfaces are well-defined
- System remains stable during module updates

**Priority**: High

---

## Summary Table

| ID | Quality Attribute | Description | Priority |
|---|---|---|---|
| NFR-1 | Performance | Execute care routines for 10,000 plants per day cycle | High |
| NFR-2 | Maintainability/Extensibility | Add new features with ≤2 file modifications | High |
| NFR-3 | Usability | Clear interface navigable by new users | Medium |
| NFR-4 | Scalability/Memory Efficiency | Handle 5,000 plant instances with shared immutable data | High |
| NFR-5 | Reliability | Modular design with isolated subsystems | High |