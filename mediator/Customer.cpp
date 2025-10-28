#include "Customer.h"
#include "Mediator.h"
#include "../composite/PlantGroup.h"
#include <iostream>

/**
 * @class Customer
 * @brief Concrete colleague representing a customer in the mediator pattern.
 *
 * Interacts with staff through mediators (sales floor, suggestion floor)
 * instead of direct coupling. Maintains a shopping basket and can request
 * suggestions or make purchases through coordinated interactions.
 */

/**
 * @brief Constructs a new Customer object.
 */
Customer::Customer() : basket(nullptr)
{
    name = "Customer";
}
Customer::Customer(string name) : basket(nullptr)
{
    this->name = name;
}

/**
 * @brief Destroys the Customer object and cleans up resources.
 */
Customer::~Customer()
{
    if (basket != nullptr)
    {
        std::cout << "Customer: Deleting unused basket with plants" << std::endl;
        delete basket;
    }
}

/**
 * @brief Requests plant care suggestions from staff via the mediator.
 */
void Customer::askForSuggestion()
{
    if (suggestionFloor != nullptr)
    {
        std::cout << "Customer: Requesting plant care suggestions" << std::endl;
        suggestionFloor->getAssistance(this);
    }
    else
    {
        std::cout << "Customer: No suggestion floor available" << std::endl;
    }
}

/**
 * @brief Initiates plant purchase transaction via the sales floor mediator.
 */
void Customer::purchasePlants()
{
    if (salesFloor != nullptr)
    {
        if (basket != nullptr)
        {
            std::cout << "Customer: Initiating plant purchase" << std::endl;
            salesFloor->getAssistance(this);
        }
        else
        {
            std::cout << "Customer: Cannot purchase - basket is empty" << std::endl;
        }
    }
    else
    {
        std::cout << "Customer: No sales floor available" << std::endl;
    }
}

/**
 * @brief Adds a plant to the customer's shopping basket.
 * @param plant Pointer to the PlantComponent to add.
 */
void Customer::addPlant(PlantComponent *plant)
{
    if (plant == nullptr)
    {
        std::cout << "Customer: Cannot add null plant to basket" << std::endl;
        return;
    }

    if (basket == nullptr)
    {
        basket = new PlantGroup();
        std::cout << "Customer: Created new shopping basket" << std::endl;
    }

    basket->addComponent(plant);
    std::cout << "Customer: Added plant to basket" << std::endl;
}

/**
 * @brief Performs a customer operation.
 */
void Customer::operation()
{
    std::cout << "Customer: Performing customer browsing operation" << std::endl;
}

/**
 * @brief Gets the customer's current shopping basket.
 * @return Pointer to the PlantGroup representing the basket
 */
PlantGroup *Customer::getBasket() const
{
    return basket;
}

/**
 * @brief Clears the customer's basket after purchase.
 */
void Customer::clearBasket()
{
    std::cout << "Customer: Clearing basket after successful purchase" << std::endl;
    if (basket != nullptr)
    {
        delete basket; // Added this line to prevent the memory leaks
        basket = nullptr;
    }
}
