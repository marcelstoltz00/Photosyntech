// please use testing like this.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "singleton/Singleton.h"
#include <doctest/doctest.h>
#include "prototype/Tree.h"
#include "state/Seed.h"

TEST_CASE("Overall Testing of flyweight strings + error handling")
{
    FlyweightFactory<int, string *> *fac = new FlyweightFactory<int, string *>();

    CHECK(fac != nullptr);

    fac->getFlyweight(0, new string("Insert1"));
    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");

    fac->getFlyweight(1, new string("Insert2"));
    CHECK(*fac->getFlyweight(1)->getState() == "Insert2");

    CHECK(*fac->getFlyweight(0)->getState() == "Insert1");

    try
    {
        fac->getFlyweight(5);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }

    delete fac;
}
TEST_CASE("Overall Testing of flyweight water strategies")
{
    FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();
    LivingPlant *plant = new Tree();
    fac->getFlyweight(LowWater::getID(), new LowWater());

    CHECK(fac->getFlyweight(LowWater::getID())->getState()->water(plant) == 10);

    fac->getFlyweight(MidWater::getID(), new MidWater());

    CHECK(fac->getFlyweight(MidWater::getID())->getState()->water(plant) == 20);
    delete fac;
    delete plant;
}
TEST_CASE("Singleton basics with water strategy testing and with state testing")
{
    LivingPlant *plant = new Tree();

    Inventory *inv = Inventory::getInstance();
    CHECK(inv == Inventory::getInstance());
    CHECK(inv->getWaterFly(LowWater::getID())->getState()->water(plant) == 10);
    CHECK(Inventory::getInstance()->getWaterFly(MidWater::getID())->getState()->water(plant) == 20);

    for (int i = 0; i < 7; i++)
    {
        Inventory::getInstance()->getStates(Seed::getID())->getState()->grow(plant);
    };
    CHECK(plant->getAge() == 7);

    CHECK(Inventory::getInstance()->getWaterFly(5000)->getState()->water(plant) == 10);

    delete inv;
    delete plant;
}

// ============================================================================
// ITERATOR PATTERN COMPREHENSIVE TEST SUITE
// ============================================================================
// These tests ensure stable iterator functionality before and after refactor
// Tests cover: PlantIterator, SeasonIterator, nested hierarchies, edge cases
// ============================================================================

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
#include <vector>

// ============================================================================
// TEST HELPER FUNCTIONS
// ============================================================================

/**
 * @brief Counts the total number of plants returned by an iterator
 * @param iter Iterator to count (will be reset with first())
 * @return Number of plants iterated
 */
int countIteratorResults(Iterator* iter) {
    int count = 0;
    iter->first();
    while (!iter->isDone()) {
        count++;
        iter->next();
    }
    return count;
}

/**
 * @brief Collects all plants from an iterator into a vector
 * @param iter Iterator to collect from (will be reset with first())
 * @return Vector of pointers to LivingPlants
 */
std::vector<LivingPlant*> collectPlants(Iterator* iter) {
    std::vector<LivingPlant*> plants;
    iter->first();
    while (!iter->isDone()) {
        plants.push_back(iter->currentItem());
        iter->next();
    }
    return plants;
}

/**
 * @brief Creates a test plant with specified season
 * @param season Season name string
 * @return Pointer to created LivingPlant (Succulent)
 */
LivingPlant* createPlantWithSeason(const std::string& season) {
    Inventory* inv = Inventory::getInstance();
    LivingPlant* plant = new Succulent();
    plant->setSeason(inv->getString(season));
    return plant;
}

// ============================================================================
// PLANTITERATOR BASIC TESTS
// ============================================================================

TEST_CASE("PlantIterator - Empty collection") {
    std::list<PlantComponent*> emptyList;
    AggPlant* agg = new AggPlant(&emptyList);
    Iterator* iter = agg->createIterator();

    SUBCASE("isDone() returns true immediately for empty collection") {
        CHECK(iter->isDone() == true);
    }

    SUBCASE("currentItem() returns nullptr for empty collection") {
        CHECK(iter->currentItem() == nullptr);
    }

    SUBCASE("Calling next() on empty collection has no effect") {
        iter->next();
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);
    }

    delete iter;
    delete agg;
}

