#include "PlantMemento.h"
#include "../prototype/LivingPlant.h"
#include "MaturityState.h"

PlantMemento::PlantMemento(LivingPlant *plant)
	: age(plant->getAge()),
	  health(plant->getHealth()),
	  waterLevel(plant->getWaterLevel()),
	  sunExposure(plant->getSunExposure()),
	  name(plant->getName()),
	  basePrice(plant->getPrice())
{
	// Extract maturity state ID from the flyweight using efficient enum-based identification
	if (plant->maturityState != nullptr)
	{
		MaturityState *state = plant->maturityState->getState();
		maturityStateID = static_cast<int>(state->getStateType());
	}
	else
	{
		maturityStateID = 0; // Default to Seed (ID 0)
	}
}

PlantMemento::~PlantMemento()
{
	// No dynamic allocation, no cleanup needed
}

void PlantMemento::restoreState(LivingPlant *plant)
{
	plant->setAge(age);
	plant->setHealth(health);
	plant->setWaterLevel(waterLevel);
	plant->setSunExposure(sunExposure);
	plant->setMaturity(maturityStateID);
}

// Accessors for debugging/testing
int PlantMemento::getAge() const
{
	return age;
}

double PlantMemento::getHealth() const
{
	return health;
}

int PlantMemento::getWaterLevel() const
{
	return waterLevel;
}

int PlantMemento::getSunExposure() const
{
	return sunExposure;
}

int PlantMemento::getMaturityStateID() const
{
	return maturityStateID;
}

std::string PlantMemento::getName() const
{
	return name;
}

double PlantMemento::getBasePrice() const
{
	return basePrice;
}
