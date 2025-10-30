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
//This is updated to add more to the suggestion. also checks directly from the inventory so i replaced the other temp list i made. it still randomised though.
string Staff::assistSuggestion()
{
    Inventory* inventory = Inventory::getInstance();
    if (!inventory) {
        return "Sorry, I can't access our inventory right now. Please check back later.\n";
    }

    PlantGroup* currentInventory = inventory->getInventory();
    if (!currentInventory || currentInventory->getPlants()->empty()) {
        return "I'm sorry, but our inventory is currently empty. Please check back later when we have new plants in stock.\n";
    }

    auto plants = currentInventory->getPlants();
    
    std::vector<PlantComponent*> availablePlants;
    for (auto plant : *plants) {
        if (plant) {
            availablePlants.push_back(plant);
        }
    }

    if (availablePlants.empty()) {
        return "We have plants in inventory, but none are available for recommendations at the moment.\n";
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int idx = std::rand() % availablePlants.size();
    PlantComponent* selectedPlant = availablePlants[idx];
    std::string plantType = selectedPlant->getName();

    std::string recommendation = "\nYou know, based on what we have in stock right now, I'd really recommend our " + plantType + ".\n";
    
    if (plantType.find("Maple") != std::string::npos || 
        plantType.find("Pine") != std::string::npos || 
        plantType.find("Cherry") != std::string::npos) {
        recommendation += "It's a tree, so it's more of a long-term investment for your garden. ";
        if (plantType.find("Maple") != std::string::npos) 
            recommendation += "The Maple gives you those gorgeous fall colors - really transforms your yard in autumn.";
        else if (plantType.find("Pine") != std::string::npos)
            recommendation += "The Pine stays green all year round and doesn't need much maintenance, which is great if you're busy.";
        else if (plantType.find("Cherry") != std::string::npos)
            recommendation += "The Cherry Blossom puts on an amazing show in spring - the flowers are just spectacular.";
        recommendation += " Just keep in mind it'll need regular watering and plenty of space to grow.\n";
        
    } else if (plantType.find("Rose") != std::string::npos || 
               plantType.find("Sunflower") != std::string::npos || 
               plantType.find("Lavender") != std::string::npos) {
        recommendation += "This is one of our flowering plants - perfect if you want some seasonal color. ";
        if (plantType.find("Rose") != std::string::npos)
            recommendation += "Roses are classic, though watch out for the thorns when you're pruning them.";
        else if (plantType.find("Sunflower") != std::string::npos) 
            recommendation += "Sunflowers grow really fast and the bees absolutely love them - great for your garden ecosystem.";
        else if (plantType.find("Lavender") != std::string::npos)
            recommendation += "Lavender smells amazing, doesn't need much water, and the purple flowers are just lovely.";
        recommendation += " They do best with regular watering and lots of sunlight.\n";
        
    } else if (plantType.find("Cactus") != std::string::npos || 
               plantType.find("Jade") != std::string::npos ||
               plantType.find("Succulent") != std::string::npos) {
        recommendation += "If you're looking for something low-maintenance, this is perfect. ";
        if (plantType.find("Cactus") != std::string::npos)
            recommendation += "Cacti are practically indestructible - they store water so you can't really overwater them.";
        else if (plantType.find("Jade") != std::string::npos)
            recommendation += "Jade plants are supposed to bring good luck, and they're super easy to grow from cuttings.";
        else
            recommendation += "Succulents are great for beginners - they're hardy and don't need constant attention.";
        recommendation += " They don't need much attention and do great indoors or in sunny spots.\n";
    } else {
        recommendation += "This is one of our quality plants that's been growing well in our nursery. ";
        recommendation += "It's a great choice that should adapt well to most home environments.\n";
    }

    recommendation += "This particular " + plantType + " is priced at R" + 
                     std::to_string(static_cast<int>(selectedPlant->getPrice())) + 
                     " and comes with our quality guarantee.\n";

    std::vector<std::string> expertiseComments = {
        "We've been getting great feedback on these from other customers.",
        "I actually have one of these at home myself - they're really easy to care for.",
        "These just came in fresh this week, so you're getting the pick of the bunch.",
        "This time of year is perfect for planting these - they'll establish really well.",
        "I've been caring for these myself and they're in excellent health.",
        "This variety has been particularly popular with our customers lately."
    };
    
    int commentIdx = std::rand() % expertiseComments.size();
    recommendation += expertiseComments[commentIdx] + " Would you like me to show you where we keep them?\n";
    
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
    return receipt.str();
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
