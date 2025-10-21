#include "SalesFloor.h"
#include "Staff.h"
#include "Customer.h"
#include "../singleton/Singleton.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void getAssistance(User* customer) {
    Customer* cust = dynamic_cast<Customer*>(customer);
    if (cust ==NULL) {
        std::cout << "SuggestionFloor: Invalid customer type for suggestion assistance" << std::endl;
        return;
    }

    std::cout << "SuggestionFloor: Routing suggestion request from customer" << std::endl;
    
    //get staff list directly from Singleton
    std::vector<Staff*>& staffList = *(Inventory::getInstance()->getStaff());
    
    if (staffList.empty()) {
        std::cout << "SuggestionFloor: No staff available, customer must wait" << std::endl;
        return;
    }
    
    //random staff selection
    int randomIndex = std::rand() % static_cast<int>(staffList.size());
    Staff* availableStaff = staffList[randomIndex];
    
    std::cout << "SuggestionFloor: Assigning customer to staff member " << randomIndex << std::endl;
    
    availableStaff->assistSuggestion();
}

void assist() {
    std::cout << "SuggestionFloor: Coordinating ongoing suggestion operations" << std::endl;
    
    //get lists directly from Singleton
    std::vector<Staff*>& staffList = *(Inventory::getInstance()->getStaff());
    std::vector<Customer*>& customerList = *(Inventory::getInstance()->getCustomers());
    
    // Report current system status
    if (staffList.empty()) {
        std::cout << "SuggestionFloor: WARNING - No suggestion staff available" << std::endl;
    } else {
        std::cout << "SuggestionFloor: " << staffList.size() << " suggestion staff members available" << std::endl;
    }
    
    if (customerList.empty()) {
        std::cout << "SuggestionFloor: No customers currently in system" << std::endl;
    } else {
        std::cout << "SuggestionFloor: " << customerList.size() << " customers in system" << std::endl;
    }
}
