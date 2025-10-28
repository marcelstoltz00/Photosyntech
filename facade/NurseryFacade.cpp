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

void NurseryFacade::addComponentToGroup(PlantComponent *parent, PlantComponent *child)
{
    PlantGroup *group = dynamic_cast<PlantGroup *>(parent);
    if (group)
    {
        group->addComponent(child);
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
    if (name.empty() == false)
    {
        name = "Customer";
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

void NurseryFacade::askForSuggestion(Customer *customer)
{
    customer->askForSuggestion();
}
void NurseryFacade::addToCustomerBasket(Customer *customer, PlantComponent *nPlant)
{
    customer->addPlant(nPlant);
}
void NurseryFacade::customerPurchase(Customer *customer)
{
    customer->purchasePlants();
}

Staff *NurseryFacade::addStaff(string name)
{
    if (name.empty() == false)
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
     return *customer->getBasket()->getPlants();
}