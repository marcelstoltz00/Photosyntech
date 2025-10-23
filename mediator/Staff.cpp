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
void Staff::assistSuggestion() {
    Inventory* inventory = Inventory::getInstance();
    if (!inventory) return;

    // Temporary plant list for all seasons, can be expanded as needed with flyweights
    std::vector<std::string> plantKeys = {
        "Rose", "Tulip", "Peony", "Bougainvillea",
        "Sunflower", "Hibiscus", "Century Plant", "Agave", "Zinnia",
        "Japanese Barberry", "Chrysanthemum", "Hawthorn", "Sedum",
        "Cactus", "Opuntia", "Juniper", "Yucca", "Winter Jasmine"
    };

    // Randomly select a plant
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int idx = std::rand() % plantKeys.size();

    std::string recommendation = "I recommend the " + plantKeys[idx] + ".";
    std::cout << recommendation << std::endl;
}


/**
 * @brief Assists customers with purchases of a PlantGroup.
 *
 * This method would typically communicate with a sales floor mediator
 * to handle purchase transactions.
 *
 * @param plants Pointer to the PlantGroup being purchased.
 */
void Staff::assistPurchases(PlantGroup* basket) {
    if (!basket) return;

    std::ostringstream receipt;
    receipt << "Purchase Receipt:\n";
    receipt << basket->getInfo();
    receipt << "Total price: " << basket->getPrice() << "\n";

    std::cout << receipt.str() << std::endl;

    // Remove purchased plants from system scope
    delete basket;
}

/**
 * @brief Receives notification that a plant needs water.
 *
 * Implements the Observer interface. Staff reacts to the notification
 * by printing a message and performing the watering action.
 *
 * @param plant Pointer to the LivingPlant requiring water.
 */
void Staff::getWaterUpdate(LivingPlant* plant) {
    if (!plant) return;
    std::cout << "Staff received water update for plant: " << plant->getName() 
              << " (Water level: " << plant->getWaterLevel() << ")" << std::endl;
    plant->water();
    std::cout << "Staff watered plant: " << plant->getName() << std::endl;
}

/**
 * @brief Receives notification that a plant needs sunlight.
 *
 * Implements the Observer interface. Staff reacts by placing the plant outside.
 *
 * @param plant Pointer to the LivingPlant requiring sun exposure.
 */
void Staff::getSunUpdate(LivingPlant* plant) {
    if (!plant) return;
    std::cout << "Staff received sunlight update for plant: " << plant->getName()
              << " (Sun exposure: " << plant->getSunExposure() << ")" << std::endl;
    plant->setOutside();
    std::cout << "Staff placed plant outside: " << plant->getName() << std::endl;
}

/**
 * @brief Receives notification that a plant's state has been updated.
 *
 * Implements the Observer interface. Staff can respond by inspecting
 * the plant's state and taking any needed actions.
 *
 * @param plant Pointer to the LivingPlant with updated state.
 */
void Staff::getStateUpdate(LivingPlant* plant) {
    if (!plant) return;
    std::cout << "Staff received state update for plant: " << plant->getName()
              << " (Health: " << plant->getHealth() << ", Age: " << plant->getAge() << ")" << std::endl;
    // Optional: React to state, e.g., water or move outside depending on strategy
    
}