TEST_CASE("PlantIterator - Single plant") {
    Inventory* inv = Inventory::getInstance();
    LivingPlant* plant = new Succulent();
    plant->setSeason(inv->getString("Spring"));

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    SUBCASE("first() positions at the plant") {
        iter->first();
        CHECK(iter->isDone() == false);
        CHECK(iter->currentItem() == plant);
    }

    SUBCASE("next() after single plant makes isDone() true") {
        iter->first();
        iter->next();
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);
    }

    SUBCASE("Iteration sequence is correct") {
        iter->first();
        CHECK(iter->currentItem() == plant);
        iter->next();
        CHECK(iter->isDone() == true);
    }

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("PlantIterator - Multiple plants in flat list") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = new Succulent();
    plant1->setSeason(inv->getString("Spring"));
    LivingPlant* plant2 = new Tree();
    plant2->setSeason(inv->getString("Summer"));
    LivingPlant* plant3 = new Shrub();
    plant3->setSeason(inv->getString("Autumn"));

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    SUBCASE("Count returns correct number") {
        CHECK(countIteratorResults(iter) == 3);
    }

    SUBCASE("Iteration returns all plants in order") {
        std::vector<LivingPlant*> collected = collectPlants(iter);
        CHECK(collected.size() == 3);
        CHECK(collected[0] == plant1);
        CHECK(collected[1] == plant2);
        CHECK(collected[2] == plant3);
    }

    SUBCASE("Manual iteration works correctly") {
        iter->first();
        CHECK(iter->currentItem() == plant1);
        iter->next();
        CHECK(iter->currentItem() == plant2);
        iter->next();
        CHECK(iter->currentItem() == plant3);
        iter->next();
        CHECK(iter->isDone() == true);
    }

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("PlantIterator - Mixed plant types") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* succulent = new Succulent();
    succulent->setSeason(inv->getString("Spring"));
    LivingPlant* tree = new Tree();
    tree->setSeason(inv->getString("Summer"));
    LivingPlant* shrub = new Shrub();
    shrub->setSeason(inv->getString("Autumn"));
    LivingPlant* herb = new Herb();
    herb->setSeason(inv->getString("Winter"));

    std::list<PlantComponent*> plantList;
    plantList.push_back(succulent);
    plantList.push_back(tree);
    plantList.push_back(shrub);
    plantList.push_back(herb);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    CHECK(countIteratorResults(iter) == 4);

    std::vector<LivingPlant*> collected = collectPlants(iter);
    CHECK(collected.size() == 4);
    CHECK(collected[0] == succulent);
    CHECK(collected[1] == tree);
    CHECK(collected[2] == shrub);
    CHECK(collected[3] == herb);

    delete iter;
    delete agg;
    delete succulent;
    delete tree;
    delete shrub;
    delete herb;
}

// ============================================================================
// SEASONITERATOR BASIC TESTS
// ============================================================================

TEST_CASE("SeasonIterator - Empty collection with season filter") {
    Inventory* inv = Inventory::getInstance();
    std::list<PlantComponent*> emptyList;

    AggSeason* agg = new AggSeason(&emptyList, inv->getString("Spring"));
    Iterator* iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    delete iter;
    delete agg;
}

