#include "Vegetative.h"

#include "Mature.h"
#include <algorithm>

void Vegetative::grow(LivingPlant *plant)
{
    plant->setAge(plant->getAge() + 1);
    double waterusage = 10.0;
    std::string season = *plant->getSeason()->getState();
    if (season == "Spring") {
        waterusage *= 0.9;
    } else if (season == "Summer") {
        waterusage *= 1.3f;
    } else if (season == "Autumn") {
        waterusage *= 1.0f;
    } else if (season == "Winter") {
        waterusage *= 0.7f;
    } else {
        waterusage *= 1.0f;
    }

    plant->setWaterLevel(plant->getWaterLevel() - waterusage);

    if (plant->getAge() >= 30 && plant->getSunExposure() >= 40)
    {
        plant->setHealth(plant->getHealth() + 3);
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
