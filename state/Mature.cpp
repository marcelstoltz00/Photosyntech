#include "Mature.h"

#include "Dead.h"
#include <algorithm>

void Mature::grow(LivingPlant* plant) {
    plant->setAge(plant->getAge() + 1);
    double waterusage = 4.0;
 

    
    plant->setWaterLevel(plant->getWaterLevel() - waterusage);
  plant->setHealth(plant->getHealth() - 2);

    if (plant->getWaterLevel() >= 30 && plant->getSunExposure() >= 40) {
        plant->setHealth(plant->getHealth() + 3);
    }
    
    if (plant->getAge() >= 120 || plant->getHealth() <= 0) {
        plant->setWaterLevel(0);
        plant->setHealth(0);
        plant->setSunExposure(0);
        
        plant->setMaturity(Dead::getID());
    }
}
std::string Mature::getImagePath(LivingPlant *plant)
{
    std::string plantName = plant->getName();
    plantName.erase(std::remove(plantName.begin(), plantName.end(), ' '), plantName.end());
    return "docs/images/" + plantName + std::to_string(getID()) + ".png";
}