TEST_CASE("SeasonIterator - Single matching plant") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant = createPlantWithSeason("Spring");
    std::list<PlantComponent*> plantList;
    plantList.push_back(plant);

    AggSeason* agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator* iter = agg->createIterator();

    SUBCASE("Returns the matching plant") {
        iter->first();
        CHECK(iter->isDone() == false);
        CHECK(iter->currentItem() == plant);
    }

    SUBCASE("Becomes done after the single match") {
        iter->first();
        iter->next();
        CHECK(iter->isDone() == true);
    }

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("SeasonIterator - Single non-matching plant") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant = createPlantWithSeason("Summer");
    std::list<PlantComponent*> plantList;
    plantList.push_back(plant);

    AggSeason* agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator* iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("SeasonIterator - Multiple matching plants") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");
    LivingPlant* plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggSeason* agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator* iter = agg->createIterator();

    CHECK(countIteratorResults(iter) == 3);

    std::vector<LivingPlant*> collected = collectPlants(iter);
    CHECK(collected.size() == 3);
    CHECK(collected[0] == plant1);
    CHECK(collected[1] == plant2);
    CHECK(collected[2] == plant3);

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("SeasonIterator - Mixed seasons with filtering") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* spring1 = createPlantWithSeason("Spring");
    LivingPlant* summer1 = createPlantWithSeason("Summer");
    LivingPlant* spring2 = createPlantWithSeason("Spring");
    LivingPlant* autumn1 = createPlantWithSeason("Autumn");

    std::list<PlantComponent*> plantList;
    plantList.push_back(spring1);
    plantList.push_back(summer1);
    plantList.push_back(spring2);
    plantList.push_back(autumn1);

    SUBCASE("Filter for Spring returns only Spring plants") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator* iter = agg->createIterator();

        std::vector<LivingPlant*> collected = collectPlants(iter);
        CHECK(collected.size() == 2);
        CHECK(collected[0] == spring1);
        CHECK(collected[1] == spring2);

        delete iter;
        delete agg;
    }

    SUBCASE("Filter for Summer returns only Summer plants") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator* iter = agg->createIterator();

        std::vector<LivingPlant*> collected = collectPlants(iter);
        CHECK(collected.size() == 1);
        CHECK(collected[0] == summer1);

        delete iter;
        delete agg;
    }

    SUBCASE("Filter for Autumn returns only Autumn plants") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Autumn"));
        Iterator* iter = agg->createIterator();

        std::vector<LivingPlant*> collected = collectPlants(iter);
        CHECK(collected.size() == 1);
        CHECK(collected[0] == autumn1);

        delete iter;
        delete agg;
    }

    delete spring1;
    delete summer1;
    delete spring2;
    delete autumn1;
}

TEST_CASE("SeasonIterator - No matching plants") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* summer1 = createPlantWithSeason("Summer");
    LivingPlant* summer2 = createPlantWithSeason("Summer");
    LivingPlant* summer3 = createPlantWithSeason("Summer");

    std::list<PlantComponent*> plantList;
    plantList.push_back(summer1);
    plantList.push_back(summer2);
    plantList.push_back(summer3);

    AggSeason* agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator* iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);
    CHECK(countIteratorResults(iter) == 0);

    delete iter;
    delete agg;
    delete summer1;
    delete summer2;
    delete summer3;
}

TEST_CASE("SeasonIterator - All four seasons") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* spring = createPlantWithSeason("Spring");
    LivingPlant* summer = createPlantWithSeason("Summer");
    LivingPlant* autumn = createPlantWithSeason("Autumn");
    LivingPlant* winter = createPlantWithSeason("Winter");

    std::list<PlantComponent*> plantList;
    plantList.push_back(spring);
    plantList.push_back(summer);
    plantList.push_back(autumn);
    plantList.push_back(winter);

    SUBCASE("Filter Spring") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == spring);
        delete iter;
        delete agg;
    }

    SUBCASE("Filter Summer") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == summer);
        delete iter;
        delete agg;
    }

    SUBCASE("Filter Autumn") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Autumn"));
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == autumn);
        delete iter;
        delete agg;
    }

    SUBCASE("Filter Winter") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Winter"));
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == winter);
        delete iter;
        delete agg;
    }

    delete spring;
    delete summer;
    delete autumn;
    delete winter;
}

// ============================================================================
// ITERATOR BEHAVIOR CONTRACT TESTS
// ============================================================================

