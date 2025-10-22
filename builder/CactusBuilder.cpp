#include "CactusBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Succulent.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Thorns.h"
#include "../state/Seed.h"
#include "../decorator/plantDecorator/Summer.h"

CactusBuilder::CactusBuilder() : plant(nullptr)
{
}

void CactusBuilder::createObject()
{
    if (!plant)
    {
        plant = new Succulent();
    }
}

void CactusBuilder::assignWaterStrategy()
{
    if (plant)
    {
        plant->setWaterStrategy(LowWater::getID());
    }
}

void CactusBuilder::assignSunStrategy()
{
    if (plant)
    {
        plant->setSunStrategy(HighSun::getID());
    }
}

void CactusBuilder::assignMaturityState()
{
    if (plant)
    {
        plant->setMaturity(Seed::getID());
    }
}

PlantComponent *CactusBuilder::getResult()
{
    if (!plant)
    {
        return NULL;
    }

    return plant->clone();
}

void CactusBuilder::addDecorators()
{

    // if (plant)
    // {
    //       season = new Summer(plant);
    //    plant->setDecorator(season);   
    //       season->AddDecorator(new SmallFlowers(plant));
    //    season->AddDecorator(new LargeStem(plant));
    //    season->AddDecorator(new Thorns(plant));
 
    // }
}

void CactusBuilder::setUp()
{
    if (plant)
    {
        plant->setHealth(100);
        plant->setWaterLevel(30);
        plant->setSunExposure(80);
    }
}

CactusBuilder::~CactusBuilder()
{
}