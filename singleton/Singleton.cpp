#include "Singleton.h"

Inventory::Inventory()
{
    inventory = new PlantGroup();
    stringFactory = new FlyweightFactory<string, string *>();
    waterStrategies = new FlyweightFactory<int, WaterStrategy *>();
    sunStrategies = new FlyweightFactory<int, SunStrategy *>();
    states = new FlyweightFactory<int, MaturityState *>();
    staffList = new vector<Staff *>();
    customerList = new vector<Customer *>();
}
Inventory *Inventory::getInstance()
{
    if (!instance)
    {
        instance = new Inventory();
    }

    return instance;
}

const Flyweight<std::string *> *Inventory::getString(std::string str)
{
    string *flyweightData = new string(str);
    Flyweight<std::string *> *fly = stringFactory->getFlyweight(*flyweightData, flyweightData);
    if (fly->getState() != flyweightData)
    {
        delete flyweightData;
    }

    return fly;
}
const Flyweight<WaterStrategy *> *Inventory::getWaterFly(int id)
{

    return waterStrategies->getFlyweight(id);
}
const Flyweight<MaturityState *> *Inventory::getStates(int id)
{
    return states->getFlyweight(id);
}

const Flyweight<SunStrategy *> *Inventory::getSunFly(int id)
{
    return sunStrategies->getFlyweight(id);
}

const PlantGroup *Inventory::getInventory()
{
    return inventory;
}
