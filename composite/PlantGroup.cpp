#include "PlantGroup.h"
#include "../observer/Observer.h"
#include "../prototype/LivingPlant.h"
#include <sstream>

PlantGroup::PlantGroup()
    : PlantComponent(0.0, 0, 0) 
{};

PlantGroup::~PlantGroup(){
    std::list<PlantComponent*>::iterator itr = plants.begin();
    while(itr != plants.end()){
    delete (*itr)->getDecorator();
    itr++;
    // should work.
    }
}

PlantGroup::PlantGroup(const PlantGroup& other)
    : PlantComponent(other)
{

    for (PlantComponent* component : other.plants){
        PlantComponent* clonedComponent = component->clone();
        this->plants.push_back(clonedComponent);
    }

}

void PlantGroup::setOutside(){
    if (!plants.empty()){
        for (PlantComponent* component : plants){
            component->setOutside();
        }
    }
};

void PlantGroup::water(){
    if (!plants.empty()){
        for (PlantComponent* component : plants){
            component->water();
        }
    }
};

std::string PlantGroup::getInfo(){
    std::stringstream ss;

    ss << "\n*** Plant Group ***" << std::endl;
    ss << "---------------------------------" << std::endl;
    int counter = 0;
    for (PlantComponent* component : plants){
        counter++;
        ss << component->getInfo();

        ss << "\n--- End of Component" + std::to_string(counter) + " ---\n"; 
    }

    ss << "---------------------------------" << std::endl;
    return ss.str();
};

PlantComponent* PlantGroup::clone(){
    return new PlantGroup(*this);

};

void PlantGroup::update(){
    for (PlantComponent* component : plants){
        component->update();
    }
};

int PlantGroup::affectWater(){
    int totalAffected = 0;
    
    for (PlantComponent* component : plants){
        totalAffected += component->affectWater(); 
    }
    
    return totalAffected;
};

int PlantGroup::affectSunlight(){
    int totalAffected = 0;
    
    for (PlantComponent* component : plants){
        totalAffected += component->affectSunlight();
    }
    
    return totalAffected;
};

double PlantGroup::getPrice(){
    double totalPrice = this->price;
    for (PlantComponent* component : plants){
        totalPrice += component->getPrice();
    }
    return totalPrice;
};

void PlantGroup::addAttribute(PlantComponent* attribute){
    for (PlantComponent* component : plants){
        PlantComponent* clonedAttribute = attribute->clone(); 
        component->addAttribute(clonedAttribute);
    }
};


void PlantGroup::addComponent(PlantComponent* component) {
    plants.push_back(component);
}

std::string PlantGroup::getName(){
    std::stringstream ss;
    ss << "Plant Group: ";

    int count = 0;
    for (PlantComponent* component : plants) {
        if (count < 3){
            ss << component->getName() << ", ";
        }
        count++;
    }
    
    std::string name = ss.str();
    if (name.length() > 2){
        name.pop_back();
        name.pop_back();
    }
    return name;
};

//observer stuff

void PlantGroup::attach(Observer* careTaker){

};

void PlantGroup::detach(Observer* careTaker){

};

void PlantGroup::waterNeeded(){

};

void PlantGroup::sunlightNeeded(){
};

void PlantGroup::stateUpdated(){
};