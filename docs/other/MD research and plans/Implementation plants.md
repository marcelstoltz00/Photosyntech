# Implementation Plans - Historical Notes

> **⚠️ DOCUMENT STATUS**: This document contains historical planning and task assignment notes from the initial development phase.
>
> **For current project documentation, see:**
> - **[ARCHITECTURE.md](../../ARCHITECTURE.md)** - Complete system architecture and design
> - **[PATTERN_MAPPING.md](../../PATTERN_MAPPING.md)** - Functional requirements mapped to patterns
> - **[CLAUDE.md](../../../CLAUDE.md)** - Project overview and quick start guide
> - **[design-patterns/](../../design-patterns/)** - Individual pattern documentation

---

## Implementation Status

> **Last Updated:** October 17, 2025

### Header Files - ✅ COMPLETED
- All .h files for all classes have been fully implemented as per the class diagram
- This provides everyone with the correct interface for implementation
- All 13 design patterns have complete header files in their respective directories:
  - `builder/`, `command/`, `composite/`, `decorator/`, `facade/`, `flyweight/`
  - `gui/`, `iterator/`, `mediator/`, `observer/`, `prototype/`, `singleton/`, `state/`, `strategy/`
- This prevents feature creep and speeds up implementation 
## Implementation details 
- The code will be broken down into sections such that everyone will work on systems related to what they are doing. 
	- These plants will be listed below. 
	- Everyone will be assigned to a certain detail of every part of the program. 
- The tick function will be a post MVP function as i believe it needs to interact with all systems once implemented.
- The last part of the implementation will be the facade which will come once again after all systems are implemented 
	- Hopefully facade can work before the MVP
	- Otherwise we will make a streamlined demo that is partially what the facade is capable of.

- ==Everyone will be expected to make their own unit tests to run on GIT HUB as is expected in the spec for the project.== 
	- These unit tests will just be your expected output in the main 
	- Github tests to my understanding run like fitch fork so use your own testing results as the set results. 
	- All testing needs to be a part of some function in main 
		- `WaterTesting() ` in main made by whoever tested it. Should have some expected output -> dont mess with others mains (->Michael <3)
 - ==Everyone must make at least 3 pull requests as expected in the project.== 

- The MVP will be the Terminal running interface for the project. 
- A gui will be implemented the week after (pray for our souls) 
- Speak to Wilmar (me) about Implementation if confused {i have a relative head canon about everything on the class diagram rn}
## Implementation Components

