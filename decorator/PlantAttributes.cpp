#include "PlantAttributes.h"
#include <sstream>

PlantAttributes::PlantAttributes(PlantComponent* component, std::string name, double price, int waterAffect, int sunAffect)
    :  PlantComponent(price, waterAffect, sunAffect), 

      component(component), 
      name(Inventory::getInstance()->getString(name)){

};

PlantAttributes::PlantAttributes(const PlantAttributes &other)
    : PlantComponent(other), 
      component(other.component->clone()), 
      name(other.name)
{};

void PlantAttributes::affectSunlight(){
    component->affectSunlight();
};

void PlantAttributes::affectWater(){
    component->affectWater();
};

void PlantAttributes::water(){
    component->water();
};

void PlantAttributes::setOutside(){
    component->setOutside();
};

void PlantAttributes::update(){
    component->update();
};

std::string PlantAttributes::getInfo(){
    std::stringstream ss;
    ss << component->getInfo();
    ss << " -> Decorated with: " << *name->getState() << " (Price Mod: R " << this->price << ")" << "\n";
    return ss.str();
};

double PlantAttributes::getPrice(){
    return component->getPrice() + this->price;
};

std::string PlantAttributes::getName(){
    return component->getName();
};

int PlantAttributes::getAffectSunlight(){
    return component->getAffectSunlight();
};

int PlantAttributes::getAffectWater(){
    return component->getAffectWater();
};

void PlantAttributes::addAttribute(PlantAttributes* attribute){
    //goes to stub
    component->addAttribute(attribute);
};

PlantComponent* PlantAttributes::clone(){
    //check that this is correct for decorator
    PlantComponent* clonedComponent = this->component->clone();

    return new PlantAttributes(*this);
};