#include "NurseryFacade.h"

NurseryFacade::NurseryFacade()
{
    sunflowerBuilder = new SunflowerBuilder();
    roseBuilder = new RoseBuilder();
    jadePlantBuilder = new JadePlantBuilder();
    mapleBuilder = new MapleBuilder();
    cactusBuilder = new CactusBuilder();
    cherryBlossomBuilder = new CherryBlossomBuilder();
    lavenderBuilder = new LavenderBuilder();
    pineBuilder = new PineBuilder();
    director = new Director(sunflowerBuilder);
    sales = new SalesFloor();
    suggestionFloor = new SuggestionFloor();
}

NurseryFacade::~NurseryFacade()
{
    delete director;
    delete sunflowerBuilder;
    delete roseBuilder;
    delete jadePlantBuilder;
    delete mapleBuilder;
    delete cactusBuilder;
    delete cherryBlossomBuilder;
    delete lavenderBuilder;
    delete pineBuilder;
    delete sales;
    delete suggestionFloor;
}

PlantComponent *NurseryFacade::createPlant(const std::string &type)
{
    Builder *selectedBuilder = nullptr;

    if (type == "Sunflower")
        selectedBuilder = sunflowerBuilder;
    else if (type == "Rose")
        selectedBuilder = roseBuilder;
    else if (type == "Jade Plant")
        selectedBuilder = jadePlantBuilder;
    else if (type == "Maple")
        selectedBuilder = mapleBuilder;
    else if (type == "Cactus")
        selectedBuilder = cactusBuilder;
    else if (type == "Cherry Blossom")
        selectedBuilder = cherryBlossomBuilder;
    else if (type == "Lavender")
        selectedBuilder = lavenderBuilder;
    else if (type == "Pine")
        selectedBuilder = pineBuilder;
    else
        return nullptr;

    director = new Director(selectedBuilder);
    director->construct();
    PlantComponent *plant = director->getPlant();

    plants.push_back(plant);

    PlantComponent *inventoryRoot = Inventory::getInstance()->getInventory();
    if (inventoryRoot && inventoryRoot->getType() == ComponentType::PLANT_GROUP)
    {
        PlantGroup *rootGroup = dynamic_cast<PlantGroup *>(inventoryRoot);
        if (rootGroup)
        {
            rootGroup->addComponent(plant);
        }
    }

    return plant;
}

void NurseryFacade::waterPlant(PlantComponent *plant)
{
    if (plant)
        plant->water();
}

void NurseryFacade::addSunlight(PlantComponent *plant)
{
    if (plant)
        plant->setOutside();
}

std::string NurseryFacade::getPlantInfo(PlantComponent *plant)
{
    return plant ? plant->getInfo() : "No plant selected";
}

PlantComponent *NurseryFacade::getPlantFromBasket(Customer *customer, int index)
{
    if (customer && customer->getBasket() && customer->getBasket()->getPlants())
    {
        if (customer->getBasket()->getPlants()->empty() || index < 0 || index >= customer->getBasket()->getPlants()->size())
        {
            return nullptr;
        }

        AggPlant *agg = new AggPlant(customer->getBasket()->getPlants());
        Iterator *itr = agg->createIterator();
        int count = 0;

        while (!itr->isDone() && count != index)
        {
            itr->next();
            count++;
        }

        PlantComponent *curr = nullptr;
        if (!itr->isDone())
        {
            curr = itr->currentItem();
        }

        delete agg;
        delete itr;
        return curr;
    }
    return nullptr;
}

std::vector<std::string> NurseryFacade::getAvailablePlantTypes()
{
    return {
        "Sunflower", "Rose", "Jade Plant", "Maple",
        "Cactus", "Cherry Blossom", "Lavender", "Pine"};
}

PlantComponent *NurseryFacade::getInventoryRoot()
{
    return Inventory::getInstance()->getInventory();
}

std::list<PlantComponent *> NurseryFacade::getGroupContents(PlantComponent *group)
{
    PlantGroup *plantGroup = dynamic_cast<PlantGroup *>(group);
    if (plantGroup)
    {
        return *plantGroup->getPlants();
    }
    return {};
}

PlantGroup *NurseryFacade::createPlantGroup()
{
    PlantGroup *newGroup = new PlantGroup();
    return newGroup;
}

PlantGroup *NurseryFacade::createPlantGroup(const std::string &name)
{
    PlantGroup *newGroup = new PlantGroup(name);
    return newGroup;
}

void NurseryFacade::addComponentToGroup(PlantComponent *parent, PlantComponent *child)
{
    PlantGroup *group = dynamic_cast<PlantGroup *>(parent);
    if (group)
    {
        group->addComponent(child);
    }
}

void NurseryFacade::removeComponentFromInventory(PlantComponent *component)
{
    PlantComponent *root = Inventory::getInstance()->getInventory();
    PlantGroup *rootGroup = dynamic_cast<PlantGroup *>(root);

    if (rootGroup)
    {
        rootGroup->removeComponent(component);
    }
}

bool NurseryFacade::startNurseryTick()
{
    return Inventory::startTicker();
}

bool NurseryFacade::stopNurseryTick()
{
    return Inventory::stopTicker();
}

