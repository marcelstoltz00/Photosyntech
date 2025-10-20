#include "AlternatingWater.h"
#include "../prototype/LivingPlant.h"
#include <ctime>

int AlternatingWater::water(LivingPlant* plant) {
    
   if (waterAmount < 5) {
      waterAmount++;
    } else {
        waterAmount = 2; 
    }
    
    // plant->addWaterLevel(waterAmount);
    return waterAmount;
}

int AlternatingWater::getID() {
    return 4;
}

AlternatingWater::AlternatingWater() {
    waterAmount = 2;
   
}