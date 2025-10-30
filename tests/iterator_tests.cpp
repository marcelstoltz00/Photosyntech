#include "doctest.h"
#include "iterator/Iterator.h"
#include "iterator/PlantIterator.h"
#include "iterator/SeasonIterator.h"
#include "iterator/AggPlant.h"
#include "iterator/AggSeason.h"
#include "composite/PlantGroup.h"
#include "prototype/Succulent.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Herb.h"
#include "singleton/Singleton.h"
#include <vector>
#include <list>

// ============================================================================
// TEST HELPER FUNCTIONS
// ============================================================================

int countIteratorResults(Iterator *iter)
{
    int count = 0;
    iter->first();
    while (!iter->isDone()) {
        count++;
        iter->next();
    }
    return count;
}

std::vector<LivingPlant *> collectPlants(Iterator *iter)
{
    std::vector<LivingPlant *> plants;
    iter->first();
    while (!iter->isDone()) {
        plants.push_back(iter->currentItem());
        iter->next();
    }
    return plants;
}

LivingPlant *createPlantWithSeason(const std::string &season)
{
    Inventory *inv = Inventory::getInstance();
    LivingPlant *plant = new Succulent();
    plant->setSeason(inv->getString(season));
    return plant;
}

// ============================================================================
// PLANTITERATOR BASIC TESTS
// ============================================================================

TEST_CASE("PlantIterator - Empty collection")
{
    SUBCASE("isDone() returns true immediately for empty collection")
    {
        std::list<PlantComponent *> emptyList;
        AggPlant *agg = new AggPlant(&emptyList);
        Iterator *iter = agg->createIterator();

        CHECK(iter->isDone() == true);

        delete iter;
        delete agg;
    }

    SUBCASE("currentItem() returns nullptr for empty collection")
    {
        std::list<PlantComponent *> emptyList;
        AggPlant *agg = new AggPlant(&emptyList);
        Iterator *iter = agg->createIterator();

        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
    }
    delete Inventory::getInstance();
}

TEST_CASE("PlantIterator - Single plant")
{
    SUBCASE("first() positions at the plant")
    {
        Inventory *inv = Inventory::getInstance();
        LivingPlant *plant = new Succulent();
        plant->setSeason(inv->getString("Spring"));

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->isDone() == false);
        CHECK(iter->currentItem() == plant);

        delete iter;
        delete agg;
        delete plant;
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

TEST_CASE("PlantIterator - Multiple plants in flat list")
{
    SUBCASE("Iteration returns all plants in order")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = new Succulent();
        plant1->setSeason(inv->getString("Spring"));
        LivingPlant *plant2 = new Tree();
        plant2->setSeason(inv->getString("Summer"));
        LivingPlant *plant3 = new Shrub();
        plant3->setSeason(inv->getString("Autumn"));

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        CHECK(countIteratorResults(iter) == 3);

        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 3);
        CHECK(collected[0] == plant1);
        CHECK(collected[1] == plant2);
        CHECK(collected[2] == plant3);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

// ============================================================================
// SEASONITERATOR BASIC TESTS
// ============================================================================

TEST_CASE("SeasonIterator - Empty collection with season filter")
{
    SUBCASE("Empty collection returns no items")
    {
        Inventory *inv = Inventory::getInstance();
        std::list<PlantComponent *> emptyList;

        AggSeason *agg = new AggSeason(&emptyList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

TEST_CASE("SeasonIterator - Single matching plant")
{
    SUBCASE("Returns the matching plant")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant = createPlantWithSeason("Spring");
        std::list<PlantComponent *> plantList;
        plantList.push_back(plant);

        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->isDone() == false);
        CHECK(iter->currentItem() == plant);

        delete iter;
        delete agg;
        delete plant;
        delete Inventory::getInstance();
    }

}

TEST_CASE("SeasonIterator - Mixed seasons with filtering")
{
    SUBCASE("Filter for Spring returns only Spring plants")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *spring1 = createPlantWithSeason("Spring");
        LivingPlant *summer1 = createPlantWithSeason("Summer");
        LivingPlant *spring2 = createPlantWithSeason("Spring");
        LivingPlant *autumn1 = createPlantWithSeason("Autumn");

        std::list<PlantComponent *> plantList;
        plantList.push_back(spring1);
        plantList.push_back(summer1);
        plantList.push_back(spring2);
        plantList.push_back(autumn1);

        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 2);
        CHECK(collected[0] == spring1);
        CHECK(collected[1] == spring2);

        delete iter;
        delete agg;
        delete spring1;
        delete summer1;
        delete spring2;
        delete autumn1;
        delete Inventory::getInstance();
    }
}