TEST_CASE("Iterator behavior - first() resets iterator") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");
    LivingPlant* plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    SUBCASE("first() called twice positions at beginning both times") {
        iter->first();
        CHECK(iter->currentItem() == plant1);
        iter->first();
        CHECK(iter->currentItem() == plant1);
    }

    SUBCASE("first() after next() resets to beginning") {
        iter->first();
        iter->next();
        CHECK(iter->currentItem() == plant2);
        iter->first();
        CHECK(iter->currentItem() == plant1);
    }

    SUBCASE("first() after complete iteration allows re-iteration") {
        // First iteration
        int count1 = countIteratorResults(iter);
        CHECK(count1 == 3);
        CHECK(iter->isDone() == true);

        // Reset and iterate again
        iter->first();
        CHECK(iter->isDone() == false);
        int count2 = countIteratorResults(iter);
        CHECK(count2 == 3);
    }

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("Iterator behavior - next() at end stays at end") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant = createPlantWithSeason("Spring");
    std::list<PlantComponent*> plantList;
    plantList.push_back(plant);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    iter->first();
    iter->next();
    CHECK(iter->isDone() == true);

    // Call next() multiple times at end
    iter->next();
    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    iter->next();
    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("Iterator behavior - currentItem() doesn't advance iterator") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    iter->first();
    LivingPlant* item1 = iter->currentItem();
    LivingPlant* item2 = iter->currentItem();
    LivingPlant* item3 = iter->currentItem();

    CHECK(item1 == plant1);
    CHECK(item2 == plant1);
    CHECK(item3 == plant1);
    CHECK(iter->isDone() == false);

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
}

TEST_CASE("Iterator behavior - isDone() accurately reflects state") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    SUBCASE("isDone() false when elements remain") {
        iter->first();
        CHECK(iter->isDone() == false);
        iter->next();
        CHECK(iter->isDone() == false);
    }

    SUBCASE("isDone() true after all elements exhausted") {
        iter->first();
        iter->next();
        iter->next();
        CHECK(iter->isDone() == true);
    }

    SUBCASE("isDone() false after first() resets") {
        iter->first();
        iter->next();
        iter->next();
        CHECK(iter->isDone() == true);
        iter->first();
        CHECK(iter->isDone() == false);
    }

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
}

// ============================================================================
// COMPARISON TESTS: PlantIterator vs SeasonIterator
// ============================================================================

TEST_CASE("PlantIterator vs SeasonIterator comparison") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* spring1 = createPlantWithSeason("Spring");
    LivingPlant* spring2 = createPlantWithSeason("Spring");
    LivingPlant* summer1 = createPlantWithSeason("Summer");
    LivingPlant* summer2 = createPlantWithSeason("Summer");
    LivingPlant* autumn1 = createPlantWithSeason("Autumn");

    std::list<PlantComponent*> plantList;
    plantList.push_back(spring1);
    plantList.push_back(summer1);
    plantList.push_back(spring2);
    plantList.push_back(summer2);
    plantList.push_back(autumn1);

    SUBCASE("PlantIterator returns all plants") {
        AggPlant* agg = new AggPlant(&plantList);
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 5);
        delete iter;
        delete agg;
    }

    SUBCASE("SeasonIterator count <= PlantIterator count") {
        AggPlant* aggAll = new AggPlant(&plantList);
        Iterator* iterAll = aggAll->createIterator();
        int allCount = countIteratorResults(iterAll);

        AggSeason* aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator* iterSpring = aggSpring->createIterator();
        int springCount = countIteratorResults(iterSpring);

        CHECK(springCount <= allCount);
        CHECK(springCount == 2);
        CHECK(allCount == 5);

        delete iterAll;
        delete aggAll;
        delete iterSpring;
        delete aggSpring;
    }

    SUBCASE("SeasonIterator is subset of PlantIterator") {
        AggSeason* aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator* iterSpring = aggSpring->createIterator();
        std::vector<LivingPlant*> springPlants = collectPlants(iterSpring);

        AggPlant* aggAll = new AggPlant(&plantList);
        Iterator* iterAll = aggAll->createIterator();
        std::vector<LivingPlant*> allPlants = collectPlants(iterAll);

        // Every spring plant should be in all plants
        for (LivingPlant* springPlant : springPlants) {
            bool found = false;
            for (LivingPlant* plant : allPlants) {
                if (plant == springPlant) {
                    found = true;
                    break;
                }
            }
            CHECK(found == true);
        }

        delete iterSpring;
        delete aggSpring;
        delete iterAll;
        delete aggAll;
    }

    delete spring1;
    delete spring2;
    delete summer1;
    delete summer2;
    delete autumn1;
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

