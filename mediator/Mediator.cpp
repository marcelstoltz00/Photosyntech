#include "Mediator.h"
#include "../singleton/Singleton.h"
#include <iostream>

/**
 * @class Mediator
 * @brief Abstract mediator interface for coordinating colleague interactions.
 *
 * Provides base functionality for mediation while accessing staff and customer
 * lists directly from the Singleton instance.
 */

/**
 * @brief Default constructor for Mediator base class.
 */
Mediator::Mediator() {
    // No need to initialize lists here - they're in Singleton
}

/**
 * @brief Virtual destructor for proper polymorphic cleanup.
 */
Mediator::~Mediator() {
    std::cout << "Mediator: Cleaning up mediator resources" << std::endl;
}
