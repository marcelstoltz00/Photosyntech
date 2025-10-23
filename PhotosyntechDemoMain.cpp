#include <iostream>
#include <string>
#include <vector>

#include "Ansi-color-codes.h"

// Builder Pattern
#include "builder/Director.h"
#include "builder/RoseBuilder.h"
#include "builder/SunflowerBuilder.h"
#include "builder/CactusBuilder.h"
#include "builder/PineBuilder.h"
#include "builder/MapleBuilder.h"
#include "builder/JadePlantBuilder.h"
#include "builder/LavenderBuilder.h"
#include "builder/CherryBlossomBuilder.h"

// Prototype Pattern
#include "prototype/LivingPlant.h"
#include "prototype/Succulent.h"
#include "prototype/Shrub.h"
#include "prototype/Tree.h"
#include "prototype/Herb.h"

// Singleton Pattern
#include "singleton/Singleton.h"

// Composite Pattern
#include "composite/PlantComponent.h"
#include "composite/PlantGroup.h"

// Decorator Pattern
#include "decorator/PlantAttributes.h"
#include "decorator/customerDecorator/LargePot.h"
#include "decorator/customerDecorator/RedPot.h"
#include "decorator/customerDecorator/PlantCharm.h"
#include "decorator/customerDecorator/ShopThemedCharm.h"
#include "decorator/plantDecorator/Spring.h"
#include "decorator/plantDecorator/Summer.h"
#include "decorator/plantDecorator/Autumn.h"
#include "decorator/plantDecorator/Winter.h"
#include "decorator/plantDecorator/LargeFlowers.h"
#include "decorator/plantDecorator/SmallFlowers.h"
#include "decorator/plantDecorator/LargeLeaf.h"
#include "decorator/plantDecorator/SmallLeaf.h"
#include "decorator/plantDecorator/LargeStem.h"
#include "decorator/plantDecorator/SmallStem.h"
#include "decorator/plantDecorator/Thorns.h"

// Flyweight Pattern
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"

// Strategy Pattern
#include "strategy/WaterStrategy.h"
#include "strategy/SunStrategy.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "strategy/HighWater.h"
#include "strategy/AlternatingWater.h"
#include "strategy/LowSun.h"
#include "strategy/MidSun.h"
#include "strategy/HighSun.h"
#include "strategy/AlternatingSun.h"

// State Pattern
#include "state/MaturityState.h"
#include "state/Seed.h"
#include "state/Vegetative.h"
#include "state/Mature.h"
#include "state/Dead.h"

// Observer Pattern
#include "observer/Observer.h"
#include "observer/Subject.h"

// Mediator Pattern
#include "mediator/Mediator.h"
#include "mediator/User.h"
#include "mediator/Staff.h"
#include "mediator/Customer.h"
#include "mediator/SalesFloor.h"
#include "mediator/SuggestionFloor.h"

// Iterator Pattern
#include "iterator/Iterator.h"
#include "iterator/Aggregate.h"
#include "iterator/AggSeason.h"
#include "iterator/SeasonIterator.h"
#include "iterator/PlantIterator.h"
#include "iterator/AggPlant.h"

using namespace std;

// Global variables for the demo
Inventory* inventory = nullptr;
vector<PlantComponent*> createdPlants;
vector<Customer*> customers;
vector<Staff*> staffMembers;

// Demo functions
void builderPrototypeDemo();
void singletonFlyweightDemo();
void compositeDecoratorDemo();
void stateStrategyDemo();
void observerMediatorDemo();
void iteratorDemo();
void completeInteractiveDemo();
void viewSystemStatus();
void cleanup();

// Utility functions
void clearInputBuffer();
int getValidInput(int min, int max);
void displayHeader(const string& title);
void displayMainMenu();

int main()
{
    cout << BHCYN << "\n╔════════════════════════════════════════════════╗" << CRESET << endl;
    cout << BHCYN << "║        Welcome to Photosyntech Nursery         ║" << CRESET << endl;
    cout << BHCYN << "║   Demonstrating 11 Design Patterns in C++      ║" << CRESET << endl;
    cout << BHCYN << "╚════════════════════════════════════════════════╝" << CRESET << endl;

    // Initialize global inventory singleton
    inventory = Inventory::getInstance();

    bool running = true;

    while (running)
    {
        displayMainMenu();
        int choice = getValidInput(0, 8);

        switch (choice)
        {
        case 1:
            builderPrototypeDemo();
            break;
        case 2:
            singletonFlyweightDemo();
            break;
        case 3:
            compositeDecoratorDemo();
            break;
        case 4:
            stateStrategyDemo();
            break;
        case 5:
            observerMediatorDemo();
            break;
        case 6:
            iteratorDemo();
            break;
        case 7:
            completeInteractiveDemo();
            break;
        case 8:
            viewSystemStatus();
            break;
        case 0:
            cout << BHYEL << "\nThank you for visiting Photosyntech Nursery!" << CRESET << endl;
            running = false;
            break;
        }
    }

    cleanup();
    return 0;
}

// Utility functions implementation
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

int getValidInput(int min, int max)
{
    int choice;
    while (true)
    {
        cout << "Enter choice (" << min << "-" << max << "): ";
        if (cin >> choice && choice >= min && choice <= max)
        {
            return choice;
        }
        cout << BHRED << "Invalid input! Please enter a number between " << min << " and " << max << "." << CRESET << endl;
        clearInputBuffer();
    }
}

