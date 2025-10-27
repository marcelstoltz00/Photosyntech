#include "Seed.h"

#include "Vegetative.h"
#include <algorithm>

void Seed::grow(LivingPlant *plant)
{
    plant->setAge(plant->getAge() + 1);
    double waterusage = 3.0;

    plant->setWaterLevel(plant->getWaterLevel() - waterusage);
  plant->setHealth(plant->getHealth() - 3);

    if (plant->getWaterLevel() >= 40 && plant->getSunExposure() >= 20)
    {
        plant->setHealth(plant->getHealth() + 4);
    }

    if (plant->getAge() >= 7 &&
        plant->getHealth() >= 50 &&
        plant->getWaterLevel() >= 50 &&
        plant->getSunExposure() >= 30)
    {

        plant->setWaterLevel(25);
        plant->setHealth(std::max(plant->getHealth(), 50));
        plant->setSunExposure(50);
          plant->setMaturity(Vegetative::getID());
    }
}

std::string Seed::getImagePath(LivingPlant *plant)
{
    std::string plantName = plant->getName();
    plantName.erase(std::remove(plantName.begin(), plantName.end(), ' '), plantName.end());
    return "docs/images/" + plantName + std::to_string(getID()) + ".png";
}
