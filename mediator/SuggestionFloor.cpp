#include "SuggestionFloor.h"
#include "Staff.h"
#include "Customer.h"
#include "../singleton/Singleton.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructs a new SuggestionFloor mediator.
 */
SuggestionFloor::SuggestionFloor()
{
    std::srand(std::time(0));
    std::cout << "SuggestionFloor: Suggestion floor mediator initialized" << std::endl;
}

/**
 * @brief Routes customer suggestion requests to available staff.
 * @param customer Pointer to the User requesting suggestions.
 */
void SuggestionFloor::getAssistance(User *customer)
{
    std::cout << "SuggestionFloor: Routing suggestion request from customer" << std::endl;

    // Get staff list directly from Singleton
    std::vector<Staff *> &staffList = *(Inventory::getInstance()->getStaff());

    if (staffList.empty())
    {
        std::cout << "SuggestionFloor: No staff available for suggestions, customer must wait" << std::endl;
        return;
    }

    // Random staff selection
    int randomIndex = std::rand() % staffList.size();
    Staff *availableStaff = staffList[randomIndex];

    std::cout << "SuggestionFloor: Assigning customer to staff member " << randomIndex << " for suggestions" << std::endl;

    // Use the existing assistSuggestion() method
    availableStaff->assistSuggestion();
}

/**
 * @brief Coordinates staff assistance for suggestion operations.
 */
void SuggestionFloor::assist()
{
    std::cout << "SuggestionFloor: Coordinating ongoing suggestion operations" << std::endl;

    // Get lists directly from Singleton
    std::vector<Staff *> &staffList = *(Inventory::getInstance()->getStaff());
    std::vector<Customer *> &customerList = *(Inventory::getInstance()->getCustomers());

    // Reports the current system status
    //STAFF
    if (staffList.empty())
    {
        std::cout << "SuggestionFloor: No suggestion staff available" << std::endl;
    }
    else
    {
        std::cout << "SuggestionFloor: " << staffList.size() << " suggestion staff members available" << std::endl;
    }
    //CUSTOMER
    if (customerList.empty())
    {
        std::cout << "SuggestionFloor: No customers currently seeking suggestions" << std::endl;
    }
    else
    {
        std::cout << "SuggestionFloor: " << customerList.size() << " customers may need plant care suggestions" << std::endl;
    }
}