TEST_CASE("Edge case - Multiple iterators on same collection are independent") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");
    LivingPlant* plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter1 = agg->createIterator();
    Iterator* iter2 = agg->createIterator();

    // Advance iter1
    iter1->first();
    iter1->next();
    CHECK(iter1->currentItem() == plant2);

    // iter2 should be independent
    iter2->first();
    CHECK(iter2->currentItem() == plant1);

    // Advance iter2
    iter2->next();
    iter2->next();
    CHECK(iter2->currentItem() == plant3);

    // iter1 should still be at plant2
    CHECK(iter1->currentItem() == plant2);

    delete iter1;
    delete iter2;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("Edge case - Iterator doesn't modify collection") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);

    size_t originalSize = plantList.size();

    AggPlant* agg = new AggPlant(&plantList);
    Iterator* iter = agg->createIterator();

    // Iterate through collection
    countIteratorResults(iter);

    // Collection should be unchanged
    CHECK(plantList.size() == originalSize);
    CHECK(plantList.front() == plant1);
    CHECK(plantList.back() == plant2);

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
}

TEST_CASE("Edge case - All plants same season") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");
    LivingPlant* plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent*> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    SUBCASE("Filtering for that season returns all") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 3);
        delete iter;
        delete agg;
    }

    SUBCASE("Filtering for different season returns none") {
        AggSeason* agg = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 0);
        delete iter;
        delete agg;
    }

    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("Edge case - Each plant different season") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* spring = createPlantWithSeason("Spring");
    LivingPlant* summer = createPlantWithSeason("Summer");
    LivingPlant* autumn = createPlantWithSeason("Autumn");
    LivingPlant* winter = createPlantWithSeason("Winter");

    std::list<PlantComponent*> plantList;
    plantList.push_back(spring);
    plantList.push_back(summer);
    plantList.push_back(autumn);
    plantList.push_back(winter);

    SUBCASE("PlantIterator returns all 4") {
        AggPlant* agg = new AggPlant(&plantList);
        Iterator* iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 4);
        delete iter;
        delete agg;
    }

    SUBCASE("Each season filter returns exactly 1") {
        AggSeason* aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator* iterSpring = aggSpring->createIterator();
        CHECK(countIteratorResults(iterSpring) == 1);
        delete iterSpring;
        delete aggSpring;

        AggSeason* aggSummer = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator* iterSummer = aggSummer->createIterator();
        CHECK(countIteratorResults(iterSummer) == 1);
        delete iterSummer;
        delete aggSummer;

        AggSeason* aggAutumn = new AggSeason(&plantList, inv->getString("Autumn"));
        Iterator* iterAutumn = aggAutumn->createIterator();
        CHECK(countIteratorResults(iterAutumn) == 1);
        delete iterAutumn;
        delete aggAutumn;

        AggSeason* aggWinter = new AggSeason(&plantList, inv->getString("Winter"));
        Iterator* iterWinter = aggWinter->createIterator();
        CHECK(countIteratorResults(iterWinter) == 1);
        delete iterWinter;
        delete aggWinter;
    }

    delete spring;
    delete summer;
    delete autumn;
    delete winter;
}

// ============================================================================
// END OF ITERATOR TEST SUITE
// ============================================================================
// Note: Nested hierarchy tests are commented out pending PlantGroup::getPlants()
// implementation. These tests assume the refactor changes will be completed.
// Uncomment when PlantGroup::getPlants() is available.
// ============================================================================

