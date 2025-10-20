## Memory management Plan 
- This part will go into the readme on github
- The 
- Memory management is very important and easiest to do if only parts manage it. 
### Composite 
- The composite is the object that holds all out plant data.
	- Composite will delete all its elements. 
	- ==Very IMPORTANT== 
		- ==Delete the `plantComponents getDecorator();` function==
		```c++
		PlantGroup::~PlantGroup()
		{
			 std::list<PlantComponent*>::iterator itr = plants.begin()
			while(itr != plants.end())
			{
				delete *itr->getDecorator();
				itr++;
				// should work.
			}
		}
		```
- From this all plants will be deleted.
- When customers add plants to their basket it is removed from the composite group
	- Will be explained further in the mediator section.
### Builder 
- Builders should delete the plants they store after creation.
- As they return the clone of their plant this should lead to no double frees
### Observer 
- No memory management needed 
	- Plants observed are deleted elsewhere
	- Only observers we have are staff who will be managed elsewhere.

### Living Plants 
- Do not delete anything 
- All flyweights they have access to will be deleted.
### PlantAttributes (decorator)
- Decorator will be the only one of all the attributes we have to delete.
	```c++
	PlantAttributes::~PlantAttributes()
	{
		delete nextAttribute();
		// since all the attributes will call the same destructor virtually.
		// this will set off a chain reaction.
	}
	```
### Strategies and Maturities
- Delete nothing
- Will be deleted by flyweight factory 
### Singleton 
- deletes all its memory
- ==Deletes itself way at the end is optional==
### Flyweight factory
- Deletes the flyweights it holds. 
### Flyweights 
- Delete the pointer memory they hold. 
### Mediator 
- Must be decided upon for staff and customers.
- Customers can take plants out the inventory and add them to their personal baskets. 
	- When doing so the plant is removed from the inventory (implementation TBD by composite and mediator contracts and must be documented for everyone to be on same page )
	- If customers go out of scope and their basket is not null. they delete it. 
	- If customers buy something they give their basket away to staff who delete the plant group object upon making the receipt.  When giving it away they set the basket to null in their attributes.