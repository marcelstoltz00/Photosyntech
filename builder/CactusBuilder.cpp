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

    return plant->getDecorator()->clone();
}

void CactusBuilder::addDecorators()
{

    if (plant)
    {
        PlantComponent *summer = new Summer();
        plant->setSeason(Inventory::getInstance()->getString(summer->getName()));
        plant->addAttribute(summer);
        plant->addAttribute(new SmallFlowers());
        plant->addAttribute(new LargeStem());
        plant->addAttribute(new Thorns());
    }
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
    if (plant)
    {
         delete plant->getDecorator();
        plant = nullptr;
    }
}