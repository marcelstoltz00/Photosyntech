#include "Vegetative.h"

#include "Mature.h"
#include <algorithm>

void Vegetative::grow(LivingPlant* plant) {
    plant->setAge(plant->getAge() + 1);
    double waterusage = 10.0;

    plant->setWaterLevel(plant->getWaterLevel() - waterusage);

    if (plant->getAge() >= 30 && plant->getSunExposure() >= 40) {
        plant->setHealth(plant->getHealth() + 3);
    }
    
    if (plant->getAge() >= 30 && 
        plant->getHealth() >= 60 && 
        plant->getWaterLevel() >= 40 && 
        plant->getSunExposure() >= 50) {
        
        plant->setWaterLevel(40);
        plant->setHealth(std::max(plant->getHealth(), 60));
        plant->setSunExposure(60);

        plant->setMaturity(Mature::getID()); 
    }
}