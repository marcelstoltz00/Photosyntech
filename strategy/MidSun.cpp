#include "MidSun.h"
#include "../prototype/LivingPlant.h"

int MidSun::addSun(LivingPlant* plant) {
    int applied = intensity * hoursNeeded;
    // plant->addSunlight(applied);
    return applied;
}

int MidSun::getID() {
    return 2;
}

MidSun::MidSun() {
    intensity = 5;   
    hoursNeeded = 5; 
}
