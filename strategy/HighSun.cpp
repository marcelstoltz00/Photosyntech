#include "HighSun.h"
#include "../prototype/LivingPlant.h"

int HighSun::addSun(LivingPlant* plant) {
    int applied = intensity * hoursNeeded;
    // plant->addSunlight(applied);
    return applied;
}

int HighSun::getID() {
    return 3;
}

HighSun::HighSun() {
    intensity = 9;  
    hoursNeeded = 8; 
}
