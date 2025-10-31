#include "HighWater.h"
#include "../prototype/LivingPlant.h"

int HighWater::water(LivingPlant* plant) {
   
  
       plant->setWaterLevel(plant->getWaterLevel() + waterAmount);
    return waterAmount;
}

 int HighWater::getID() {
    return 3;
}

HighWater::HighWater() {
    waterAmount = 25; 
}