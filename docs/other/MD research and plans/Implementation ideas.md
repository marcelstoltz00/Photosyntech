# Implementation suggestion
### Full simulation 
- Requires An observer (or adjacent) to tick the timers on all plants states 
	- use ticks as a way of decreasing water.
	- use ticks as a way of increasing or decreasing sunlight for plants 
		- Plant->tick();
			- water--;
			- sunlight++ / ++; (depending on some if value like outside)
			- age++ 
			- Tick will be implemented in the base class Plant
```c++
tick()
{

water--;

if (water < healthyWaterLevel || (water >= overfilled))
	{
		health --;
	else
	{
		health ++;
	}
	
if (Isoutside()) // sun strategy will out it outside
	{ 
		sun++;
	}
else
	{
		sun--;
	}
// repeat the sun checks here to increase / decrease health

	
}
```

-> this could be extended using chain of command to handle the plant object 
	-> We have a universal chain of command that all plants get pushed through that handles this 
-> per tick the plant goes through the chain 
- Could be useful to think about a very basic **concurrent** system for ticks at this level
	- <span style="background:#fff88f">- Each thread could have its own chain of command to put the plants through. </span>
- All we would need to do is set limits on where each thread increments 
- e.g 
	- using 4 threads tick through the 200 plants 
	- thread 1 gets 0 -> 50 
	- thread 2 gets 51->100
	- thread 3 gets 101 -> 150
	- thread 4 gets 151 -> 200
	- In terms of scale-ability this would make having 1 000 000 plants 4 times quicker to tick through. 


### Singleton
- Holds the flyweight factory 
	- Flyweights holding shared strings 
	- Current Season (can change every 8 ticks or something )
	
	- Winter String 
	- Summer String 
	- Autumn String
	- Spring string 

	- Season Modifier 
		- something that changes how much water is lost or sunlight is gained
	- Each plant should probably know how to handle being in off seasons 
		- <span style="background:#fff88f">More water lost </span>
		- <span style="background:#fff88f">less sun gained</span> 

- Holds a pointer to our main plant stock 
- Make a templatized flyweight that holds different data 
- Example from previous  iterator
```c++
template <typename T>

class Iterator

{

public:
Iterator() {}
virtual ~Iterator() {}
virtual void first() = 0;
virtual void next() = 0;
virtual bool isDone() = 0;
virtual T *currentItem() = 0;

};
```

```c++
 
class HistoryIterator : public Iterator<Message>
{
private:
	vector<Message *> *list; 
	int currentIndex; 
	
public:
	HistoryIterator(vector<Message *> *list);
	virtual ~HistoryIterator();
	virtual void first();
	virtual void next();
	virtual bool isDone();
	virtual Message *currentItem() override;
	virtual int operator*();

}; 

#endif
```
- Note the `currentItem()` function has a T return type and that allows us to get what type it has to change
- Example Flyweight 

```c++
template <class T>
class baseFly<T>
{
private:
T *data;
public:
T* getData()=0;
}

class SeasonFlyweight : public baseFly<string>
{
	public:
string* getData(){return this->data;};
}
```
