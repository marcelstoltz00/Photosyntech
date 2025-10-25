#include "BasketMemento.h"
#include "Customer.h"
#include "../composite/PlantGroup.h"

BasketMemento::BasketMemento(Customer *customer)
	: basketExisted(customer->getBasket() != nullptr)
{
	// Capture current basket contents
	if (customer->getBasket() != nullptr)
	{
		// Get the list of plants from the basket
		std::list<PlantComponent *> *basketPlants = customer->getBasket()->getPlants();
		if (basketPlants != nullptr)
		{
			// Copy the plant pointers (shallow copy of list, not plants themselves)
			plants = *basketPlants;
		}
	}
}

BasketMemento::~BasketMemento()
{
	// No dynamic allocation to clean up
	// Plant pointers are not owned by this memento
	plants.clear();
}

void BasketMemento::restoreBasket(Customer *customer)
{
	if (basketExisted)
	{
		// Basket should have existed, restore contents
		PlantGroup *basket = customer->getBasket();
		if (basket == nullptr)
		{
			// Need to recreate basket - this shouldn't happen in normal usage
			// but handle it gracefully by clearing any existing basket
			customer->clearBasket();
		}
		else
		{
			// Clear current basket contents
			customer->clearBasket();

			// Restore each plant to the basket
			for (PlantComponent *plant : plants)
			{
				customer->addPlant(plant);
			}
		}
	}
	else
	{
		// Basket didn't exist, clear it
		customer->clearBasket();
	}
}

const std::list<PlantComponent *> &BasketMemento::getPlants() const
{
	return plants;
}

bool BasketMemento::didBasketExist() const
{
	return basketExisted;
}