### Plant System Architecture
See [ARCHITECTURE.md](../../ARCHITECTURE.md#greenhouse--plant-management-subsystem) for complete plant subsystem details.

---

### Plant Species Reference (from Planning Phase)
### 🌸 **Spring Plants**

These often feature vibrant flowers and moderate stem growth.

|Plant Name|Leaf Size|Flower Size|Stem Size|Thorns|
|---|---|---|---|---|
|**Rose**|Small|Large|Medium|Yes|
|**Tulip**|Small|Large|Small|No|
|**Peony**|Large|Large|Medium|No|
|**Bougainvillea**|Small|Large|Medium|Yes|

---

### ☀️ **Summer Plants**

Typically robust, sun-loving, and structurally large.

|Plant Name|Leaf Size|Flower Size|Stem Size|Thorns|
|---|---|---|---|---|
|**Sunflower**|Large|Large|Large|No|
|**Hibiscus**|Large|Large|Medium|No|
|**Century Plant (Agave)**|Small|Small|Large|Yes|
|**Zinnia**|Small|Large|Small|No|

---

### 🍂 **Autumn Plants**

Often hardy, with defensive traits or drought adaptations.

|Plant Name|Leaf Size|Flower Size|Stem Size|Thorns|
|---|---|---|---|---|
|**Japanese Barberry**|Small|Small|Medium|Yes|
|**Chrysanthemum**|Small|Large|Medium|No|
|**Hawthorn**|Small|Small|Medium|Yes|
|**Sedum**|Small|Small|Small|No|

---

### ❄️ **Winter Plants**

Survivors of harsh climates, often with minimal foliage and defensive structures.

|Plant Name|Leaf Size|Flower Size|Stem Size|Thorns|
|---|---|---|---|---|
|**Cactus (Opuntia)**|Small|Small|Large|Yes|
|**Juniper**|Small|Small|Medium|No|
|**Yucca**|Large|Small|Large|Yes|
|**Winter Jasmine**|Small|Small|Small|No|

---
#### Plant Group 1: Core Plant Components
**Status**: Header files completed, implementation in progress
**Location**: `prototype/`, `composite/`, `decorator/`
- Includes
	- ==Plant Component== 
	- ==Living plant and its children==
		- Water and setOutside act as follows
			```c++
			void function()
			{
				this->water += flyweight->get()->water();
				// access the flyweight holding the strategy 
				// call water on that returned value
				// same for sunlight
			}
			```
		- For the affect water and affect sun functions. it should do the same 
			- uses recursion to send back the subtraction value accumulated down the chain of attributes.
		- 
	- All the ==plant Attributes== -> can be implemented with support of others.
		- All the plant Attributes can be in one cpp file?
		- ==FOR the iterator there must be a get season function to get the season assigned by the builder==
		- Make a google doc with each attribute and why you chose that value for
			- Price increase 
			- Water affect
			- Sun affect
			- Info {should just print what it is in a format followed by all attributes + living plant children} 
		- ==The only function needed for all Attributes is just the constructor where the parent is called with the chosen parameters into the parent constructor==.
	- The decorator will look like this
		```c++
		int getWater()
		{
			if (next!= null)
				return myValue + next.getWater();
			else
				return myValue;
		}
		```
	- The base components such as shrub and tree do not have a next 
	- They will simply use their parents version of the function that only returns the value
```c++ 
	int getWater()
	{
		return myValue;
	}
```
#### Plant Group 2: Strategies and States
**Status**: Header files completed, implementation in progress
**Location**: `strategy/`, `state/`, `composite/`
- Includes 
	- ==water strategy== => return the water value 
	- ==Sun strategy== => return the sun value
	- ==Maturities== => make sure that all the states can go from one to the next based on the passed in plants `getAge()` function 
		- If state progresses or it dies based on water, sunlight and health needs 
			- Use the plants `setMaturityState()` function to progress the state
			- At the same time its water & sun can be upgraded / downgraded if we wish
	- ==PlantGroup== => since composite can interact will all of these previously mentioned classes.

### Observer and Mediator Patterns
**Status**: Header files completed, implementation in progress
**Location**: `observer/`, `mediator/`
**See**: [observer.md](../../design-patterns/observer.md) and [mediator.md](../../design-patterns/mediator.md)
- Mediator acts as the suggestion floor or as a sales floor 
- A customer asking to purchase something will talk through mediator to a randomly selected staff member who will handle the purchase.
	- Customers should get a plant group as their basket and pass that through 
- A customer asking for help will go through the same process where a staff member is selected, however a staff member will present some line such as 
	- `"I reccomend the "+ // a random plant from the fly weight`
	- This can be implemented when fly weight is done post mvp even.
- add whatever functions you need to make staff and customers work (within reason)
	- ==Always communicate first with the team ==
	- Make sure it matches with mediator 
		- Customers never talk directly to staff only through mediator 
			- something like as a parameter give the basket the customers have 
			- staff return a string that is a receipt (could use chain of command) 
				- And delete the plants in the basket (out of the systems scope) 
- ==Also implement the observer keep tight communication with the person who implements composite these 2 systems need to cooperate==
### Builder Pattern
**Status**: Header files completed, implementation in progress
**Location**: `builder/`
**See**: [builder.md](../../design-patterns/builder.md)
**Implemented Builders**: RoseBuilder, SunflowerBuilder, Plant3Builder
- Your job is to make as many builders as possible with the attributes we have 
- Don't worry about specialized directors for MVP. 
- You can team up with somone else if you are done early 
- -> all plants must be given a season for iterator.
- -> all builders for the getProduct function get a clone of what theyve made. 
### Singleton and Flyweight Patterns
**Status**: Header files completed, implementation in progress
**Location**: `singleton/`, `flyweight/`
**See**: [singleton.md](../../design-patterns/singleton.md) and [flyweight.md](../../design-patterns/flyweight.md)
**Assignee**: Wilmar Smit
**Notes**:
- Flyweight pattern provides 99.92% memory reduction for shared data (see ARCHITECTURE.md)
- Singleton manages global inventory and flyweight factories
- Multi-threading implementation planned for plant tick system
### Iterator Pattern
**Status**: Header files completed, implementation in progress
**Location**: `iterator/`
**See**: [iterator.md](../../design-patterns/iterator.md)
**Implemented Iterators**: PlantIterator, SpringIterator, SummerIterator, AutumnIterator, WinterIterator
- Im too tired to go through this one in its entirety 
	- plant iterator checks for all plants matching a name given in the constructor of AggPlant
	- the others Will iterate through different seasons 
		- -> all plants must be given a season in the builder 
		- -> find out from whoever implements plants how getSeason() will work and what you need to access it if its through a living plant pointer etc 
	- remember how the composite looks 
	\[ \[ composite ] \[ composite  ] ]
	- Somehow each inner composite should also be traversed.
	- your decision on depth first or breadth first searching.
	- **Iterator Implementation Note**:
		- The PlantComponent interface must be updated to have some means of accessing inner lists 
		- Since the iterator does not know if the plant is a list or not, what can be done is something like this 
```c++
void next()
{
while (plants !=null )
{
	List<plants> * temp = plants;
	
	while (temp->getList() != null)
	{
	temp = temp->getlist();

	}
		if (temp.getseason()==myseason)
		{
			return;
		}
		else
		plants ++;
}
}
```
basically -> go as deep as possible then cycle back (youll figure it out) talk to composite team 
-> can also implement a recursive  private function used for recursively going deeper into a composite.

