#include "Vegetative.h"

#include "../singleton/Singleton.h"
#include "Mature.h"
#include <algorithm>

void Vegetative::grow(LivingPlant *plant) {
  plant->setAge(plant->getAge() + 1);
  double waterusage = 2.0;

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

  if (plant->getWaterLevel() >= 30 && plant->getSunExposure() >= 40)
  {
    plant->setHealth(plant->getHealth() + 5);
  }
  if (plant->getWaterLevel() <= 10 || plant->getSunExposure() <= 10)
    plant->setHealth(plant->getHealth() - 5);


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
  return "../external/ftxui-image-view/imgs/" + plantName + std::to_string(getID()) + ".png";
}

