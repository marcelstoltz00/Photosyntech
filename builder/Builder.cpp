#include "Builder.h"

PlantComponent *Builder::getResult()
{

    if (plant && plant->getDecorator())
        return plant->getDecorator()->clone();
    else
    {
        throw "Plant has not been constructed";
        return NULL;
    }

}
Builder::~Builder()
{
    if (plant)
    {
        delete plant;
        plant = NULL;
    }
}