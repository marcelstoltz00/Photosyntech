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
        cache[id] = new Flyweight<T>(data);

        if (data == NULL)
            throw "Data given for flyweight is NULL";
        return cache[id];
    }
}

template <class ID, class T>
FlyweightFactory<ID, T>::~FlyweightFactory()
{
    auto itr = cache.begin();
    while (itr != cache.end())
    {
        if (itr->second)
        {
            delete itr->second;
        }
        itr++;
    }
}