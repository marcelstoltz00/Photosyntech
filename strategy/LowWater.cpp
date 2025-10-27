#include "LowWater.h"
#include "../prototype/LivingPlant.h"

int LowWater::water(LivingPlant *plant)
{


    plant->setWaterLevel(plant->getWaterLevel() + waterAmount);
    return waterAmount;
}

int LowWater::getID()
{
    return 1;
}

LowWater::LowWater()
{
    waterAmount = 35;
}