/*
// ============================================================================
// NESTED HIERARCHY TESTS (Requires PlantGroup::getPlants())
// ============================================================================

TEST_CASE("Nested hierarchy - PlantGroup with plants") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");
    LivingPlant* plant3 = createPlantWithSeason("Spring");

    PlantGroup* group = new PlantGroup();
    // Assuming PlantGroup has add() or similar method
    group->add(plant1);
    group->add(plant2);
    group->add(plant3);

    std::list<PlantComponent*> components;
    components.push_back(group);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();

    CHECK(countIteratorResults(iter) == 3);

    delete iter;
    delete agg;
    delete group;
}

TEST_CASE("Nested hierarchy - 2 levels deep") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Summer");

    PlantGroup* innerGroup = new PlantGroup();
    innerGroup->add(plant1);
    innerGroup->add(plant2);

    LivingPlant* plant3 = createPlantWithSeason("Autumn");

    PlantGroup* outerGroup = new PlantGroup();
    outerGroup->add(innerGroup);
    outerGroup->add(plant3);

    std::list<PlantComponent*> components;
    components.push_back(outerGroup);

    AggPlant* aggAll = new AggPlant(&components);
    Iterator* iterAll = aggAll->createIterator();
    CHECK(countIteratorResults(iterAll) == 3);
    delete iterAll;
    delete aggAll;

    AggSeason* aggSpring = new AggSeason(&components, inv->getString("Spring"));
    Iterator* iterSpring = aggSpring->createIterator();
    CHECK(countIteratorResults(iterSpring) == 1);
    delete iterSpring;
    delete aggSpring;

    delete outerGroup;
}

TEST_CASE("Nested hierarchy - 3+ levels deep") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    PlantGroup* level3 = new PlantGroup();
    level3->add(plant1);

    LivingPlant* plant2 = createPlantWithSeason("Summer");
    PlantGroup* level2 = new PlantGroup();
    level2->add(level3);
    level2->add(plant2);

    LivingPlant* plant3 = createPlantWithSeason("Autumn");
    PlantGroup* level1 = new PlantGroup();
    level1->add(level2);
    level1->add(plant3);

    std::list<PlantComponent*> components;
    components.push_back(level1);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();
    CHECK(countIteratorResults(iter) == 3);
    delete iter;
    delete agg;

    delete level1;
}

TEST_CASE("Nested hierarchy - Mixed plants and groups") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Summer");

    PlantGroup* group1 = new PlantGroup();
    group1->add(plant2);

    LivingPlant* plant3 = createPlantWithSeason("Autumn");

    std::list<PlantComponent*> components;
    components.push_back(plant1);
    components.push_back(group1);
    components.push_back(plant3);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();

    std::vector<LivingPlant*> collected = collectPlants(iter);
    CHECK(collected.size() == 3);
    CHECK(collected[0] == plant1);
    CHECK(collected[1] == plant2);
    CHECK(collected[2] == plant3);

    delete iter;
    delete agg;
    delete group1;
}

TEST_CASE("Nested hierarchy - Empty nested groups") {
    PlantGroup* emptyInner = new PlantGroup();
    PlantGroup* outerGroup = new PlantGroup();
    outerGroup->add(emptyInner);

    std::list<PlantComponent*> components;
    components.push_back(outerGroup);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(countIteratorResults(iter) == 0);

    delete iter;
    delete agg;
    delete outerGroup;
}

TEST_CASE("Nested hierarchy - Seasonal filtering with nesting") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* spring1 = createPlantWithSeason("Spring");
    LivingPlant* summer1 = createPlantWithSeason("Summer");

    PlantGroup* innerGroup = new PlantGroup();
    innerGroup->add(spring1);
    innerGroup->add(summer1);

    LivingPlant* spring2 = createPlantWithSeason("Spring");
    LivingPlant* summer2 = createPlantWithSeason("Summer");

    PlantGroup* outerGroup = new PlantGroup();
    outerGroup->add(innerGroup);
    outerGroup->add(spring2);
    outerGroup->add(summer2);

    std::list<PlantComponent*> components;
    components.push_back(outerGroup);

    AggSeason* aggSpring = new AggSeason(&components, inv->getString("Spring"));
    Iterator* iterSpring = aggSpring->createIterator();
    CHECK(countIteratorResults(iterSpring) == 2);
    delete iterSpring;
    delete aggSpring;

    AggSeason* aggSummer = new AggSeason(&components, inv->getString("Summer"));
    Iterator* iterSummer = aggSummer->createIterator();
    CHECK(countIteratorResults(iterSummer) == 2);
    delete iterSummer;
    delete aggSummer;

    delete outerGroup;
}
*/
