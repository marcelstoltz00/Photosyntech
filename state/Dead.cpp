#include "Dead.h"
#include "LivingPlant.h"

void Dead::grow(LivingPlant* plant) {
    
    plant->setAge(plant->getAge() + 1);
}