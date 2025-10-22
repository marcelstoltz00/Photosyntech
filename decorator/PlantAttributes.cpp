#include "PlantAttributes.h"
#include <sstream>

PlantAttributes::PlantAttributes(std::string name, double price, int waterAffect, int sunAffect)
    : PlantComponent(price, waterAffect, sunAffect),

      nextComponent(nullptr),
      name(Inventory::getInstance()->getString(name)) {

      };

PlantAttributes::PlantAttributes(const PlantAttributes &other)
    : PlantComponent(other),
      nextComponent(other.nextComponent->clone()),
      name(other.name) {};

void PlantAttributes::water()
{
    if (nextComponent)
        nextComponent->water();
};

void PlantAttributes::setOutside()
{
    if (nextComponent)
        nextComponent->setOutside();
};

void PlantAttributes::update()
{
    if (nextComponent)
        nextComponent->update();
};

std::string PlantAttributes::getInfo()
{
    std::string baseInfo = (nextComponent != nullptr) ? nextComponent->getInfo() : "";
    std::stringstream ss;
    ss << baseInfo;
    ss << " -> Decorated with: " << *name->getState() << " (+R" << this->price << ")\n";
    return ss.str();
};

double PlantAttributes::getPrice()
{
    double nextPrice = (nextComponent != nullptr) ? nextComponent->getPrice() : 0.0;
    return this->price + nextPrice;
};

std::string PlantAttributes::getName()
{
    return *name->getState();
};

int PlantAttributes::affectSunlight()
{
    int baseAffect = (nextComponent) ? nextComponent->affectSunlight() : 0;
    return baseAffect + this->affectSunValue;
};

int PlantAttributes::affectWater()
{
    int baseAffect = (nextComponent) ? nextComponent->affectWater() : 0;
    return baseAffect + this->affectWaterValue;
};

void PlantAttributes::addAttribute(PlantComponent *attribute)
{
    if (nextComponent == nullptr)
        nextComponent = attribute;
    else
    {
        attribute->addAttribute(nextComponent);
        this->nextComponent = attribute;
    }
};