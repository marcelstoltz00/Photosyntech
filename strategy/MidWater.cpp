#include "MidWater.h"
#include "../prototype/LivingPlant.h"

int MidWater::water(LivingPlant* plant) {
 
    waterAmount = 20;
    plant->setWaterLevel(plant->getWaterLevel() + waterAmount);
    return waterAmount;
}

int MidWater::getID() {
    return 2;
}

MidWater::MidWater() {
    waterAmount = 20; 
}