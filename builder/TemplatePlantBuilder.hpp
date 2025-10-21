#ifndef TEMPLATEPLANTBUILDER_HPP
#define TEMPLATEPLANTBUILDER_HPP

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
class TemplatePlantBuilder {
public:
    TemplatePlantBuilder(int health, int water, int sun);
    void createObject();
    void assignWaterStrategy();
    void assignSunStrategy();
    void assignMaturityState();
    void setUp();
    PlantType* getResult();
    ~TemplatePlantBuilder();

private:
    PlantType* plant;
    int initialHealth;
    int initialWater;
    int initialSun;
};

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::TemplatePlantBuilder(
    int health, int water, int sun)
    : plant(nullptr), initialHealth(health), initialWater(water), initialSun(sun) {}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::createObject() {
    if (!plant) {
        plant = new PlantType();
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::assignWaterStrategy() {
    if (plant) {
        plant->setWaterStrategy(WaterStrategyType::getID());
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::assignSunStrategy() {
    if (plant) {
        plant->setSunStrategy(SunStrategyType::getID());
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::assignMaturityState() {
    if (plant) {
        plant->setMaturity(Seed::getID());
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
void TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::setUp() {
    if (plant) {
        plant->setHealth(initialHealth);
        plant->setWater(initialWater);
        plant->setSun(initialSun);
    }
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
PlantType* TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::getResult() {
    return plant;
}

template<typename PlantType, typename SunStrategyType, typename WaterStrategyType>
TemplatePlantBuilder<PlantType, SunStrategyType, WaterStrategyType>::~TemplatePlantBuilder() {
    // Plant deletion handled by Director
}

#endif // TEMPLATEPLANTBUILDER_HPP