#include "Vegetative.h"
#include "LivingPlant.h"
#include "Mature.h"

void Vegetative::grow(LivingPlant* plant) {
    plant->incrementAge();
    
    float waterUsage = 10.0f * plant->getSeasonMultiplier();
    plant->decreaseWater(waterUsage);
    
    if (plant->getWater() >= 30 && plant->getSunExposure() >= 40) {
        plant->increaseHealth(3);
    }
    
    if (plant->getAge() >= 30 && 
        plant->getHealth() >= 60 && 
        plant->getWater() >= 40 && 
        plant->getSunExposure() >= 50) {
        
        plant->setWater(40);
        plant->setHealth(std::max(plant->getHealth(), 60));
        plant->setSunExposure(60);
        
        plant->setState(new Mature());
    }
}