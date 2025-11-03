# Observer Pattern

## 1. Responsibility
Establishes a one-to-many dependency between `PlantGroup` objects (Subjects) and `Staff` members (Observers). When a `PlantGroup`'s state changes (e.g., plants need water or sunlight, or their maturity state changes), all registered `Staff` observers are automatically notified, allowing them to react appropriately.

## 2. File Structure
```
observer/
├── Observer.h/.cpp # Abstract Observer interface
└── Subject.h/.cpp  # Abstract Subject interface
```

## 3. Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Subject** | `Subject` (abstract)<br>`PlantGroup` (concrete) | Defines the interface for attaching, detaching, and notifying observers. `PlantGroup` maintains a list of `Observer`s and implements the notification logic. |
| **Observer** | `Observer` (abstract)<br>`Staff` (concrete) | Defines the update interface (`getWaterUpdate()`, `getSunUpdate()`, `getStateUpdate()`) for receiving notifications. `Staff` implements these methods to respond to plant care needs and lifecycle events. The `Observer` interface also includes `getNameObserver()` for identification. |

## 4. Functional Requirements

### Primary Requirements
- **FR-14: Plant Monitoring by Staff**: Directly enables staff members to monitor assigned plant groups and receive real-time notifications about health changes and lifecycle transitions.
- **FR-8: Inventory Tracking and Notifications**: Facilitates notifying staff of inventory changes (e.g., plants needing care) and supports multiple staff members monitoring the same inventory or plant group.

### Supporting Requirements
- **NFR-5: Reliability**: Promotes loose coupling between `PlantGroup`s and `Staff` members, allowing changes to one without affecting the other.
- **FR-15: Staff Action Execution**: Notifications serve as triggers for staff to execute appropriate care actions (e.g., watering, adding sunlight) via the `NurseryFacade`.

## 5. System Role & Integration

The **Observer** pattern is crucial for enabling **proactive plant care and staff management**:

- **Loose Coupling**: `PlantGroup`s (Subjects) do not need to know the concrete types of `Staff` (Observers) that are monitoring them. Communication happens through abstract interfaces.

- **Notification Mechanism**: `PlantGroup` implements the `Subject` interface. Within its `update()` method, after processing plant changes, it checks for conditions (e.g., `if (component->getWaterValue() <= 50)`) and, if met, calls its `waterNeeded()`, `sunlightNeeded()`, or `stateUpdated()` methods. These methods then iterate through the attached `Observer`s and invoke their respective update methods.

- **Staff Responsiveness**: `Staff` members, as `ConcreteObserver`s, implement the update methods to react to these notifications. For instance, `Staff::getWaterUpdate()` would log the event or queue a care action.

- **Dynamic Subscriptions**: `Staff` members can be dynamically attached to or detached from `PlantGroup`s using `PlantGroup::attach()` and `PlantGroup::detach()`, often orchestrated by the `NurseryFacade`.

- **Pattern Integration**:
  - **Composite Pattern**: `PlantGroup` (a composite node) acts as the concrete `Subject` that observers attach to.
  - **State Pattern**: State transitions within `LivingPlant`s (managed by the State pattern) can trigger `PlantGroup` to send `stateUpdated()` notifications to observers.
  - **Facade Pattern**: The `NurseryFacade` provides high-level methods (`setObserver`, `RemoveObserver`) for clients to manage observer relationships between `Staff` and `PlantGroup`s.
  - **Mediator Pattern**: `Staff` (the concrete observer) often interacts with customers via `Mediator`s, and notifications might inform their mediated interactions.

## 6. Design Rationale

The Observer pattern was chosen for plant monitoring because:
1. **One-to-Many Dependency**: It efficiently handles scenarios where multiple `Staff` members need to be informed about changes in the same `PlantGroup`.
2. **Dynamic Subscriptions**: `Staff` members can be added or removed as observers at runtime without requiring modifications to the `PlantGroup`.
3. **Loose Coupling**: It minimizes dependencies between `PlantGroup`s and `Staff` members, making the system more flexible and easier to maintain.
4. **Event-Driven System**: It supports an event-driven architecture where changes in plant status automatically trigger responses from monitoring staff.
5. **Scalability**: It allows for efficient notification of multiple observers without the need for constant polling.

![Observer Diagram](https://raw.githubusercontent.com/marcelstoltz00/Photosyntech/main/docs/images/Observer.jpg)