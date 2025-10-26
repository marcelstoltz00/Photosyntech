#include "CactusBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Succulent.h"
#include "../decorator/plantDecorator/SmallFlowers.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Thorns.h"
#include "../state/Seed.h"
#include "../decorator/plantDecorator/Summer.h"

CactusBuilder::CactusBuilder() : Builder()
{
}

void CactusBuilder::createObject()
{
    if (!plant)
    {
        plant = new Succulent("Cactus");
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

