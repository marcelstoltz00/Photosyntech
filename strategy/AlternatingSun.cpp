#include "AlternatingSun.h"
#include "../prototype/LivingPlant.h"

int AlternatingSun::addSun(LivingPlant* plant) {
    intensity= intensity == 4 ? 6 : 4;
    hoursNeeded = hoursNeeded == 4 ? 6 : 4;

    int applied = intensity * hoursNeeded;
         plant->setSunExposure(plant->getSunExposure() + applied);
    return applied;
}

int AlternatingSun::getID() {
    return 4;
}

AlternatingSun::AlternatingSun() {
    intensity = 4;   
    hoursNeeded = 4; 
}