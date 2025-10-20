#include "LivingPlant.h"
#include "PlantComponent.h"
#include "Singleton.h";

LivingPlant::LivingPlant(std::string name, double price, int waterAffect, int sunAffect)
    : PlantComponent(price, waterAffect, sunAffect), 
    //remember to change to getString() after Wilmar fixes getSeason()
      name(*Inventory::getInstance()->getSeason("")),
      season(*Inventory::getInstance()->getSeason("")),
      age(0), 
      health(0), 
      waterLevel(0), 
      sunExposure(0),
      maturityState(nullptr), 
      waterStrategy(nullptr), 
      sunStrategy(nullptr)
{};

LivingPlant::LivingPlant(const LivingPlant& other) 
    : PlantComponent(other),

      name(other.name),
      age(other.age),
      health(other.health),
      waterLevel(other.waterLevel),
      sunExposure(other.sunExposure),
      season(other.season),

      maturityState(other.maturityState),
      waterStrategy(other.waterStrategy),
      sunStrategy(other.sunStrategy)
{};

void LivingPlant::setAge(int age){
    this->age = age;
};

void LivingPlant::setHealth(int health){
    this->health = health;
};

void LivingPlant::setWaterLevel(int waterLevel){
    this->waterLevel = waterLevel;
};

void LivingPlant::setSunExposure(int sunExposure){
    this->sunExposure = sunExposure;
};

void LivingPlant::setWaterStrategy(int strategy){
    //waiting on wilmar's final implementation for flyweight
};

void LivingPlant::setSunStrategy(int strategy){
    //waiting on wilmar's final implementation for flyweight
};

void LivingPlant::setMaturity(int state){
    //waiting on wilmar's final implementation for flyweight
};

void LivingPlant::addAttribute(PlantAttributes* attribute){
//stub since this is the ConcreteComponent
};

int LivingPlant::getAge(){
    return this->age;
};

std::string LivingPlant::getName(){
    return *name.getState();
};

int LivingPlant::getAffectSunlight(){
    return this->affectSunValue;
};

int LivingPlant::getAffectWater(){
    return this->affectWaterValue;
};

double LivingPlant::getPrice(){
    return this->price;
};

std::string LivingPlant::getInfo(){
    std::string plantName = *name.getState();
    std::string baseInfo;

    baseInfo += "Name: " + plantName + "\n";
    baseInfo += "Status: Basic Plant Component\n";
    baseInfo += "--------------------------------------\n";
    baseInfo += "Health: " + std::to_string(health) + "\n";
    baseInfo += "Age: " + std::to_string(age) + " days\n";
    baseInfo += "Water Level: " + std::to_string(waterLevel) + "\n";
    baseInfo += "Sun Exposure: " + std::to_string(sunExposure) + "\n";
    baseInfo += "Base Price: R" + std::to_string(PlantComponent::price) + "\n";
    baseInfo += "Water Affection: " + std::to_string(PlantComponent::affectWaterValue) + "\n";
    baseInfo += "Sun Affection: " + std::to_string(PlantComponent::affectSunValue) + "\n";
    
    return baseInfo;
};



PlantComponent* LivingPlant::clone(){
    return new LivingPlant(*this);
};