// ============================================================================
// SEASONITERATOR FLYWEIGHT IMPLEMENTATION TESTS
// ============================================================================

TEST_CASE("SeasonIterator - Flyweight pointer comparison")
{
    SUBCASE("Same season string yields same Flyweight pointer")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<std::string *> *season1 = inv->getString("Spring");
        Flyweight<std::string *> *season2 = inv->getString("Spring");

        CHECK(season1 == season2);

        delete Inventory::getInstance();
    }

    SUBCASE("Different season strings yield different Flyweight pointers")
    {
        Inventory *inv = Inventory::getInstance();

        Flyweight<std::string *> *spring = inv->getString("Spring");
        Flyweight<std::string *> *summer = inv->getString("Summer");

        CHECK(spring != summer);

        delete Inventory::getInstance();
    }
}

// ============================================================================
// ITERATOR BEHAVIOR CONTRACT TESTS
// ============================================================================

TEST_CASE("Iterator behavior - first() resets iterator")
{
    SUBCASE("first() called twice positions at beginning both times")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Spring");
        LivingPlant *plant3 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->currentItem() == plant1);
        iter->first();
        CHECK(iter->currentItem() == plant1);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }
}

TEST_CASE("Iterator behavior - next() at end stays at end")
{
    SUBCASE("Calling next() multiple times at end maintains isDone() true")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant = createPlantWithSeason("Spring");
        std::list<PlantComponent *> plantList;
        plantList.push_back(plant);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        iter->next();
        CHECK(iter->isDone() == true);

        iter->next();
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
        delete plant;
        delete Inventory::getInstance();
    }
}

TEST_CASE("Iterator behavior - currentItem() doesn't advance iterator")
{
    SUBCASE("Multiple currentItem() calls return same item")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        LivingPlant *item1 = iter->currentItem();
        LivingPlant *item2 = iter->currentItem();
        LivingPlant *item3 = iter->currentItem();

        CHECK(item1 == plant1);
        CHECK(item2 == plant1);
        CHECK(item3 == plant1);
        CHECK(iter->isDone() == false);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete Inventory::getInstance();
    }
}

// ============================================================================
// COMPARISON TESTS: PlantIterator vs SeasonIterator
// ============================================================================

TEST_CASE("PlantIterator vs SeasonIterator comparison")
{
    SUBCASE("SeasonIterator count <= PlantIterator count")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *spring1 = createPlantWithSeason("Spring");
        LivingPlant *spring2 = createPlantWithSeason("Spring");
        LivingPlant *summer1 = createPlantWithSeason("Summer");
        LivingPlant *summer2 = createPlantWithSeason("Summer");
        LivingPlant *autumn1 = createPlantWithSeason("Autumn");

        std::list<PlantComponent *> plantList;
        plantList.push_back(spring1);
        plantList.push_back(summer1);
        plantList.push_back(spring2);
        plantList.push_back(summer2);
        plantList.push_back(autumn1);

        AggPlant *aggAll = new AggPlant(&plantList);
        Iterator *iterAll = aggAll->createIterator();
        int allCount = countIteratorResults(iterAll);

        AggSeason *aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iterSpring = aggSpring->createIterator();
        int springCount = countIteratorResults(iterSpring);

        CHECK(springCount <= allCount);
        CHECK(springCount == 2);
        CHECK(allCount == 5);

        delete iterAll;
        delete aggAll;
        delete iterSpring;
        delete aggSpring;
        delete spring1;
        delete spring2;
        delete summer1;
        delete summer2;
        delete autumn1;
        delete Inventory::getInstance();
    }
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

TEST_CASE("Edge case - Multiple iterators on same collection are independent")
{
    SUBCASE("Two iterators maintain independent positions")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Spring");
        LivingPlant *plant3 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter1 = agg->createIterator();
        Iterator *iter2 = agg->createIterator();

        iter1->first();
        iter1->next();
        CHECK(iter1->currentItem() == plant2);

        iter2->first();
        CHECK(iter2->currentItem() == plant1);

        delete iter1;
        delete iter2;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }
}

TEST_CASE("Edge case - Iterator doesn't modify collection")
{
    SUBCASE("Collection remains unchanged after iteration")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);

        size_t originalSize = plantList.size();

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        countIteratorResults(iter);

        CHECK(plantList.size() == originalSize);
        CHECK(plantList.front() == plant1);
        CHECK(plantList.back() == plant2);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete Inventory::getInstance();
    }
}

