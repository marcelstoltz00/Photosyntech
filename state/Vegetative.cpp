#include "Vegetative.h"

#include "Mature.h"
#include <algorithm>

void Vegetative::grow(LivingPlant *plant)
{
    plant->setAge(plant->getAge() + 1);
    double waterusage = 10.0;


    plant->setWaterLevel(plant->getWaterLevel() - waterusage);
  plant->setHealth(plant->getHealth() - 4);

    if (plant->getAge() >= 30 && plant->getSunExposure() >= 40)
    {
        plant->setHealth(plant->getHealth() + 5);
    }

    if (plant->getAge() >= 30 &&
        plant->getHealth() >= 60 &&
        plant->getWaterLevel() >= 40 &&
        plant->getSunExposure() >= 50)
    {

        plant->setWaterLevel(40);
        plant->setHealth(std::max(plant->getHealth(), 60));
        plant->setSunExposure(60);

        plant->setMaturity(Mature::getID());
    }
}

std::string Vegetative::getImagePath(LivingPlant *plant)
{
    std::string plantName = plant->getName();
    plantName.erase(std::remove(plantName.begin(), plantName.end(), ' '), plantName.end());
    return "docs/images/" + plantName + std::to_string(getID()) + ".png";
}
