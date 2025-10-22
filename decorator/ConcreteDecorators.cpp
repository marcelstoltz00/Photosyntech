#include "customerDecorator/LargePot.h"
#include "customerDecorator/PlantCharm.h"
#include "customerDecorator/RedPot.h"
#include "customerDecorator/ShopThemedCharm.h"

#include "plantDecorator/Autumn.h"
#include "plantDecorator/LargeFlowers.h"
#include "plantDecorator/LargeLeaf.h"
#include "plantDecorator/LargeStem.h"
#include "plantDecorator/SmallFlowers.h"
#include "plantDecorator/SmallLeaf.h"
#include "plantDecorator/SmallStem.h"
#include "plantDecorator/Spring.h"
#include "plantDecorator/Summer.h"
#include "plantDecorator/Thorns.h"
#include "plantDecorator/Winter.h"

LargePot::LargePot()
    : PlantAttributes("Large Pot", 25.00, 0, 0)
{}

LargePot::LargePot(const LargePot &other) 
    : PlantAttributes(other)
{}

PlantComponent* LargePot::clone(){
    return new LargePot(*this);
}

PlantCharm::PlantCharm()
    : PlantAttributes("Standard Plant Charm", 10.00, 0, 0)
{}

PlantCharm::PlantCharm(const PlantCharm &other) 
    : PlantAttributes(other)
{}

PlantComponent* PlantCharm::clone(){
    return new PlantCharm(*this);
}

RedPot::RedPot()
    : PlantAttributes("Red Clay Pot", 15.00, 0, 0)
{}

RedPot::RedPot(const RedPot &other) 
    : PlantAttributes(other)
{}

PlantComponent* RedPot::clone(){
    return new RedPot(*this);
}

ShopThemedCharm::ShopThemedCharm()
    : PlantAttributes("Cute Charm", 20.00, 0, 0)
{}

ShopThemedCharm::ShopThemedCharm(const ShopThemedCharm &other) 
    : PlantAttributes(other)
{}

PlantComponent* ShopThemedCharm::clone(){
    return new ShopThemedCharm(*this);
}

Autumn::Autumn()
    : PlantAttributes("Autumn Season", 0.00, 0, 0)
{}

Autumn::Autumn(const Autumn &other) 
    : PlantAttributes(other)
{}

PlantComponent* Autumn::clone(){
    return new Autumn(*this);
}

LargeFlowers::LargeFlowers()
    : PlantAttributes("Large Flowers", 5.00, 1, 1)
{}

LargeFlowers::LargeFlowers(const LargeFlowers &other) 
    : PlantAttributes(other)
{}

PlantComponent* LargeFlowers::clone(){
    return new LargeFlowers(*this);
}

LargeLeaf::LargeLeaf()
    : PlantAttributes("Large Leaves", 3.00, 1, 0)
{}

LargeLeaf::LargeLeaf(const LargeLeaf &other) 
    : PlantAttributes(other)
{}

PlantComponent* LargeLeaf::clone(){
    return new LargeLeaf(*this);
}

LargeStem::LargeStem()
    : PlantAttributes("Large Stem", 2.00, 0, 0)
{}

LargeStem::LargeStem(const LargeStem &other) 
    : PlantAttributes(other)
{}

PlantComponent* LargeStem::clone(){
    return new LargeStem(*this);
}

SmallFlowers::SmallFlowers()

    : PlantAttributes("Small Flowers", 1.00, 0, 0)
{}

SmallFlowers::SmallFlowers(const SmallFlowers &other) 
    : PlantAttributes(other)
{}

PlantComponent* SmallFlowers::clone(){
    return new SmallFlowers(*this);
}

SmallLeaf::SmallLeaf()
    : PlantAttributes("Small Leaves", 1.00, -1, 0)
{}

SmallLeaf::SmallLeaf(const SmallLeaf &other) 
    : PlantAttributes(other)
{}

PlantComponent* SmallLeaf::clone(){
    return new SmallLeaf(*this);
}

SmallStem::SmallStem()
    : PlantAttributes("Small Stem", 0.00, 0, 0)
{}

SmallStem::SmallStem(const SmallStem &other) 
    : PlantAttributes(other)
{}

PlantComponent* SmallStem::clone(){
    return new SmallStem(*this);
}

Spring::Spring()
    : PlantAttributes("Spring Season", 0.00, 0, 0)
{}

Spring::Spring(const Spring &other) 
    : PlantAttributes(other)
{}

PlantComponent* Spring::clone(){
    return new Spring(*this);
}

Summer::Summer()
    : PlantAttributes("Summer Season", 0.00, 0, 0)
{}

Summer::Summer(const Summer &other) 
    : PlantAttributes(other)
{}

PlantComponent* Summer::clone(){
    return new Summer(*this);
}

Thorns::Thorns()
    : PlantAttributes("Thorns/Spikes", 5.00, 0, -1)
{}

Thorns::Thorns(const Thorns &other) 
    : PlantAttributes(other)
{}

PlantComponent* Thorns::clone(){
    return new Thorns(*this);
}

Winter::Winter()
    : PlantAttributes("Winter Season", 0.00, 0, 0)
{}

Winter::Winter(const Winter &other) 
    : PlantAttributes(other)
{}

PlantComponent* Winter::clone(){
    return new Winter(*this);
}