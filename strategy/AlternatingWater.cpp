#include "AlternatingWater.h"
#include "../prototype/LivingPlant.h"
#include <ctime>

int AlternatingWater::water(LivingPlant* plant) {
    
    time_t now = time(nullptr);
    long days = now / 86400; 
    waterAmount = (days % 2 == 0) ? 25 : 15;
    
    // plant->addWaterLevel(waterAmount);
    return waterAmount;
}

int AlternatingWater::getID() {
    return 4;
}

AlternatingWater::AlternatingWater() {
    waterAmount = 0;
   
}