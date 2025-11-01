#include "Mature.h"

#include "../singleton/Singleton.h"
#include "Dead.h"
#include <algorithm>

void Mature::grow(LivingPlant *plant) {
  plant->setAge(plant->getAge() + 1);
  double waterusage = 3.0;

  Flyweight<std::string*>* currentSeasonFly = Inventory::getInstance()->getSeason();
  Flyweight<std::string*>* plantSeasonFly = plant->getSeason();
  
  if (currentSeasonFly != nullptr && plantSeasonFly != nullptr) {
    std::string *currentSeason = currentSeasonFly->getState();
    std::string *plantSeason = plantSeasonFly->getState();
    
    if (currentSeason != nullptr && plantSeason != nullptr) {
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
    }
  }

  plant->setWaterLevel(plant->getWaterLevel() - waterusage);

  if (plant->getWaterLevel() >= 30 && plant->getSunExposure() >= 40 ) {
    plant->setHealth(plant->getHealth() + 1);
  }

  if (plant->getAge() >= 120 || plant->getHealth() <= 0) {
    plant->setWaterLevel(0);
    plant->setHealth(0);
    plant->setSunExposure(0);

    plant->setMaturity(Dead::getID());
  }
}
std::string Mature::getImagePath(LivingPlant *plant) {
  std::string plantName = plant->getName();
  plantName.erase(std::remove(plantName.begin(), plantName.end(), ' '),
                  plantName.end());
  return "../docs/images/" + plantName + std::to_string(getID()) + ".png";
}