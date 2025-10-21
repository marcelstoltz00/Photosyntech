#include "Director.h"

void Director::construct() {
    builder->createObject();
    builder->assignWaterStrategy();
    builder->assignSunStrategy();
    builder->assignMaturityState();
    builder->addDecorators();
}
LivingPlant* Director::getPlant() {
    return builder->getResult();
}