#include "AlternatingWater.h"
#include "../prototype/LivingPlant.h"
#include <ctime>

int AlternatingWater::water(LivingPlant* plant) {
    
   if (waterAmount < 40) {
      waterAmount+=5;
    } else {
        waterAmount = 20; 
    }
    
    plant->setWaterLevel(plant->getWaterLevel() + waterAmount);
    return waterAmount;
}

int AlternatingWater::getID() {
    return 4;
}

AlternatingWater::AlternatingWater() {
    waterAmount = 20;
   
}