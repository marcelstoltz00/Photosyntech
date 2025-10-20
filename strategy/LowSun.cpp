#include "LowSun.h"
#include "../prototype/LivingPlant.h"

int LowSun::addSun(LivingPlant* plant) {
    int applied = intensity * hoursNeeded;
     plant->setSunExposure(plant->getSunExposure() + applied);
    return applied;
}

int LowSun::getID() {
    return 1;
}

LowSun::LowSun() {
    intensity = 2;    // low intensity
    hoursNeeded = 3;  // short exposure
}
