# Observer Pattern

## Responsibility
Establishes a one-to-many dependency between plant groups and staff members, automatically notifying all registered staff observers when plants require water, sunlight, or experience state changes.

## Participant Mapping

| Pattern Role | Photosyntech Class(es) | Responsibility |
|--------------|------------------------|----------------|
| **Subject** | `Subject` (abstract)<br>`PlantGroup` (concrete) | Maintains list of observers and provides methods to attach/detach them; notifies observers of plant care needs and state changes |
| **Observer** | `Observer` (interface)<br>`Staff` (concrete) | Defines update interface for receiving notifications about plant status changes |
| **ConcreteObserver** | `Staff` | Implements the update interface to receive and respond to plant care notifications (water needed, sunlight needed, state changes) |

## Functional Requirements

### Primary Requirements
- **FR-14: Plant Monitoring by Staff** - Allows staff members to monitor assigned plants and receive notifications about health changes and lifecycle transitions
- **FR-8: Inventory Tracking and Notifications** - Notifies staff of inventory changes; supports multiple staff monitoring the same inventory

### Supporting Requirements
- **NFR-5: Reliability** - Decouples plant groups from staff, allowing changes to one without affecting the other
- **FR-15: Staff Action Execution** - Notifications trigger staff to execute appropriate care actions

## System Role & Integration

### Pattern Integration
The **Observer** pattern enables **automatic monitoring and notifications** through these interactions:

- **Composite Pattern**: `PlantGroup` (composite node) implements Subject interface
- **State Pattern**: State transitions trigger notifications to observers
- **Facade Pattern**: Facade coordinates observer notifications and staff actions
- **Mediator Pattern**: Staff (observer) coordinates with customers through mediators
- **Singleton Pattern**: Staff instances managed globally for consistent monitoring
- **Strategy Pattern**: Observer may respond differently based on plant strategies
- **Facade Pattern**: Facade sets up observer relationships during initialization

### System Dependencies
- **Monitoring Flow**: Plant groups notify staff of water/sunlight/state needs
- **Event-Driven Actions**: Staff responds to notifications with care actions via facade
- **Decoupling**: Plants unaware of specific staff implementation
- **Scalability**: Multiple staff members can monitor same plant group independently

## Design Rationale

The Observer pattern was chosen because:
1. **One-to-Many**: Multiple staff members monitor same plant groups
2. **Dynamic Subscriptions**: Staff can be added/removed without plant knowledge
3. **Loose Coupling**: Plants and staff communicate through abstract interfaces
4. **Event-Driven**: Notifications trigger appropriate staff responses
5. **Maintenance**: Adding new observer types doesn't modify plant code
6. **Scalability**: Efficient multi-observer notifications without polling

## Extension Points

**Adding New Observer Types:**
1. Create observer class implementing `Observer` interface in observer or mediator directories
2. Implement `update()` to respond to notifications from Subject
3. Can observe from `PlantGroup` (composite) or individual plants if interface expanded
4. Path: `observer/NewObserverType.h` or `mediator/NewStaffRole.h`
5. Register observer with plant groups through Facade or direct attachment
6. Observer maintains local state tracking plant changes
