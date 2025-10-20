#include "Singleton.h"
Inventory *Inventory::instance = nullptr;

Inventory::Inventory()
{
    // waiting for update of header file
    // inventory = new PlantGroup();

    // remove
    inventory = nullptr;
    // remove

    stringFactory = new FlyweightFactory<string, string *>();
    waterStrategies = new FlyweightFactory<int, WaterStrategy *>();
    sunStrategies = new FlyweightFactory<int, SunStrategy *>();
    states = new FlyweightFactory<int, MaturityState *>();
    staffList = new vector<Staff *>();
    customerList = new vector<Customer *>();

    // Adding the water strategies
    waterStrategies->getFlyweight(LowWater::getID(), new LowWater());
    waterStrategies->getFlyweight(MidWater::getID(), new MidWater());
    waterStrategies->getFlyweight(HighWater::getID(), new HighWater());
    waterStrategies->getFlyweight(AlternatingWater::getID(), new AlternatingWater());

    // adding the water strategies
    sunStrategies->getFlyweight(LowSun::getID(), new LowSun());
    sunStrategies->getFlyweight(MidSun::getID(), new MidSun());
    sunStrategies->getFlyweight(HighSun::getID(), new HighSun());

    // adding the maturities { wating on header update}
    // states->getFlyweight(Seed::getID(), new Seed());
    // states->getFlyweight(Vegetative::getID(), new Vegetative());
    // states->getFlyweight(Mature::getID(), new Mature());
    // states->getFlyweight(Dead::getID(), new Dead());
}
Inventory::~Inventory()
{
    if (inventory)
        delete inventory;

    delete stringFactory;
    delete waterStrategies;
    delete sunStrategies;
    delete states;

    std::vector<Staff *>::iterator itr = staffList->begin();
    while (!(itr == staffList->end()))
    {
        if (*itr != nullptr)
        {
            delete *itr;
        }
        itr++;
    }

    std::vector<Customer *>::iterator itrCustomer = customerList->begin();
    while (!(itrCustomer == customerList->end()))
    {
        if (*itrCustomer != nullptr)
        {
            delete *itrCustomer;
        }
        itrCustomer++;
    }
    delete staffList;
    delete customerList;
}
Inventory *Inventory::getInstance()
{
    if (!instance)
    {
        instance = new Inventory();
    }

    return instance;
}

Flyweight<std::string *> *Inventory::getString(std::string str)
{
    string *flyweightData = new string(str);
    Flyweight<std::string *> *fly = stringFactory->getFlyweight(*flyweightData, flyweightData);
    if (fly->getState() != flyweightData)
    {
        delete flyweightData;
    }

    return fly;
}
Flyweight<WaterStrategy *> *Inventory::getWaterFly(int id)
{

    return waterStrategies->getFlyweight(id);
}
Flyweight<MaturityState *> *Inventory::getStates(int id)
{
    return states->getFlyweight(id);
}

Flyweight<SunStrategy *> *Inventory::getSunFly(int id)
{
    return sunStrategies->getFlyweight(id);
}

PlantGroup *Inventory::getInventory()
{
    return inventory;
}

vector<Customer *> *Inventory::getCustomers()
{
    return customerList;
}
vector<Staff *> *Inventory::getStaff()
{
    return staffList;
}

void Inventory::addCustomer(Staff *staff)
{
    staffList->push_back(staff);
}
void Inventory::addCustomer(Customer *customer)
{
    customerList->push_back(customer);
}