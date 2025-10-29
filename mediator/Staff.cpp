#include "Staff.h"
#include "../composite/PlantGroup.h"
#include "../singleton/Singleton.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

/**
 * @brief Provides a plant recommendation to a customer.
 *
 * This method simulates staff assistance through the mediator by randomly
 * selecting a plant from a temporary list of plants spanning all seasons.
 * The recommendation is printed to standard output. Later, this can be
 * extended to use Flyweight instances for memory-efficient plant names
 * or season-aware recommendations.
 *
 * **Behavior:**
 * - Retrieves the singleton Inventory instance (not strictly needed here
 *   but kept for future integration with Flyweight/factories).
 * - Defines a temporary vector of plant names across all four seasons.
 * - Randomly selects one plant from the vector.
 * - Prints the recommendation string to the console.
 *
 * @note Currently, this function only outputs a string and does not return
 * any object or interact with customer baskets. Can be extended post-MVP
 * to integrate with Flyweight and plant builders.
 */
Staff::Staff() : User()
{
    this->name = "Staff member";
}

Staff::Staff(std::string name) : User(name)
{
    this->name = name;
}

string Staff::assistSuggestion()
{
    Inventory *inventory = Inventory::getInstance();
    if (!inventory)
        return "No inventory";

    // Temporary plant list for all seasons, can be expanded as needed with flyweights
    std::vector<std::string> plantKeys = {
        "Sunflower", "Rose", "Jade Plant", "Maple",
        "Cactus", "Cherry Blossom", "Lavender", "Pine"};

    // Randomly select a plant
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int idx = std::rand() % plantKeys.size();

    std::string recommendation = this->name + ": recommends the " + plantKeys[idx] + ".";
    std::cout << recommendation << std::endl;
    return recommendation;
}

/**
 * @brief Assists customers with purchases of a PlantGroup.
 *
 * This method would typically communicate with a sales floor mediator
 * to handle purchase transactions.
 *
 * @param plants Pointer to the PlantGroup being purchased.
 */
string Staff::assistPurchases(PlantGroup *basket)
{
    if (!basket)
        return "Invalid basket provided";

    std::ostringstream receipt;
    receipt << "Purchase Receipt:\n";
    receipt << basket->getInfo();
    receipt << "Total price: " << basket->getPrice() << "\n";
    delete basket;
    // std::cout << receipt.str() << std::endl;
    return receipt.str();
    // Remove purchased plants from system scope
}

/**
 * @brief Receives notification that a plant needs water.
 *
 * Implements the Observer interface. Staff reacts to the notification
 * by printing a message and performing the watering action.
 *
 * @param plant Pointer to the LivingPlant requiring water.
 */
void Staff::getWaterUpdate(PlantComponent *plant)
{
    if (plant)
    {
        int oldWater = plant->getWaterValue();
        plant->water();
        cout << "Plant [" << plant->getName() << "] has had its water updated by " << this->name << endl;
        cout << "The water level was " << oldWater << " and is now " << plant->getWaterValue() << endl;
    }
}

/**
 * @brief Receives notification that a plant needs sunlight.
 *
 * Implements the Observer interface. Staff reacts by placing the plant outside.
 *
 * @param plant Pointer to the LivingPlant requiring sun exposure.
 */
void Staff::getSunUpdate(PlantComponent *plant)
{
    if (plant)
    {
        int oldSun = plant->getSunlightValue();
        plant->setOutside();
        cout << "Plant [" << plant->getName() << "] has had its sunlight updated by " << this->name << endl;
        cout << "The sun level was " << oldSun << " and is now " << plant->getSunlightValue() << endl;
    }
}

/**
 * @brief Receives notification that a plant's state has been updated.
 *
 * Implements the Observer interface. Staff can respond by inspecting
 * the plant's state and taking any needed actions.
 *
 * @param plant Pointer to the LivingPlant with updated state.
 */
void Staff::getStateUpdate(PlantComponent *plant)
{
    if (plant)
    {
        cout << "Checking State of [" << plant->getName() << "]" << endl;

        if (plant->getDecorator())
        {
            cout << plant->getDecorator()->getInfo() << endl;
        }
        else
        {
            cout << "decroator is null" << endl;
            cout << plant->getInfo() << endl;
        }
    }
}
