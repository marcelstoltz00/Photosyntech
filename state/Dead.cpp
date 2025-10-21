#include "Dead.h"

void Dead::grow(LivingPlant *plant)
{

    plant->setAge(plant->getAge() + 1);
}
