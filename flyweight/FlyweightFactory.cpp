#include "FlyweightFactory.h"
template <class ID, class T>
FlyweightFactory<ID, T>::FlyweightFactory()
{
}

template <class ID, class T>
Flyweight<T> *FlyweightFactory<ID, T>::getFlyweight(ID id, T data)
{

    if (cache.find(id) != cache.end())
    {
        return cache[id];
    }
    else
    {
        if (data != NULL)
            cache[id] = new Flyweight<T>(data);

        return cache[id];
    }
}

template <class ID, class T>
FlyweightFactory<ID, T>::~FlyweightFactory()
{
    typename unordered_map<ID, T>::iterator itr = cache.begin();
    while (itr != cache.end())
    {
        if (*itr)
        {
            delete *itr->second();
        }
        itr++;
    }
}