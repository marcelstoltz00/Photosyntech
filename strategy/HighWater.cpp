#include "HighWater.h"
#include "../prototype/LivingPlant.h"

int HighWater::water(LivingPlant* plant) {
   
    waterAmount = 30;
    // plant->addWaterLevel(waterAmount);
    return waterAmount;
}

 int HighWater::getID() {
    return 3;
}