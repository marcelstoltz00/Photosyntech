#include "Vegetative.h"

#include "../singleton/Singleton.h"
#include "Mature.h"
#include <algorithm>

void Vegetative::grow(LivingPlant *plant) {
  plant->setAge(plant->getAge() + 1);
  double waterusage = 5.0;

  std::string *currentSeason =
      Inventory::getInstance()->getSeason()->getState();
  std::string *plantSeason = plant->getSeason()->getState();

 if (*currentSeason == *plantSeason) {
    waterusage *= 1.0;
  } else {
    if (*currentSeason == "Spring Season")
      waterusage *= 0.9;
    else if (*currentSeason == "Summer Season")
      waterusage *= 1.3;
    else if (*currentSeason == "Autumn Season")
      waterusage *= 1.0;
    else if (*currentSeason == "Winter Season")
      waterusage *= 0.8;
  }

  plant->setWaterLevel(plant->getWaterLevel() - waterusage);
  plant->setHealth(plant->getHealth() - 10);

  if (plant->getAge() >= 30 && plant->getSunExposure() >= 40) {
    plant->setHealth(plant->getHealth() + 5);
  }

  if (plant->getAge() >= 30 && plant->getHealth() >= 60 &&
      plant->getWaterLevel() >= 40 && plant->getSunExposure() >= 50) {

    plant->setWaterLevel(40);
    plant->setHealth(std::max(plant->getHealth(), 60));
    plant->setSunExposure(60);

    plant->setMaturity(Mature::getID());
  }
}

std::string Vegetative::getImagePath(LivingPlant *plant) {
  std::string plantName = plant->getName();
  plantName.erase(std::remove(plantName.begin(), plantName.end(), ' '),
                  plantName.end());
  return "docs/images/" + plantName + std::to_string(getID()) + ".png";
}
