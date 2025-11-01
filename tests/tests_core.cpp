#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../facade/NurseryFacade.h"
// This file will include all individual test files.
// As tests are migrated, their files will be included here.

#include "builder_tests.cpp"   //Passing
#include "composite_tests.cpp" //Passing - removed for merge
#include "decorator_tests.cpp" //Passing
// #include "facade_tests.cpp" //Passing - finally - removed for merge
#include "flyweight_tests.cpp" //Passing
#include "iterator_tests.cpp"  //Passing
#include "mediator_tests.cpp"  //Passing
#include "observer_tests.cpp"  //Passing
#include "prototype_tests.cpp" //Passing
#include "singleton_tests.cpp" //Passing
#include "strategy_tests.cpp"  //Passing
#include "state_tests.cpp"     //Passing

TEST_CASE("Testing nursery function")
{
    NurseryFacade *fac = new NurseryFacade;
    fac->createPlant("Sunflower");
    fac->createPlant("Rose");
    fac->createPlant("Rose");
    /*
    fac.createPlant("Sunflower");
     fac.createPlant("Sunflower");
     vector<string> vec = fac.getAllPlantGroups();

 */
    delete fac;

    delete Inventory::getInstance();
}
TEST_CASE("Testing nursery function")
{
    NurseryFacade *fac = new NurseryFacade;
    PlantGroup *pg = new PlantGroup();
    Staff *staf = new Staff("jerry");
    pg->attach(staf);
    fac->getObservers(pg);

    delete pg;
    delete staf;
    delete fac;
    delete Inventory::getInstance();
}
TEST_CASE("Testing nursery function")
{

    Builder *si = new SunflowerBuilder();
    Director *dir = new Director(si);
    dir->construct();
    Inventory::getInstance()->getInventory()->addComponent(dir->getPlant());
    Inventory::getInstance()->getInventory()->addComponent(dir->getPlant());
    Inventory::getInstance()->getInventory()->addComponent(dir->getPlant());
    NurseryFacade *fac = new NurseryFacade;
    fac->createItr();
    while (fac->next())
    {

    }
    

    delete fac;
    delete Inventory::getInstance();
}