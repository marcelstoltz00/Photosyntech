#include "Dead.h"
#include <algorithm>
void Dead::grow(LivingPlant *plant)
{

    plant->setAge(plant->getAge() + 1);
}

std::string Dead::getImagePath(LivingPlant *plant)
{
    std::string plantName = plant->getName();
    plantName.erase(std::remove(plantName.begin(), plantName.end(), ' '), plantName.end());
    return "docs/images/" + plantName + std::to_string(getID()) + ".png";
}

