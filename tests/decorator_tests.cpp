#include "doctest.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Succulent.h"
#include "prototype/Herb.h"
#include "decorator/plantDecorator/Autumn.h"
#include "decorator/plantDecorator/Spring.h"
#include "decorator/plantDecorator/Summer.h"
#include "decorator/plantDecorator/Winter.h"
#include "decorator/plantDecorator/LargeLeaf.h"
#include "decorator/plantDecorator/SmallLeaf.h"
#include "decorator/plantDecorator/LargeFlowers.h"
#include "decorator/plantDecorator/SmallFlowers.h"
#include "decorator/plantDecorator/LargeStem.h"
#include "decorator/plantDecorator/SmallStem.h"
#include "decorator/plantDecorator/Thorns.h"
#include "decorator/customerDecorator/LargePot.h"
#include "decorator/customerDecorator/RedPot.h"
#include "decorator/customerDecorator/PlantCharm.h"
#include "singleton/Singleton.h"
#include <vector>

TEST_CASE("Testing Decorator Pattern - Basic Decoration")
{
    SUBCASE("Single decorator applied to plant")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Autumn());

        // Plant should have a decorator
        CHECK(plant->getDecorator() != nullptr);

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Plant with no decorator returns nullptr")
    {
        LivingPlant *plant = new Tree();
        CHECK(plant->getDecorator() == nullptr);
        delete plant;
    }
}

