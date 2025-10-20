#include "MidWater.h"
#include "../prototype/LivingPlant.h"

int MidWater::water(LivingPlant* plant) {
 
    waterAmount = 20;
    // plant->addWaterLevel(waterAmount);
    return waterAmount;
}

int MidWater::getID() {
    return 2;
}

MidWater::MidWater() {
    waterAmount = 3; 
}