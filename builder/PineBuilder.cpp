#include "PineBuilder.h"
#include "../strategy/HighSun.h"
#include "../strategy/LowWater.h"
#include "../prototype/Tree.h"
#include "../decorator/plantDecorator/SmallLeaf.h"
#include "../decorator/plantDecorator/LargeStem.h"
#include "../decorator/plantDecorator/Winter.h"
#include "../state/Seed.h"

PineBuilder::PineBuilder() : plant(nullptr)
{
}

void PineBuilder::createObject()
{
    if (!plant)
    {
        plant = new Tree();
    }
}

void PineBuilder::assignWaterStrategy()
{
    if (plant)
    {
        plant->setWaterStrategy(LowWater::getID());
    }
}

void PineBuilder::assignSunStrategy()
{
    if (plant)
    {
        plant->setSunStrategy(HighSun::getID());
    }
}

void PineBuilder::assignMaturityState()
{
    if (plant)
    {
        plant->setMaturity(Seed::getID());
    }
}

PlantComponent *PineBuilder::getResult()
{
    return plant->clone();
}

void PineBuilder::addDecorators() {
    if (plant) {
        PlantComponent *season = new Winter();
        plant->setSeason(Inventory::getInstance()->getString(season->getName()));
        plant->addAttribute(season);
        plant->addAttribute(new SmallLeaf());
        plant->addAttribute(new LargeStem());
    }
}
void PineBuilder::setUp()
{
    if (plant)
    {
        plant->setHealth(100);
        plant->setWaterLevel(40);
        plant->setSunExposure(80);
    }
}

PineBuilder::~PineBuilder()
{
}