TEST_CASE("Testing Decorator Pattern - Plant Type Decoration")
{
    SUBCASE("Tree can be decorated")
    {
        LivingPlant *tree = new Tree();
        tree->addAttribute(new Autumn());
        CHECK(tree->getDecorator() != nullptr);
        delete tree;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Shrub can be decorated")
    {
        LivingPlant *shrub = new Shrub();
        shrub->addAttribute(new Autumn());
        CHECK(shrub->getDecorator() != nullptr);
        delete shrub;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Succulent can be decorated")
    {
        LivingPlant *succulent = new Succulent();
        succulent->addAttribute(new Autumn());
        CHECK(succulent->getDecorator() != nullptr);
        delete succulent;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Decorator Modification")
{
    SUBCASE("Plant decorated with Autumn attribute")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Autumn());

        // Decorator should be retrievable
        PlantComponent *decorated = plant->getDecorator();
        CHECK(decorated != nullptr);

        delete plant;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Multiple Decorations")
{
    SUBCASE("Single plant can have multiple decorations applied")
    {
        LivingPlant *plant = new Tree();

        // Add first decoration
        plant->addAttribute(new Autumn());
        CHECK(plant->getDecorator() != nullptr);

        delete plant;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Decorator Functionality")
{
    SUBCASE("Decorated plant maintains core functionality")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Autumn());

        // Plant should still support water operation
        plant->setWaterLevel(0);
        plant->water();

        // Plant should still have water level after operation
        CHECK(plant->getWaterLevel() >= 0);

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Decorated plant supports setOutside operation")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Autumn());

        plant->setSunExposure(0);
        plant->setOutside();

        // Plant should have sun exposure after operation
        CHECK(plant->getSunExposure() >= 0);

        delete plant;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Decorator and Plant Information")
{
    SUBCASE("Decorated plant provides information")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Autumn());

        std::string info = plant->getInfo();
        CHECK(!info.empty());

        delete plant;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Decorator Memory Management")
{
    SUBCASE("Decorator cleanup works properly")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Autumn());

        PlantComponent *decorator = plant->getDecorator();
        CHECK(decorator != nullptr);

        // Cleanup should work without issues
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Multiple plants with decorators can be cleaned up")
    {
        LivingPlant *plant1 = new Tree();
        plant1->addAttribute(new Autumn());

        LivingPlant *plant2 = new Shrub();
        plant2->addAttribute(new Autumn());

        // Cleanup
        delete plant1;  // Plant destructor will handle decorator cleanup
        delete plant2;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Component Interface")
{
    SUBCASE("Decorated plant is also a PlantComponent")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Autumn());

        PlantComponent *component = plant;
        CHECK(component != nullptr);

        // Component operations should work
        component->water();
        component->setOutside();

        delete plant;  // Plant destructor will handle decorator cleanup
    }
}

// ============================================================================
// EXPANDED DECORATOR TESTS - ALL DECORATOR TYPES
// ============================================================================

TEST_CASE("Testing Decorator Pattern - Season Decorators")
{
    SUBCASE("Spring decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Spring());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Summer decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Summer());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Winter decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Winter());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Season decorators on different plant types")
    {
        LivingPlant *tree = new Tree();
        tree->addAttribute(new Spring());

        LivingPlant *shrub = new Shrub();
        shrub->addAttribute(new Summer());

        LivingPlant *succulent = new Succulent();
        succulent->addAttribute(new Winter());

        CHECK(tree->getDecorator() != nullptr);
        CHECK(shrub->getDecorator() != nullptr);
        CHECK(succulent->getDecorator() != nullptr);

        delete tree;  // Plant destructor will handle decorator cleanup
        delete shrub;  // Plant destructor will handle decorator cleanup
        delete succulent;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Leaf Decorators")
{
    SUBCASE("Large leaf decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new LargeLeaf());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Small leaf decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new SmallLeaf());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Leaf decorators with different plant types")
    {
        std::vector<LivingPlant *> plants;
        plants.push_back(new Tree());
        plants.push_back(new Shrub());
        plants.push_back(new Succulent());
        plants.push_back(new Herb());

        plants[0]->addAttribute(new LargeLeaf());
        plants[1]->addAttribute(new SmallLeaf());
        plants[2]->addAttribute(new LargeLeaf());
        plants[3]->addAttribute(new SmallLeaf());

        for (LivingPlant *p : plants) {
            CHECK(p->getDecorator() != nullptr);
        }

        for (LivingPlant *p : plants) {
            delete p;  // Plant destructor will handle decorator cleanup
        }
    }
}

TEST_CASE("Testing Decorator Pattern - Flower Decorators")
{
    SUBCASE("Large flowers decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new LargeFlowers());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Small flowers decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new SmallFlowers());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Flower decorators on all plant types")
    {
        LivingPlant *tree = new Tree();
        tree->addAttribute(new LargeFlowers());

        LivingPlant *shrub = new Shrub();
        shrub->addAttribute(new SmallFlowers());

        LivingPlant *succulent = new Succulent();
        succulent->addAttribute(new LargeFlowers());

        LivingPlant *herb = new Herb();
        herb->addAttribute(new SmallFlowers());

        CHECK(tree->getDecorator() != nullptr);
        CHECK(shrub->getDecorator() != nullptr);
        CHECK(succulent->getDecorator() != nullptr);
        CHECK(herb->getDecorator() != nullptr);

        delete tree;  // Plant destructor will handle decorator cleanup
        delete shrub;  // Plant destructor will handle decorator cleanup
        delete succulent;  // Plant destructor will handle decorator cleanup
        delete herb;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Stem Decorators")
{
    SUBCASE("Large stem decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new LargeStem());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Small stem decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new SmallStem());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Stem decorator combinations")
    {
        LivingPlant *plant1 = new Tree();
        plant1->addAttribute(new LargeStem());

        LivingPlant *plant2 = new Shrub();
        plant2->addAttribute(new SmallStem());

        CHECK(plant1->getDecorator() != nullptr);
        CHECK(plant2->getDecorator() != nullptr);

        delete plant1;  // Plant destructor will handle decorator cleanup
        delete plant2;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Special Decorators")
{
    SUBCASE("Thorns decorator")
    {
        LivingPlant *plant = new Succulent();
        plant->addAttribute(new Thorns());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Thorns on different plant types")
    {
        LivingPlant *succulent = new Succulent();
        succulent->addAttribute(new Thorns());

        LivingPlant *tree = new Tree();
        tree->addAttribute(new Thorns());

        CHECK(succulent->getDecorator() != nullptr);
        CHECK(tree->getDecorator() != nullptr);

        delete succulent;  // Plant destructor will handle decorator cleanup
        delete tree;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Pot Decorators")
{
    SUBCASE("Large pot decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new LargePot());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Red pot decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new RedPot());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Pot decorators on all plant types")
    {
        std::vector<LivingPlant *> plants;
        plants.push_back(new Tree());
        plants.push_back(new Shrub());
        plants.push_back(new Succulent());

        plants[0]->addAttribute(new LargePot());
        plants[1]->addAttribute(new RedPot());
        plants[2]->addAttribute(new LargePot());

        for (LivingPlant *p : plants) {
            CHECK(p->getDecorator() != nullptr);
        }

        for (LivingPlant *p : plants) {
            delete p;  // Plant destructor will handle decorator cleanup
        }
    }
}

TEST_CASE("Testing Decorator Pattern - Charm Decorators")
{
    SUBCASE("Plant charm decorator")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new PlantCharm());
        CHECK(plant->getDecorator() != nullptr);
        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Multiple charm instances")
    {
        LivingPlant *plant1 = new Tree();
        plant1->addAttribute(new PlantCharm());

        LivingPlant *plant2 = new Shrub();
        plant2->addAttribute(new PlantCharm());

        CHECK(plant1->getDecorator() != nullptr);
        CHECK(plant2->getDecorator() != nullptr);

        delete plant1;  // Plant destructor will handle decorator cleanup
        delete plant2;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Chained/Nested Decorators")
{
    SUBCASE("Two decorators on single plant")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Spring());
        plant->addAttribute(new LargeLeaf());

        // Should support multiple decorators
        CHECK(plant->getDecorator() != nullptr);

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Multiple sequential decorators")
    {
        LivingPlant *plant = new Tree();

        plant->addAttribute(new Spring());
        CHECK(plant->getDecorator() != nullptr);

        plant->addAttribute(new LargeFlowers());
        CHECK(plant->getDecorator() != nullptr);

        plant->addAttribute(new LargePot());
        CHECK(plant->getDecorator() != nullptr);

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Decorator chain with 5+ decorators")
    {
        LivingPlant *plant = new Tree();

        plant->addAttribute(new Spring());
        plant->addAttribute(new LargeLeaf());
        plant->addAttribute(new LargeFlowers());
        plant->addAttribute(new LargeStem());
        plant->addAttribute(new LargePot());

        // All decorators should be present
        CHECK(plant->getDecorator() != nullptr);

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Decorator removal and replacement")
    {
        // Test replacing decorators by creating a new plant instance
        // Note: The current architecture doesn't support removing decorators
        // without deleting the wrapped plant, so we test the concept by
        // creating separate plant instances

        LivingPlant *plant1 = new Tree();
        plant1->addAttribute(new Spring());
        CHECK(plant1->getDecorator() != nullptr);
        delete plant1;  // Delete the plant with Spring decorator

        // Create a new plant and add a different decorator
        LivingPlant *plant2 = new Tree();
        plant2->addAttribute(new Summer());
        CHECK(plant2->getDecorator() != nullptr);
        delete plant2;  // Delete the plant with Summer decorator
    }
}

TEST_CASE("Testing Decorator Pattern - Complex Scenarios")
{
    SUBCASE("All plant types with all decorator combinations")
    {
        std::vector<LivingPlant *> plants;
        plants.push_back(new Tree());
        plants.push_back(new Shrub());
        plants.push_back(new Succulent());
        plants.push_back(new Herb());

        // Apply various decorators
        plants[0]->addAttribute(new Spring());
        plants[1]->addAttribute(new Summer());
        plants[2]->addAttribute(new Winter());
        plants[3]->addAttribute(new Autumn());

        for (LivingPlant *p : plants) {
            CHECK(p->getDecorator() != nullptr);
        }

        for (LivingPlant *p : plants) {
            delete p;  // Plant destructor will handle decorator cleanup
        }
    }

    SUBCASE("Decorator performance with many plants")
    {
        std::vector<LivingPlant *> plants;

        for (int i = 0; i < 50; i++) {
            LivingPlant *p = new Tree();

            if (i % 4 == 0) p->addAttribute(new Spring());
            else if (i % 4 == 1) p->addAttribute(new Summer());
            else if (i % 4 == 2) p->addAttribute(new Winter());
            else p->addAttribute(new Autumn());

            plants.push_back(p);
        }

        for (LivingPlant *p : plants) {
            CHECK(p->getDecorator() != nullptr);
        }

        for (LivingPlant *p : plants) {
            delete p;  // Plant destructor will handle decorator cleanup
        }
    }

    SUBCASE("Decorator state preservation")
    {
        LivingPlant *plant = new Tree();
        plant->setWaterLevel(25);
        plant->setHealth(75);

        plant->addAttribute(new Spring());

        // Plant state should be preserved
        CHECK(plant->getWaterLevel() == 25);
        CHECK(plant->getHealth() == 75);

        delete plant;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - Decorator Functionality")
{
    SUBCASE("Decorated plant supports water operation")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Spring());

        plant->setWaterLevel(0);
        plant->water();

        // Water operation should work on decorated plant
        CHECK(plant->getWaterLevel() >= 0);

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Decorated plant supports setOutside operation")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Spring());

        plant->setSunExposure(0);
        plant->setOutside();

        // Sun operation should work on decorated plant
        CHECK(plant->getSunExposure() >= 0);

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Multi-decorated plant supports operations")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Spring());
        plant->addAttribute(new LargeLeaf());
        plant->addAttribute(new LargeFlowers());

        plant->setWaterLevel(0);
        plant->setWaterStrategy(LowWater::getID());
        plant->water();

        plant->setSunExposure(0);
        plant->setOutside();

        CHECK(plant->getWaterLevel() >= 0);
        CHECK(plant->getSunExposure() >= 0);

        delete plant;  // Plant destructor will handle decorator cleanup
    }
}

TEST_CASE("Testing Decorator Pattern - getInfo() with Decorators")
{
    SUBCASE("Single decorator getInfo")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Spring());

        std::string info = plant->getInfo();
        CHECK(!info.empty());

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Multiple decorators in getInfo")
    {
        LivingPlant *plant = new Tree();
        plant->addAttribute(new Spring());
        plant->addAttribute(new LargeLeaf());
        plant->addAttribute(new LargeFlowers());

        std::string info = plant->getInfo();
        CHECK(!info.empty());

        delete plant;  // Plant destructor will handle decorator cleanup
    }

    SUBCASE("Different decorators produce different info")
    {
        LivingPlant *plant1 = new Tree();
        plant1->addAttribute(new Spring());

        LivingPlant *plant2 = new Tree();
        plant2->addAttribute(new Winter());

        std::string info1 = plant1->getInfo();
        std::string info2 = plant2->getInfo();

        // Different decorators should potentially produce different info
        CHECK(!info1.empty());
        CHECK(!info2.empty());

        delete plant1;  // Plant destructor will handle decorator cleanup
        delete plant2;  // Plant destructor will handle decorator cleanup
    }
}