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
- **FR-12: Plant Monitoring by Staff** - Allows staff members to monitor assigned plants and receive notifications about health changes and lifecycle transitions
- **FR-8: Inventory Tracking and Notifications** - Notifies staff of inventory changes; supports multiple staff monitoring the same inventory

### Supporting Requirements
- **NFR-5: Reliability** - Decouples plant groups from staff, allowing changes to one without affecting the other
- **FR-13: Staff Action Execution** - Notifications trigger staff to execute appropriate care actions