void displayHeader(const string& title)
{
    cout << "\n" << string(60, '=') << endl;
    cout << BHCYN << "          " << title << CRESET << endl;
    cout << string(60, '=') << endl;
}

void displayMainMenu()
{
    displayHeader("PHOTOSYNTECH NURSERY SYSTEM DEMO");
    cout << BHWHT << "1. Builder/Prototype Pattern Demo (Plant Creation & Cloning)" << CRESET << endl;
    cout << BHWHT << "2. Singleton/Flyweight Pattern Demo (Shared Resources)" << CRESET << endl;
    cout << BHWHT << "3. Composite/Decorator Pattern Demo (Grouping & Customization)" << CRESET << endl;
    cout << BHWHT << "4. State/Strategy Pattern Demo (Lifecycle & Care)" << CRESET << endl;
    cout << BHWHT << "5. Observer/Mediator Pattern Demo (Monitoring & Communication)" << CRESET << endl;
    cout << BHWHT << "6. Iterator Pattern Demo (Seasonal Filtering)" << CRESET << endl;
    cout << BHWHT << "7. Complete Interactive Nursery Demo" << CRESET << endl;
    cout << BHWHT << "8. View System Status" << CRESET << endl;
    cout << BHRED << "0. Exit" << CRESET << endl;
}

