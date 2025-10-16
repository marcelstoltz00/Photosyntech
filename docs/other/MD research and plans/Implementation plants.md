## Before implementing begins
- the .h files for all classes will be fully implemented as it stands in the class diagram
	- For everyone to have the correct interface when implementing
	- This will be done likely monday / tuesday.
	- This ensures no feature creep and allows us to speed up the implementation 
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
## Implementation components 
### Plants and its sub parts
![[Pasted image 20251016164540.png]]
#### Plant group 1 
Done by {}
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
#### Plant group 2 
Done by {};
- Includes 
	- ==water strategy== => return the water value 
	- ==Sun strategy== => return the sun value
	- ==Maturities== => make sure that all the states can go from one to the next based on the passed in plants `getAge()` function 
		- If state progresses or it dies based on water, sunlight and health needs 
			- Use the plants `setMaturityState()` function to progress the state
			- At the same time its water & sun can be upgraded / downgraded if we wish
	- ==PlantGroup== => since composite can interact will all of these previously mentioned classes.

### observer and mediator
done by {}
![[Pasted image 20251016164625.png]]
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
### Builder
done by {}
![[Pasted image 20251016165729.png]]
- Your job is to make as many builders as possible with the attributes we have 
- Don't worry about specialized directors for MVP. 
- You can team up with somone else if you are done early 
- -> all plants must be given a season for iterator.
### Singleton and flyweight
done by {Wilmar Smit} (pls)
- I really want to implement this one as i think i did tons of planning on flyweights and such and would love to implement this 
- Ill also start implementing the multi-threading for this where a thread in the singleton will run and do tick for all the plants (it will only be the outline since none of the plants have their tick functions )
![[Pasted image 20251016165914.png]]
### Iterator 
done by {} -> i can also do this one if its a pain i kinda know how it can be done. 
![[Pasted image 20251016170240.png]]
- Im too tired to go through this one in its entirety 
	- plant iterator checks for all plants matching a name given in the constructor of AggPlant
	- the others Will iterate through different seasons 
		- -> all plants must be given a season in the builder 
		- -> find out from whoever implements plants how getSeason() will work and what you need to access it if its through a living plant pointer etc 
	- remember how the composite looks 
	\[ \[ composite ] \[ composite  ] ]
	- Somehow each inner composite should also be traversed. 
	- your decision on depth first or breadth first searching. 
	- ![[Pasted image 20251016171202.png]]
		- This interface must be updated to have some means of accessing inner lists 
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

