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
    //waiting on wilmar's final implementation for flyweight
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

};

int LivingPlant::getAge(){
    return this->age;
};

std::string LivingPlant::getName(){
    return *name.getState();
};

int LivingPlant::getAffectSunlight(){

};

int LivingPlant::getAffectWater(){

};

double LivingPlant::getPrice(){
    
};