Customer *NurseryFacade::addCustomer(string name)
{
    if (name.empty() != false)
    {
        return nullptr;
    }
    std::vector<Customer *> *list = Inventory::getInstance()->getCustomers();
    for (size_t i = 0; i < list->size(); i++)
    {
        if ((*list)[i]->getName() == name)
        {
            return (*list)[i];
        }
    }

    Customer *nCust = new Customer(name);
    Inventory::getInstance()->addCustomer(nCust);
    nCust->setSalesFloor(sales);
    nCust->setSuggestionFloor(suggestionFloor);
    return nCust;
}

string NurseryFacade::askForSuggestion(Customer *customer)
{
    if (customer)
        return customer->askForSuggestion();

    return "";
}
bool NurseryFacade::addToCustomerBasket(Customer *customer, PlantComponent *nPlant)
{
    if (customer && nPlant)
    {
        customer->addPlant(nPlant);
        Inventory::getInstance()->getInventory()->getPlants()->remove(nPlant);
        return true;
    }
    return false;
}
string NurseryFacade::customerPurchase(Customer *customer)
{
    if (customer)
        return customer->purchasePlants();
    return "";
}

Staff *NurseryFacade::addStaff(string name)
{
    if (name.empty() != false)
    {
        name = "Staff";
    }

    std::vector<Staff *> *list = Inventory::getInstance()->getStaff();
    for (size_t i = 0; i < list->size(); i++)
    {
        if ((*list)[i]->getName() == name)
        {
            return (*list)[i];
        }
    }
    Staff *nStaff = new Staff(name);
    Inventory::getInstance()->addStaff(nStaff);
    nStaff->setSalesFloor(sales);
    nStaff->setSuggestionFloor(suggestionFloor);
    return nStaff;
}

void NurseryFacade::setObserver(Staff *staff, PlantGroup *plants)
{
    plants->attach(staff);
}

std::list<PlantComponent *> NurseryFacade::getCustomerPlants(Customer *customer)
{
    if (customer)
        return *customer->getBasket()->getPlants();
    else
        return list<PlantComponent *>();
}
std::vector<string> NurseryFacade::getCustomerBasketString(Customer *customer)
{
    if (customer && customer->getBasket() && customer->getBasket()->getPlants())
    {

        AggPlant *agg = new AggPlant(customer->getBasket()->getPlants());
        std::vector<string> plantNames;
        Iterator *itr = agg->createIterator();
        while (!itr->isDone())
        {
            plantNames.push_back(itr->currentItem()->getName());
            itr->next();
        }
        delete agg;
        delete itr;
        return plantNames;
    }
    return {};
}

std::vector<string> NurseryFacade::getMenuString()
{
    AggPlant *agg = new AggPlant(Inventory::getInstance()->getInventory()->getPlants());
    std::vector<string> plantNames;
    Iterator *itr = agg->createIterator();
    while (!itr->isDone())
    {
        plantNames.push_back(itr->currentItem()->getName());
        itr->next();
    }
    delete agg;
    delete itr;
    return plantNames;
}
PlantComponent *NurseryFacade::findPlant(int index)
{
    AggPlant *agg = new AggPlant(Inventory::getInstance()->getInventory()->getPlants());
    Iterator *itr = agg->createIterator();
    int count = 0;
    while (!itr->isDone() && count != index)
    {

        itr->next();
        count++;
    }
    PlantComponent *curr = itr->currentItem();
    delete agg;
    delete itr;
    return curr;
}

PlantComponent *NurseryFacade::removeFromCustomer(Customer *customer, int index)
{
    if (customer && customer->getBasket())
    {
        AggPlant *agg = new AggPlant(customer->getBasket()->getPlants());
        Iterator *itr = agg->createIterator();
        int count = 0;
        while (!itr->isDone() && count != index)
        {

            itr->next();
            count++;
        }
        customer->getBasket()->getPlants()->remove(itr->currentItem());
        PlantComponent *curr = itr->currentItem();
        Inventory::getInstance()->getInventory()->addComponent(curr);
        delete agg;
        delete itr;
        return curr;
    }
    return nullptr;
}

std::vector<string> NurseryFacade::getAllStaffMembers()
{
    std::vector<string> names;
    std::vector<Staff *> *staff = Inventory::getInstance()->getStaff();
    for (size_t i = 0; i < staff->size(); i++)
    {
        names.push_back((*staff)[i]->getName());
    }
    return names;
}

Staff *NurseryFacade::findStaff(int index)
{
    std::vector<string> names;
    std::vector<Staff *> staff = *Inventory::getInstance()->getStaff();
    auto itr = staff.begin();
    int count = 0;

    while (itr != staff.end() && *itr != nullptr && count < index)
    {
        count++;
        itr++;
    }

    if (*itr)
    {
        return *itr;
    }
    else
    {
        return addStaff("Staff");
    }
}

std::vector<string> NurseryFacade::getAllPlantGroups()
{
    std::vector<string> names;
    std::list<PlantComponent *> groups = *Inventory::getInstance()->getInventory()->getPlants();
    std::vector<string> groupNames;
    int count = 0;
    auto itr = groups.begin();
    while (itr != groups.end())
    {
        if (*itr && (*itr)->getType() == ComponentType::PLANT_GROUP)
        {
            groupNames.push_back("Plant Group " + to_string(count++));
        }
    }
    return groupNames;
}