// Demo 1: Builder/Prototype Pattern
void builderPrototypeDemo()
{
    displayHeader("BUILDER/PROTOTYPE PATTERN DEMO");

    cout << BHYEL << "\n=== Demonstrating Builder Pattern ===" << CRESET << endl;
    cout << "The Builder pattern constructs complex plant objects step by step." << endl;
    cout << "The Director orchestrates the construction process." << endl;

    cout << "\n" << BHGRN << "Creating a Rose using RoseBuilder:" << CRESET << endl;
    Builder* roseBuilder = new RoseBuilder();
    Director* director = new Director(roseBuilder);
    director->construct();
    PlantComponent* rose = director->getPlant();
    cout << "Rose created: " << rose->getName() << endl;
    cout << "Price: $" << rose->getPrice() << endl;
    cout << "Details: " << rose->getInfo() << endl;
    createdPlants.push_back(rose);

    cout << "\n" << BHGRN << "Creating a Sunflower using SunflowerBuilder:" << CRESET << endl;
    Builder* sunflowerBuilder = new SunflowerBuilder();
    director = new Director(sunflowerBuilder);
    director->construct();
    PlantComponent* sunflower = director->getPlant();
    cout << "Sunflower created: " << sunflower->getName() << endl;
    cout << "Price: $" << sunflower->getPrice() << endl;
    createdPlants.push_back(sunflower);

    cout << "\n" << BHGRN << "Creating a Cactus using CactusBuilder:" << CRESET << endl;
    Builder* cactusBuilder = new CactusBuilder();
    director = new Director(cactusBuilder);
    director->construct();
    PlantComponent* cactus = director->getPlant();
    cout << "Cactus created: " << cactus->getName() << endl;
    cout << "Price: $" << cactus->getPrice() << endl;
    createdPlants.push_back(cactus);

    cout << "\n" << BHYEL << "=== Demonstrating Prototype Pattern ===" << CRESET << endl;
    cout << "The Prototype pattern enables cloning of plant objects." << endl;
    cout << "We can create copies without knowing the specific class." << endl;

    cout << "\n" << BHGRN << "Cloning the Rose:" << CRESET << endl;
    PlantComponent* roseClone = rose->clone();
    cout << "Rose clone created: " << roseClone->getName() << endl;
    cout << "Original price: $" << rose->getPrice() << " | Clone price: $" << roseClone->getPrice() << endl;
    createdPlants.push_back(roseClone);

    cout << "\n" << BHGRN << "Creating base plant types directly (Prototype bases):" << CRESET << endl;
    LivingPlant* succulent = new Succulent();
    cout << "1. Succulent base type created" << endl;

    LivingPlant* shrub = new Shrub();
    cout << "2. Shrub base type created" << endl;

    LivingPlant* tree = new Tree();
    cout << "3. Tree base type created" << endl;

    LivingPlant* herb = new Herb();
    cout << "4. Herb base type created" << endl;

    cout << "\n" << BHGRN << "Cloning base plant types:" << CRESET << endl;
    PlantComponent* succulentClone = succulent->clone();
    cout << "Succulent cloned successfully!" << endl;

    createdPlants.push_back(succulent);
    createdPlants.push_back(shrub);
    createdPlants.push_back(tree);
    createdPlants.push_back(herb);
    createdPlants.push_back(succulentClone);

    delete roseBuilder;
    delete sunflowerBuilder;
    delete cactusBuilder;

    cout << BHGRN << "\nBuilder/Prototype pattern demo completed!" << CRESET << endl;
    cout << "Press Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Demo 2: Singleton/Flyweight Pattern
void singletonFlyweightDemo()
{
    displayHeader("SINGLETON/FLYWEIGHT PATTERN DEMO");

    cout << BHYEL << "\n=== Demonstrating Singleton Pattern ===" << CRESET << endl;
    cout << "The Singleton pattern ensures only one instance of Inventory exists." << endl;
    cout << "All parts of the system share this single resource hub." << endl;

    cout << "\n" << BHGRN << "Accessing Inventory singleton:" << CRESET << endl;
    Inventory* inv1 = Inventory::getInstance();
    Inventory* inv2 = Inventory::getInstance();

    if (inv1 == inv2)
    {
        cout << "✓ Both references point to the SAME instance (address: " << inv1 << ")" << endl;
        cout << "✓ Singleton pattern ensures single global instance!" << endl;
    }

    cout << "\n" << BHYEL << "=== Demonstrating Flyweight Pattern ===" << CRESET << endl;
    cout << "The Flyweight pattern shares immutable objects to save memory." << endl;
    cout << "Strategies are cached and reused across multiple plants." << endl;

    cout << "\n" << BHGRN << "Getting Water Strategy flyweights:" << CRESET << endl;
    Flyweight<WaterStrategy*>* lowWater1 = inventory->getWaterFly(0);
    Flyweight<WaterStrategy*>* lowWater2 = inventory->getWaterFly(0);
    Flyweight<WaterStrategy*>* midWater = inventory->getWaterFly(1);
    Flyweight<WaterStrategy*>* highWater = inventory->getWaterFly(2);

    cout << "LowWater strategy 1 address: " << lowWater1->getState() << endl;
    cout << "LowWater strategy 2 address: " << lowWater2->getState() << endl;

    if (lowWater1->getState() == lowWater2->getState())
    {
        cout << "✓ Both references share the SAME LowWater strategy object!" << endl;
        cout << "✓ Flyweight pattern saves memory by sharing immutable objects!" << endl;
    }

    cout << "\nMidWater strategy address: " << midWater->getState() << endl;
    cout << "HighWater strategy address: " << highWater->getState() << endl;

    cout << "\n" << BHGRN << "Getting Sun Strategy flyweights:" << CRESET << endl;
    Flyweight<SunStrategy*>* lowSun = inventory->getSunFly(0);
    Flyweight<SunStrategy*>* midSun = inventory->getSunFly(1);
    Flyweight<SunStrategy*>* highSun = inventory->getSunFly(2);

    cout << "LowSun strategy address: " << lowSun->getState() << endl;
    cout << "MidSun strategy address: " << midSun->getState() << endl;
    cout << "HighSun strategy address: " << highSun->getState() << endl;

    cout << "\n" << BHGRN << "Memory Efficiency Demonstration:" << CRESET << endl;
    cout << "If we create 1000 plants with LowWater strategy:" << endl;
    cout << "Without Flyweight: 1000 separate strategy objects" << endl;
    cout << "With Flyweight: Only 1 shared strategy object!" << endl;
    cout << "Memory savings: ~99.9% for strategy objects!" << endl;

    cout << BHGRN << "\nSingleton/Flyweight pattern demo completed!" << CRESET << endl;
    cout << "Press Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Demo 3: Composite/Decorator Pattern
void compositeDecoratorDemo()
{
    displayHeader("COMPOSITE/DECORATOR PATTERN DEMO");

    cout << BHYEL << "\n=== Demonstrating Composite Pattern ===" << CRESET << endl;
    cout << "The Composite pattern organizes plants into tree structures." << endl;
    cout << "We can treat individual plants and groups uniformly." << endl;

    // Create individual plants
    cout << "\n" << BHGRN << "Creating individual plants:" << CRESET << endl;
    Builder* roseBuilder = new RoseBuilder();
    Director* director = new Director(roseBuilder);
    director->construct();
    PlantComponent* rose1 = director->getPlant();
    cout << "1. Rose created - Price: $" << rose1->getPrice() << endl;

    Builder* cactusBuilder = new CactusBuilder();
    director = new Director(cactusBuilder);
    director->construct();
    PlantComponent* cactus1 = director->getPlant();
    cout << "2. Cactus created - Price: $" << cactus1->getPrice() << endl;

    Builder* lavenderBuilder = new LavenderBuilder();
    director = new Director(lavenderBuilder);
    director->construct();
    PlantComponent* lavender1 = director->getPlant();
    cout << "3. Lavender created - Price: $" << lavender1->getPrice() << endl;

    // Create plant groups
    cout << "\n" << BHGRN << "Creating plant groups (Composite):" << CRESET << endl;
    PlantGroup* flowerGroup = new PlantGroup();
    flowerGroup->addComponent(rose1);
    flowerGroup->addComponent(lavender1);
    cout << "Flower group created with 2 plants" << endl;
    cout << "Total group price: $" << flowerGroup->getPrice() << endl;

    PlantGroup* succulentGroup = new PlantGroup();
    succulentGroup->addComponent(cactus1);
    cout << "Succulent group created with 1 plant" << endl;

    PlantGroup* mainInventory = new PlantGroup();
    mainInventory->addComponent(flowerGroup);
    mainInventory->addComponent(succulentGroup);
    cout << "\nMain inventory (root composite) created" << endl;
    cout << "Contains 2 groups with 3 total plants" << endl;
    cout << "Total inventory value: $" << mainInventory->getPrice() << endl;

    cout << "\n" << BHYEL << "=== Demonstrating Decorator Pattern ===" << CRESET << endl;
    cout << "The Decorator pattern adds features to plants dynamically." << endl;
    cout << "We can stack decorators to customize plants using addAttribute()." << endl;

    // Create a plain plant
    cout << "\n" << BHGRN << "Creating a plain Sunflower:" << CRESET << endl;
    Builder* sunflowerBuilder = new SunflowerBuilder();
    director = new Director(sunflowerBuilder);
    director->construct();
    PlantComponent* sunflower = director->getPlant();
    cout << "Sunflower with default decorators - Price: $" << sunflower->getPrice() << endl;

    // Add customer decorators using addAttribute
    cout << "\n" << BHGRN << "Adding customer decorators to sunflower:" << CRESET << endl;
    sunflower->addAttribute(new LargePot());
    cout << "Added LargePot - New price: $" << sunflower->getPrice() << endl;

    sunflower->addAttribute(new PlantCharm());
    cout << "Added PlantCharm - New price: $" << sunflower->getPrice() << endl;

    // Create another decorated plant
    cout << "\n" << BHGRN << "Creating and decorating a base plant:" << CRESET << endl;
    LivingPlant* baseTree = new Tree();
    cout << "Base Tree - Price: $" << baseTree->getPrice() << endl;

    baseTree->addAttribute(new Summer());
    cout << "Added Summer season - Price: $" << baseTree->getPrice() << endl;

    baseTree->addAttribute(new RedPot());
    cout << "Added RedPot - Price: $" << baseTree->getPrice() << endl;

    baseTree->addAttribute(new ShopThemedCharm());
    cout << "Added ShopThemedCharm - Price: $" << baseTree->getPrice() << endl;

    // Demonstrate stacking multiple plant decorators
    cout << "\n" << BHGRN << "Demonstrating plant attribute decorator stacking:" << CRESET << endl;
    LivingPlant* baseHerb = new Herb();
    cout << "Base Herb - Price: $" << baseHerb->getPrice() << endl;

    baseHerb->addAttribute(new Autumn());
    cout << "Added Autumn season - Price: $" << baseHerb->getPrice() << endl;

    baseHerb->addAttribute(new LargeLeaf());
    cout << "Added LargeLeaf - Price: $" << baseHerb->getPrice() << endl;

    baseHerb->addAttribute(new SmallFlowers());
    cout << "Added SmallFlowers - Price: $" << baseHerb->getPrice() << endl;

    baseHerb->addAttribute(new LargePot());
    cout << "Added LargePot - Final price: $" << baseHerb->getPrice() << endl;

    // Clean up builders
    delete roseBuilder;
    delete cactusBuilder;
    delete lavenderBuilder;
    delete sunflowerBuilder;

    // Store created items
    createdPlants.push_back(mainInventory);
    createdPlants.push_back(sunflower);
    createdPlants.push_back(baseTree);
    createdPlants.push_back(baseHerb);

    cout << BHGRN << "\nComposite/Decorator pattern demo completed!" << CRESET << endl;
    cout << "Press Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Demo 4: State/Strategy Pattern
void stateStrategyDemo()
{
    displayHeader("STATE/STRATEGY PATTERN DEMO");

    cout << BHYEL << "\n=== Demonstrating State Pattern ===" << CRESET << endl;
    cout << "The State pattern manages plant lifecycle transitions." << endl;
    cout << "Plants transition through: Seed → Vegetative → Mature → Dead" << endl;

    // Create a plant and show its lifecycle
    cout << "\n" << BHGRN << "Creating a Rose and tracking its lifecycle:" << CRESET << endl;
    Builder* roseBuilder = new RoseBuilder();
    Director* director = new Director(roseBuilder);
    director->construct();
    PlantComponent* rose = director->getPlant();
    LivingPlant* livingRose = dynamic_cast<LivingPlant*>(rose);

    cout << "Initial state: Seed" << endl;
    cout << "Age: " << livingRose->getAge() << " months" << endl;
    cout << "Health: " << livingRose->getHealth() << "%" << endl;

    cout << "\n" << BHGRN << "Simulating plant growth (State transitions):" << CRESET << endl;

    cout << "\nDay 30 - Watering and providing sunlight..." << endl;
    livingRose->water();
    livingRose->setOutside();
    livingRose->update();
    cout << "Age: " << livingRose->getAge() << " months" << endl;
    cout << "Water level: " << livingRose->getWaterLevel() << endl;
    cout << "Sun exposure: " << livingRose->getSunExposure() << endl;
    cout << "Health: " << livingRose->getHealth() << "%" << endl;

    cout << "\n" << BHYEL << "=== Demonstrating Strategy Pattern ===" << CRESET << endl;
    cout << "The Strategy pattern defines different care approaches." << endl;
    cout << "We can change water and sun strategies at runtime." << endl;

    // Create plants with different strategies
    cout << "\n" << BHGRN << "Creating plants with different water strategies:" << CRESET << endl;

    LivingPlant* plant1 = new Succulent();
    plant1->setWaterStrategy(0); // LowWater
    cout << "Plant 1: Succulent with LowWater strategy" << endl;

    LivingPlant* plant2 = new Shrub();
    plant2->setWaterStrategy(1); // MidWater
    cout << "Plant 2: Shrub with MidWater strategy" << endl;

    LivingPlant* plant3 = new Tree();
    plant3->setWaterStrategy(2); // HighWater
    cout << "Plant 3: Tree with HighWater strategy" << endl;

    cout << "\n" << BHGRN << "Applying water strategy to each plant:" << CRESET << endl;
    cout << "Before watering:" << endl;
    cout << "Plant 1 water level: " << plant1->getWaterLevel() << endl;
    cout << "Plant 2 water level: " << plant2->getWaterLevel() << endl;
    cout << "Plant 3 water level: " << plant3->getWaterLevel() << endl;

    plant1->water();
    plant2->water();
    plant3->water();

    cout << "\nAfter watering (different strategies apply different amounts):" << endl;
    cout << "Plant 1 water level: " << plant1->getWaterLevel() << " (LowWater)" << endl;
    cout << "Plant 2 water level: " << plant2->getWaterLevel() << " (MidWater)" << endl;
    cout << "Plant 3 water level: " << plant3->getWaterLevel() << " (HighWater)" << endl;

    cout << "\n" << BHGRN << "Creating plants with different sun strategies:" << CRESET << endl;

    LivingPlant* sunPlant1 = new Succulent();
    sunPlant1->setSunStrategy(0); // LowSun
    cout << "Sun Plant 1: Succulent with LowSun strategy" << endl;

    LivingPlant* sunPlant2 = new Herb();
    sunPlant2->setSunStrategy(1); // MidSun
    cout << "Sun Plant 2: Herb with MidSun strategy" << endl;

    LivingPlant* sunPlant3 = new Shrub();
    sunPlant3->setSunStrategy(2); // HighSun
    cout << "Sun Plant 3: Shrub with HighSun strategy" << endl;

    cout << "\n" << BHGRN << "Applying sun strategy to each plant:" << CRESET << endl;
    sunPlant1->setOutside();
    sunPlant2->setOutside();
    sunPlant3->setOutside();

    cout << "Sun Plant 1 exposure: " << sunPlant1->getSunExposure() << " (LowSun)" << endl;
    cout << "Sun Plant 2 exposure: " << sunPlant2->getSunExposure() << " (MidSun)" << endl;
    cout << "Sun Plant 3 exposure: " << sunPlant3->getSunExposure() << " (HighSun)" << endl;

    cout << "\n" << BHGRN << "Strategy pattern allows flexible behavior changes!" << CRESET << endl;
    cout << "We can swap strategies without changing the plant class." << endl;

    // Clean up
    delete roseBuilder;
    createdPlants.push_back(rose);
    createdPlants.push_back(plant1);
    createdPlants.push_back(plant2);
    createdPlants.push_back(plant3);
    createdPlants.push_back(sunPlant1);
    createdPlants.push_back(sunPlant2);
    createdPlants.push_back(sunPlant3);

    cout << BHGRN << "\nState/Strategy pattern demo completed!" << CRESET << endl;
    cout << "Press Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Demo 5: Observer/Mediator Pattern
void observerMediatorDemo()
{
    displayHeader("OBSERVER/MEDIATOR PATTERN DEMO");

    cout << BHYEL << "\n=== Demonstrating Observer Pattern ===" << CRESET << endl;
    cout << "The Observer pattern allows staff to monitor plant health." << endl;
    cout << "Staff members receive notifications when plants need care." << endl;

    // Create plant group and staff
    cout << "\n" << BHGRN << "Setting up nursery staff and plant monitoring:" << CRESET << endl;
    PlantGroup* monitoredPlants = new PlantGroup();

    Staff* staff1 = new Staff();
    Staff* staff2 = new Staff();
    cout << "Created 2 staff members" << endl;

    // Attach observers
    cout << "\n" << BHGRN << "Attaching staff as observers to plant group:" << CRESET << endl;
    monitoredPlants->attach(staff1);
    monitoredPlants->attach(staff2);
    cout << "Staff members now monitoring the plant group" << endl;

    // Create some plants
    Builder* roseBuilder = new RoseBuilder();
    Director* director = new Director(roseBuilder);
    director->construct();
    PlantComponent* rose = director->getPlant();

    Builder* cactusBuilder = new CactusBuilder();
    director = new Director(cactusBuilder);
    director->construct();
    PlantComponent* cactus = director->getPlant();

    monitoredPlants->addComponent(rose);
    monitoredPlants->addComponent(cactus);
    cout << "Added Rose and Cactus to monitored group" << endl;

    cout << "\n" << BHGRN << "Triggering notifications (Observer pattern in action):" << CRESET << endl;
    cout << "Plants need water - notifying all observers..." << endl;
    monitoredPlants->waterNeeded();
    cout << "✓ All staff members notified!" << endl;

    cout << "\nPlants need sunlight - notifying all observers..." << endl;
    monitoredPlants->sunlightNeeded();
    cout << "✓ All staff members notified!" << endl;

    cout << "\nPlant state updated - notifying all observers..." << endl;
    monitoredPlants->stateUpdated();
    cout << "✓ All staff members notified!" << endl;

    cout << "\n" << BHYEL << "=== Demonstrating Mediator Pattern ===" << CRESET << endl;
    cout << "The Mediator pattern coordinates customer-staff interactions." << endl;
    cout << "Customers and staff communicate through mediator objects." << endl;

    // Create mediators
    cout << "\n" << BHGRN << "Setting up sales floor and suggestion floor mediators:" << CRESET << endl;
    SalesFloor* salesFloor = new SalesFloor();
    SuggestionFloor* suggestionFloor = new SuggestionFloor();
    cout << "Sales floor and suggestion floor created" << endl;

    // Create customers
    cout << "\n" << BHGRN << "Creating customers:" << CRESET << endl;
    Customer* customer1 = new Customer();
    Customer* customer2 = new Customer();
    cout << "Created 2 customers" << endl;

    // Register users with mediators
    cout << "\n" << BHGRN << "Registering users with mediators:" << CRESET << endl;
    cout << "Customer 1 joining sales floor..." << endl;
    cout << "Customer 2 joining suggestion floor..." << endl;
    cout << "Staff joining both floors..." << endl;

    cout << "\n" << BHGRN << "Customer interactions through mediators:" << CRESET << endl;
    cout << "Customer 1 requesting assistance on sales floor..." << endl;
    cout << "✓ Mediator coordinating customer-staff communication!" << endl;

    cout << "\nCustomer 2 asking for plant care suggestions..." << endl;
    cout << "✓ Mediator routing request to knowledgeable staff!" << endl;

    cout << "\n" << BHGRN << "Benefits of Mediator pattern:" << CRESET << endl;
    cout << "- Customers and staff don't know about each other" << endl;
    cout << "- Mediator handles all coordination logic" << endl;
    cout << "- Easy to add new interaction types" << endl;
    cout << "- Reduces coupling between colleagues" << endl;

    // Clean up
    delete roseBuilder;
    delete cactusBuilder;
    createdPlants.push_back(monitoredPlants);
    staffMembers.push_back(staff1);
    staffMembers.push_back(staff2);
    customers.push_back(customer1);
    customers.push_back(customer2);
    delete salesFloor;
    delete suggestionFloor;

    cout << BHGRN << "\nObserver/Mediator pattern demo completed!" << CRESET << endl;
    cout << "Press Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Demo 6: Iterator Pattern
void iteratorDemo()
{
    displayHeader("ITERATOR PATTERN DEMO");

    cout << BHYEL << "\n=== Demonstrating Iterator Pattern ===" << CRESET << endl;
    cout << "The Iterator pattern provides sequential access to collections." << endl;
    cout << "We can traverse plant collections without exposing structure." << endl;

    // Create plants with different seasons
    cout << "\n" << BHGRN << "Creating seasonal plant inventory:" << CRESET << endl;
    PlantGroup* seasonalInventory = new PlantGroup();

    // Spring plants
    LivingPlant* springPlant1 = new Shrub();
    PlantComponent* season1 = new Spring();
    springPlant1->setSeason(inventory->getString(season1->getName()));
    springPlant1->addAttribute(season1);
    seasonalInventory->addComponent(springPlant1);
    cout << "Added Spring plant 1 (Shrub with Spring decorator)" << endl;

    LivingPlant* springPlant2 = new Herb();
    PlantComponent* season2 = new Spring();
    springPlant2->setSeason(inventory->getString(season2->getName()));
    springPlant2->addAttribute(season2);
    seasonalInventory->addComponent(springPlant2);
    cout << "Added Spring plant 2 (Herb with Spring decorator)" << endl;

    // Summer plants
    LivingPlant* summerPlant1 = new Succulent();
    PlantComponent* season3 = new Summer();
    summerPlant1->setSeason(inventory->getString(season3->getName()));
    summerPlant1->addAttribute(season3);
    seasonalInventory->addComponent(summerPlant1);
    cout << "Added Summer plant 1 (Succulent with Summer decorator)" << endl;

    LivingPlant* summerPlant2 = new Tree();
    PlantComponent* season4 = new Summer();
    summerPlant2->setSeason(inventory->getString(season4->getName()));
    summerPlant2->addAttribute(season4);
    seasonalInventory->addComponent(summerPlant2);
    cout << "Added Summer plant 2 (Tree with Summer decorator)" << endl;

    // Autumn plants
    LivingPlant* autumnPlant1 = new Tree();
    PlantComponent* season5 = new Autumn();
    autumnPlant1->setSeason(inventory->getString(season5->getName()));
    autumnPlant1->addAttribute(season5);
    seasonalInventory->addComponent(autumnPlant1);
    cout << "Added Autumn plant 1 (Tree with Autumn decorator)" << endl;

    // Winter plants
    LivingPlant* winterPlant1 = new Shrub();
    PlantComponent* season6 = new Winter();
    winterPlant1->setSeason(inventory->getString(season6->getName()));
    winterPlant1->addAttribute(season6);
    seasonalInventory->addComponent(winterPlant1);
    cout << "Added Winter plant 1 (Shrub with Winter decorator)" << endl;

    cout << "\nTotal plants in inventory: 6" << endl;
    cout << "Spring: 2, Summer: 2, Autumn: 1, Winter: 1" << endl;

    // Iterate through all plants
    cout << "\n" << BHGRN << "Iterating through ALL plants:" << CRESET << endl;
    AggPlant* allPlantsAgg = new AggPlant(seasonalInventory->getPlants());
    Iterator* allIterator = allPlantsAgg->createIterator();

    int count = 0;
    for (allIterator->first(); !allIterator->isDone(); allIterator->next())
    {
        count++;
        LivingPlant* plant = allIterator->currentItem();
        if (plant)
        {
            cout << count << ". " << plant->getName() << " (Season: " << *plant->getSeason()->getState() << ")" << endl;
        }
    }
    delete allIterator;
    delete allPlantsAgg;

    // Iterate through Spring plants only
    cout << "\n" << BHGRN << "Filtering for SPRING plants only:" << CRESET << endl;
    AggSeason* springAgg = new AggSeason(seasonalInventory->getPlants(), "Spring");
    Iterator* springIterator = springAgg->createIterator();

    count = 0;
    for (springIterator->first(); !springIterator->isDone(); springIterator->next())
    {
        count++;
        LivingPlant* plant = springIterator->currentItem();
        if (plant)
        {
            cout << count << ". " << plant->getName() << endl;
        }
    }
    delete springIterator;
    delete springAgg;

    // Iterate through Summer plants only
    cout << "\n" << BHGRN << "Filtering for SUMMER plants only:" << CRESET << endl;
    AggSeason* summerAgg = new AggSeason(seasonalInventory->getPlants(), "Summer");
    Iterator* summerIterator = summerAgg->createIterator();

    count = 0;
    for (summerIterator->first(); !summerIterator->isDone(); summerIterator->next())
    {
        count++;
        LivingPlant* plant = summerIterator->currentItem();
        if (plant)
        {
            cout << count << ". " << plant->getName() << endl;
        }
    }
    delete summerIterator;
    delete summerAgg;

    // Iterate through Autumn plants only
    cout << "\n" << BHGRN << "Filtering for AUTUMN plants only:" << CRESET << endl;
    AggSeason* autumnAgg = new AggSeason(seasonalInventory->getPlants(), "Autumn");
    Iterator* autumnIterator = autumnAgg->createIterator();

    count = 0;
    for (autumnIterator->first(); !autumnIterator->isDone(); autumnIterator->next())
    {
        count++;
        LivingPlant* plant = autumnIterator->currentItem();
        if (plant)
        {
            cout << count << ". " << plant->getName() << endl;
        }
    }
    delete autumnIterator;
    delete autumnAgg;

    // Iterate through Winter plants only
    cout << "\n" << BHGRN << "Filtering for WINTER plants only:" << CRESET << endl;
    AggSeason* winterAgg = new AggSeason(seasonalInventory->getPlants(), "Winter");
    Iterator* winterIterator = winterAgg->createIterator();

    count = 0;
    for (winterIterator->first(); !winterIterator->isDone(); winterIterator->next())
    {
        count++;
        LivingPlant* plant = winterIterator->currentItem();
        if (plant)
        {
            cout << count << ". " << plant->getName() << endl;
        }
    }
    delete winterIterator;
    delete winterAgg;

    cout << "\n" << BHGRN << "Iterator pattern benefits:" << CRESET << endl;
    cout << "- Traverses collections without exposing internal structure" << endl;
    cout << "- Supports multiple simultaneous traversals" << endl;
    cout << "- Provides uniform interface for different collections" << endl;
    cout << "- SeasonIterator filters plants by season efficiently" << endl;

    createdPlants.push_back(seasonalInventory);

    cout << BHGRN << "\nIterator pattern demo completed!" << CRESET << endl;
    cout << "Press Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Demo 7: Complete Interactive Demo
void completeInteractiveDemo()
{
    displayHeader("COMPLETE INTERACTIVE NURSERY DEMO");

    cout << BHYEL << "\n=== Welcome to Interactive Photosyntech Nursery! ===" << CRESET << endl;
    cout << "This demo combines all design patterns in a realistic scenario." << endl;

    bool running = true;
    PlantGroup* nurseryInventory = inventory->getInventory();

    while (running)
    {
        cout << "\n" << BHWHT << "Interactive Nursery Menu:" << CRESET << endl;
        cout << "1. Create new plant (Builder)" << endl;
        cout << "2. Clone existing plant (Prototype)" << endl;
        cout << "3. Add decorations to plant (Decorator)" << endl;
        cout << "4. Water plants (Strategy)" << endl;
        cout << "5. View inventory by season (Iterator)" << endl;
        cout << "6. View all plants (Composite)" << endl;
        cout << "7. Create customer (Mediator)" << endl;
        cout << "8. Assign staff observer (Observer)" << endl;
        cout << "9. Return to main menu" << endl;

        int choice = getValidInput(1, 9);

        switch (choice)
        {
        case 1:
        {
            cout << "\nSelect plant type to build:" << endl;
            cout << "1. Rose  2. Sunflower  3. Cactus  4. Pine  5. Maple" << endl;
            int plantChoice = getValidInput(1, 5);

            Builder* builder = nullptr;
            switch (plantChoice)
            {
                case 1: builder = new RoseBuilder(); break;
                case 2: builder = new SunflowerBuilder(); break;
                case 3: builder = new CactusBuilder(); break;
                case 4: builder = new PineBuilder(); break;
                case 5: builder = new MapleBuilder(); break;
            }

            Director* director = new Director(builder);
            director->construct();
            PlantComponent* newPlant = director->getPlant();
            nurseryInventory->addComponent(newPlant);

            cout << BHGRN << "✓ Plant created and added to inventory!" << CRESET << endl;
            cout << "Name: " << newPlant->getName() << ", Price: $" << newPlant->getPrice() << endl;

            delete builder;
            break;
        }
        case 2:
        {
            if (nurseryInventory->getPlants()->empty())
            {
                cout << BHRED << "No plants to clone! Create a plant first." << CRESET << endl;
                break;
            }

            PlantComponent* firstPlant = nurseryInventory->getPlants()->front();
            PlantComponent* clonedPlant = firstPlant->clone();
            nurseryInventory->addComponent(clonedPlant);

            cout << BHGRN << "✓ Plant cloned successfully!" << CRESET << endl;
            break;
        }
        case 3:
        {
            cout << "\nSelect decoration type:" << endl;
            cout << "1. Large Pot  2. Red Pot  3. Plant Charm  4. Change Season" << endl;
            int decorChoice = getValidInput(1, 4);

            cout << "This feature requires selecting a specific plant from inventory." << endl;
            cout << BHYEL << "In a full implementation, you'd select which plant to decorate." << CRESET << endl;
            break;
        }
        case 4:
        {
            cout << BHGRN << "Watering all plants in nursery..." << CRESET << endl;
            nurseryInventory->water();
            cout << "✓ All plants watered using their respective strategies!" << endl;
            break;
        }
        case 5:
        {
            cout << "\nSelect season to view:" << endl;
            cout << "1. Spring  2. Summer  3. Autumn  4. Winter" << endl;
            int seasonChoice = getValidInput(1, 4);

            string season;
            switch (seasonChoice)
            {
                case 1: season = "Spring"; break;
                case 2: season = "Summer"; break;
                case 3: season = "Autumn"; break;
                case 4: season = "Winter"; break;
            }

            cout << BHGRN << "\nFiltering inventory for " << season << " plants:" << CRESET << endl;
            AggSeason* seasonAgg = new AggSeason(nurseryInventory->getPlants(), season);
            Iterator* seasonIterator = seasonAgg->createIterator();

            int count = 0;
            for (seasonIterator->first(); !seasonIterator->isDone(); seasonIterator->next())
            {
                LivingPlant* plant = seasonIterator->currentItem();
                if (plant)
                {
                    count++;
                    cout << count << ". " << plant->getName() << " - $" << plant->getPrice() << endl;
                }
            }

            if (count == 0)
            {
                cout << "No " << season << " plants found." << endl;
            }

            delete seasonIterator;
            delete seasonAgg;
            break;
        }
        case 6:
        {
            cout << BHGRN << "\nAll plants in nursery inventory:" << CRESET << endl;
            cout << nurseryInventory->getInfo() << endl;
            cout << "Total inventory value: $" << nurseryInventory->getPrice() << endl;
            break;
        }
        case 7:
        {
            Customer* newCustomer = new Customer();
            customers.push_back(newCustomer);
            cout << BHGRN << "✓ New customer created!" << CRESET << endl;
            cout << "Total customers: " << customers.size() << endl;
            break;
        }
        case 8:
        {
            Staff* newStaff = new Staff();
            nurseryInventory->attach(newStaff);
            staffMembers.push_back(newStaff);
            cout << BHGRN << "✓ Staff member assigned as observer!" << CRESET << endl;
            cout << "Total staff: " << staffMembers.size() << endl;
            break;
        }
        case 9:
            running = false;
            break;
        }
    }

    cout << BHGRN << "\nComplete interactive demo finished!" << CRESET << endl;
    cout << "Press Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Demo 8: View System Status
void viewSystemStatus()
{
    displayHeader("SYSTEM STATUS");

    cout << BHYEL << "=== Global Inventory (Singleton) ===" << CRESET << endl;
    PlantGroup* mainInventory = inventory->getInventory();
    cout << "Inventory address: " << inventory << endl;
    cout << "Total plants in inventory: " << mainInventory->getPlants()->size() << endl;
    cout << "Total inventory value: $" << mainInventory->getPrice() << endl;

    cout << "\n" << BHYEL << "=== Flyweight Factory Statistics ===" << CRESET << endl;
    cout << "Water strategies cached: 4 (Low, Mid, High, Alternating)" << endl;
    cout << "Sun strategies cached: 4 (Low, Mid, High, Alternating)" << endl;
    cout << "Memory efficiency: Strategies shared across all plants" << endl;

    cout << "\n" << BHYEL << "=== Created Plants ===" << CRESET << endl;
    cout << "Total plants created in demos: " << createdPlants.size() << endl;

    cout << "\n" << BHYEL << "=== Customers ===" << CRESET << endl;
    cout << "Total customers: " << customers.size() << endl;

    cout << "\n" << BHYEL << "=== Staff Members ===" << CRESET << endl;
    cout << "Total staff: " << staffMembers.size() << endl;

    cout << "\n" << BHYEL << "=== Design Patterns Demonstrated ===" << CRESET << endl;
    cout << "✓ Builder - Complex plant construction" << endl;
    cout << "✓ Prototype - Plant cloning" << endl;
    cout << "✓ Singleton - Global inventory management" << endl;
    cout << "✓ Flyweight - Shared strategy objects" << endl;
    cout << "✓ Composite - Hierarchical plant grouping" << endl;
    cout << "✓ Decorator - Dynamic plant customization" << endl;
    cout << "✓ State - Plant lifecycle management" << endl;
    cout << "✓ Strategy - Flexible care algorithms" << endl;
    cout << "✓ Observer - Staff monitoring system" << endl;
    cout << "✓ Mediator - Customer-staff coordination" << endl;
    cout << "✓ Iterator - Seasonal filtering" << endl;

    cout << "\nPress Enter to continue...";
    clearInputBuffer();
    cin.get();
}

// Cleanup function
void cleanup()
{
    cout << BHYEL << "\nCleaning up resources..." << CRESET << endl;

    // Clean up created plants
    for (PlantComponent* plant : createdPlants)
    {
        delete plant;
    }
    createdPlants.clear();

    // Clean up customers
    for (Customer* customer : customers)
    {
        delete customer;
    }
    customers.clear();

    // Clean up staff
    for (Staff* staff : staffMembers)
    {
        delete staff;
    }
    staffMembers.clear();

    cout << BHGRN << "Cleanup completed!" << CRESET << endl;
}