TEST_CASE("Edge case - All plants same season")
{
    SUBCASE("Filtering for that season returns all")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Spring");
        LivingPlant *plant3 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 3);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }

    SUBCASE("Filtering for different season returns none")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);

        AggSeason *agg = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 0);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

TEST_CASE("Edge case - Each plant different season")
{
    SUBCASE("PlantIterator returns all 4")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *spring = createPlantWithSeason("Spring");
        LivingPlant *summer = createPlantWithSeason("Summer");
        LivingPlant *autumn = createPlantWithSeason("Autumn");
        LivingPlant *winter = createPlantWithSeason("Winter");

        std::list<PlantComponent *> plantList;
        plantList.push_back(spring);
        plantList.push_back(summer);
        plantList.push_back(autumn);
        plantList.push_back(winter);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 4);

        delete iter;
        delete agg;
        delete spring;
        delete summer;
        delete autumn;
        delete winter;
        delete Inventory::getInstance();
    }

    SUBCASE("Each season filter returns exactly 1")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *spring = createPlantWithSeason("Spring");
        LivingPlant *summer = createPlantWithSeason("Summer");
        LivingPlant *autumn = createPlantWithSeason("Autumn");
        LivingPlant *winter = createPlantWithSeason("Winter");

        std::list<PlantComponent *> plantList;
        plantList.push_back(spring);
        plantList.push_back(summer);
        plantList.push_back(autumn);
        plantList.push_back(winter);

        AggSeason *aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iterSpring = aggSpring->createIterator();
        CHECK(countIteratorResults(iterSpring) == 1);
        delete iterSpring;
        delete aggSpring;

        delete spring;
        delete summer;
        delete autumn;
        delete winter;
        delete Inventory::getInstance();
    }
    delete Inventory::getInstance();
}

// ============================================================================
// BACK() FUNCTIONALITY TESTS - PlantIterator
// ============================================================================

TEST_CASE("PlantIterator - back() basic functionality")
{
    SUBCASE("back() moves to previous plant in flat list")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Summer");
        LivingPlant *plant3 = createPlantWithSeason("Autumn");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        iter->next();  // Now at plant2
        CHECK(iter->currentItem() == plant2);

        iter->back();  // Should move back to plant1
        CHECK(iter->currentItem() == plant1);
        CHECK(iter->isDone() == false);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }

    SUBCASE("back() at first position stays at beginning")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Summer");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->currentItem() == plant1);

        iter->back();  // Should handle gracefully at beginning
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete Inventory::getInstance();
    }
}

TEST_CASE("PlantIterator - back() traversing entire list backwards")
{
    SUBCASE("Can traverse from end to beginning using back()")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Summer");
        LivingPlant *plant3 = createPlantWithSeason("Autumn");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        // Go to end
        iter->first();
        while (!iter->isDone()) {
            iter->next();
        }

        // Now traverse backwards
        iter->back();
        CHECK(iter->currentItem() == plant3);

        iter->back();
        CHECK(iter->currentItem() == plant2);

        iter->back();
        CHECK(iter->currentItem() == plant1);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }
}

TEST_CASE("PlantIterator - bidirectional navigation")
{
    SUBCASE("Alternating next() and back() maintains correct position")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Summer");
        LivingPlant *plant3 = createPlantWithSeason("Autumn");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->currentItem() == plant1);

        iter->next();
        CHECK(iter->currentItem() == plant2);

        iter->next();
        CHECK(iter->currentItem() == plant3);

        iter->back();
        CHECK(iter->currentItem() == plant2);

        iter->next();
        CHECK(iter->currentItem() == plant3);

        iter->back();
        CHECK(iter->currentItem() == plant2);

        iter->back();
        CHECK(iter->currentItem() == plant1);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }
}

// ============================================================================
// BACK() FUNCTIONALITY TESTS - SeasonIterator
// ============================================================================

