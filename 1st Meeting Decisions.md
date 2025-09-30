## Greenhouse/Garden Area
#### Plant Care
 - Plants require different care based off type and maturity
	 - Strategy for Sunlight/Water/Fertiliser - Might be Decorator
#### Plant Lifecycle
- The life cycle of a plant differs per plant type. Some grow to maturity much faster than others meaning that plants may be put up for sale at different times.
	- State - Pricing will be based off State
#### Plant Inventory
- There must be an inventory tracking subsystem in place so that staff know what is on hand to sell to the customers. All plants should be accounted for, whether they are ready to sell or still growing to maturity.
	- Singleton - Only one instance of an inventory can exist
	- Observer - Updates Inventory on Changes
	- Composite - Used to group plants together
#### Plant Stock
- Prototype - Plants can be cloned - simulating an order
- Abstract Factory - Seasonal Plants - Factory needs to start at a state - eg. Mature
	- Potentially Factory Method in this
## Staff
#### Plant Care
 - Tend to plants according to their unique care routines (watering, fertilising, sunlight management, pruning, etc.).
#### Plant Life-cycles
- Monitor plant health and life cycles, and take action when plants need extra attention.
	- Observer - Subscribed to State
#### Inventory
- Track inventory and coordinate with other staff to ensure the sales floor reflects what is available in the greenhouse.
	- Observer - Observes inventory
#### Customer Interaction
- Interact with customers by offering advice, answering questions, and helping them find suitable plants.
	- Mediator - Handles staff - customer interaction
## Customer
#### Customer Browsing
- Customers can view available plants, ask for information, or request recommendations.
#### Personalisation
- Customers may want to customise their plants (e.g., decorative pots, gift wrapping, or special arrangements).
	- Decorator - Add to Plant/Composition
#### Interaction with Staff
- They receive guidance, purchase assistance, and updates on availability or stock changes.
	- Mediator
#### Sales and Transactions
- The system should handle plant purchases, updating inventory, and optionally recording transaction details.
	- Builder???
	- Strategy??
## GUI/Interface
#### Facade
 - Used to exclusively interact with DearIamGui
#### Command
 - Used to interact with Facade for complex actions
