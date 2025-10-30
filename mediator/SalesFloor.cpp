#include "SalesFloor.h"
#include "Staff.h"
#include "Customer.h"
#include "../singleton/Singleton.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructs a new SalesFloor mediator.
 */
SalesFloor::SalesFloor()
{
    std::srand(std::time(0));
    std::cout << "SalesFloor: Sales floor mediator initialized" << std::endl;
}

/**
 * @brief Routes customer assistance requests to available sales staff.
 * @param customer Pointer to the User requesting sales assistance.
 */
string SalesFloor::getAssistance(User *customer)
{
    Customer *cust = dynamic_cast<Customer *>(customer);
    if (cust == 0)
    {
        std::cout << "SalesFloor: Invalid customer type for sales assistance" << std::endl;
        return "SalesFloor: Invalid customer type for sales assistance";
    }

    std::cout << "SalesFloor: Routing purchase request from customer" << std::endl;

    // get staff list directly from Singleton
    std::vector<Staff *> &staffList = *(Inventory::getInstance()->getStaff());

    if (staffList.empty())
    {
        std::cout << "SalesFloor: No staff available, customer must wait" << std::endl;
        return "SalesFloor: No staff available, customer must wait";
    }

    // random staff selection
    int randomIndex = std::rand() % staffList.size();
    Staff *availableStaff = staffList[randomIndex];

    std::cout << "SalesFloor: Assigning customer to staff member " << randomIndex << std::endl;

    PlantGroup *basket = cust->getBasket();
    if (basket != 0)
    {
        return availableStaff->assistPurchases(basket);
    }
    else
    {
        std::cout << "SalesFloor: Customer basket is empty - no purchase to process" << std::endl;
        return "SalesFloor: Customer basket is empty - no purchase to process";
    }
}

/**
 * @brief Coordinates staff assistance for sales operations.
 */
void SalesFloor::assist()
{
    std::cout << "SalesFloor: Coordinating ongoing sales operations" << std::endl;

    // get lists directly from Singleton
    std::vector<Staff *> &staffList = *(Inventory::getInstance()->getStaff());
    std::vector<Customer *> &customerList = *(Inventory::getInstance()->getCustomers());

    // report current system status
    // STAFF
    if (staffList.empty())
    {
        std::cout << "SalesFloor: No sales staff available" << std::endl;
    }
    else
    {
        std::cout << "SalesFloor: " << staffList.size() << " sales staff members available" << std::endl;
    }
    // CUSTOMER
    if (customerList.empty())
    {
        std::cout << "SalesFloor: No customers currently in system" << std::endl;
    }
    else
    {
        std::cout << "SalesFloor: " << customerList.size() << " customers in system" << std::endl;
    }
}