TEST_CASE("SeasonIterator - back() with filtering")
{
    SUBCASE("back() moves to previous matching plant, skipping non-matches")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *spring1 = createPlantWithSeason("Spring");
        LivingPlant *summer1 = createPlantWithSeason("Summer");
        LivingPlant *spring2 = createPlantWithSeason("Spring");
        LivingPlant *autumn1 = createPlantWithSeason("Autumn");
        LivingPlant *spring3 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(spring1);
        plantList.push_back(summer1);
        plantList.push_back(spring2);
        plantList.push_back(autumn1);
        plantList.push_back(spring3);

        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        // Collect all Spring plants forward
        std::vector<LivingPlant *> forward = collectPlants(iter);
        CHECK(forward.size() == 3);
        CHECK(forward[0] == spring1);
        CHECK(forward[1] == spring2);
        CHECK(forward[2] == spring3);

        // Now traverse backwards
        iter->back();
        CHECK(iter->currentItem() == spring3);

        iter->back();
        CHECK(iter->currentItem() == spring2);

        iter->back();
        CHECK(iter->currentItem() == spring1);

        delete iter;
        delete agg;
        delete spring1;
        delete summer1;
        delete spring2;
        delete autumn1;
        delete spring3;
        delete Inventory::getInstance();
    }

    SUBCASE("back() returns nullptr when no previous matching plant")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *summer1 = createPlantWithSeason("Summer");
        LivingPlant *spring1 = createPlantWithSeason("Spring");
        LivingPlant *summer2 = createPlantWithSeason("Summer");

        std::list<PlantComponent *> plantList;
        plantList.push_back(summer1);
        plantList.push_back(spring1);
        plantList.push_back(summer2);

        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->currentItem() == spring1);

        iter->back();  // No previous Spring plant
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
        delete summer1;
        delete spring1;
        delete summer2;
        delete Inventory::getInstance();
    }
}

TEST_CASE("SeasonIterator - bidirectional navigation with filtering")
{
    SUBCASE("next() and back() work correctly with season filtering")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *spring1 = createPlantWithSeason("Spring");
        LivingPlant *summer1 = createPlantWithSeason("Summer");
        LivingPlant *spring2 = createPlantWithSeason("Spring");
        LivingPlant *summer2 = createPlantWithSeason("Summer");
        LivingPlant *spring3 = createPlantWithSeason("Spring");

        std::list<PlantComponent *> plantList;
        plantList.push_back(spring1);
        plantList.push_back(summer1);
        plantList.push_back(spring2);
        plantList.push_back(summer2);
        plantList.push_back(spring3);

        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->currentItem() == spring1);

        iter->next();
        CHECK(iter->currentItem() == spring2);

        iter->next();
        CHECK(iter->currentItem() == spring3);

        iter->back();
        CHECK(iter->currentItem() == spring2);

        iter->back();
        CHECK(iter->currentItem() == spring1);

        iter->next();
        CHECK(iter->currentItem() == spring2);

        delete iter;
        delete agg;
        delete spring1;
        delete summer1;
        delete spring2;
        delete summer2;
        delete spring3;
        delete Inventory::getInstance();
    }
}

// ============================================================================
// BACK() EDGE CASE TESTS
// ============================================================================

TEST_CASE("Edge case - back() on empty collection")
{
    SUBCASE("back() on empty collection handles gracefully")
    {
        std::list<PlantComponent *> emptyList;
        AggPlant *agg = new AggPlant(&emptyList);
        Iterator *iter = agg->createIterator();

        CHECK(iter->isDone() == true);
        iter->back();
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
    }
}

TEST_CASE("Edge case - back() on single element")
{
    SUBCASE("back() on single element collection")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant = createPlantWithSeason("Spring");
        std::list<PlantComponent *> plantList;
        plantList.push_back(plant);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        CHECK(iter->currentItem() == plant);

        iter->back();
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
        delete plant;
        delete Inventory::getInstance();
    }
}

TEST_CASE("Edge case - Multiple back() calls at beginning")
{
    SUBCASE("Multiple back() calls at start stay at beginning")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Summer");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        iter->back();
        iter->back();
        iter->back();

        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete Inventory::getInstance();
    }
}

TEST_CASE("Edge case - first() resets position after back()")
{
    SUBCASE("first() after back() operations resets to beginning")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Summer");
        LivingPlant *plant3 = createPlantWithSeason("Autumn");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        iter->next();
        iter->next();
        CHECK(iter->currentItem() == plant3);

        iter->back();
        CHECK(iter->currentItem() == plant2);

        iter->first();  // Reset
        CHECK(iter->currentItem() == plant1);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete Inventory::getInstance();
    }
}

TEST_CASE("Iterator symmetry - forward then backward equals identity")
{
    SUBCASE("Going forward N steps then back N steps returns to start")
    {
        Inventory *inv = Inventory::getInstance();

        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Summer");
        LivingPlant *plant3 = createPlantWithSeason("Autumn");
        LivingPlant *plant4 = createPlantWithSeason("Winter");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);
        plantList.push_back(plant3);
        plantList.push_back(plant4);

        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();

        iter->first();
        LivingPlant *start = iter->currentItem();

        // Forward 3 steps
        iter->next();
        iter->next();
        iter->next();

        // Back 3 steps
        iter->back();
        iter->back();
        iter->back();

        CHECK(iter->currentItem() == start);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
        delete plant3;
        delete plant4;
        delete Inventory::getInstance();
    }
}
