#include "Seed.h"

#include "../singleton/Singleton.h"
#include "Vegetative.h"
#include <algorithm>

void Seed::grow(LivingPlant *plant) {
  plant->setAge(plant->getAge() + 1);
  double waterusage = 3.0;

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
  plant->setHealth(plant->getHealth() - 9);

  if (plant->getWaterLevel() >= 40 && plant->getSunExposure() >= 20) {
    plant->setHealth(plant->getHealth() + 4);
  }

  if (plant->getAge() >= 7 && plant->getHealth() >= 50 &&
      plant->getWaterLevel() >= 50 && plant->getSunExposure() >= 30) {

    plant->setWaterLevel(25);
    plant->setHealth(std::max(plant->getHealth(), 50));
    plant->setSunExposure(50);
    plant->setMaturity(Vegetative::getID());
  }
}

std::string Seed::getImagePath(LivingPlant *plant) {
  std::string plantName = plant->getName();
  plantName.erase(std::remove(plantName.begin(), plantName.end(), ' '),
                  plantName.end());
  return "docs/images/" + plantName + std::to_string(getID()) + ".png";
}
