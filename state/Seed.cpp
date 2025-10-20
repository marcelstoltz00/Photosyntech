#include "Seed.h"
#include "LivingPlant.h"
#include "Vegetative.h"
#include <algorithm>

void Seed::grow(LivingPlant* plant) {
    plant->setAge(plant->getAge() + 1);
    double waterusage = 6.0;
    //    switch (plant->getSeason()) {
//         case Season::SPRING:
//             waterusage *= 0.9;
//             break;
//         case Season::SUMMER:
//             waterusage *= 1.3f;
//             break;
//         case Season::AUTUMN:
//             waterusage *= 1.0f;
//             break;
//         case Season::WINTER:
//             waterusage *= 0.7f;
//             break;
//         default:
//             waterusage *= 1.0f;
//     }
    
    plant->setWaterLevel(plant->getWaterLevel() - waterusage);

    if (plant->getWaterLevel() >= 40 && plant->getSunExposure() >= 20) {
        plant->setHealth(plant->getHealth() + 4);
    }
    
    if (plant->getAge() >= 7 && 
        plant->getHealth() >= 50 && 
        plant->getWaterLevel() >= 50 && 
        plant->getSunExposure() >= 30) {
        
        plant->setWaterLevel(25);
        plant->setHealth(std::max(plant->getHealth(), 50));
        plant->setSunExposure(50);
        
        plant->setMaturity(Vegetative::getID());
    }
}