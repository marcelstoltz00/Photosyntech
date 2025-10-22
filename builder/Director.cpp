#include "Director.h"
Director::Director(Builder* builder) : builder(builder) {
}

void Director::construct() {
    if (!builder) {
        return;
    }
    builder->createObject();
    builder->assignWaterStrategy();
    builder->assignSunStrategy();
    builder->assignMaturityState();
    builder->addDecorators();
    builder->setUp();
}
PlantComponent* Director::getPlant() {
    if (!builder) {
        return nullptr;
    }
    return builder->getResult();
}