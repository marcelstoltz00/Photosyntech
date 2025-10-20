#include "Mature.h"
#include "LivingPlant.h"
#include "Dead.h"
#include <algorithm>

void Mature::grow(LivingPlant* plant) {
    plant->setAge(plant->getAge() + 1);
    double waterusage = 8.0;
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

    if (plant->getWaterLevel() >= 30 && plant->getSunExposure() >= 40) {
        plant->setHealth(plant->getHealth() + 1);
    }
    
    if (plant->getAge() >= 120 || plant->getHealth() <= 0) {
        plant->setWaterLevel(0);
        plant->setHealth(0);
        plant->setSunExposure(0);
        
        plant->setMaturity(Dead::getID());
    }
}