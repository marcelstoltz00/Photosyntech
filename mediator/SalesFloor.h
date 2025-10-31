#ifndef SalesFloor_h
#define SalesFloor_h

#include "Mediator.h"

/**
 * @brief Concrete mediator for handling sales floor operations.
 *
 * Coordinates interactions between customers and sales staff,
 * routing purchase requests to available staff members and
 * managing sales transactions.
 */
class SalesFloor : public Mediator
{
public:
    /**
     * @brief Constructs a new SalesFloor mediator.
     */
    SalesFloor();  // added a explicit constructor declaration

    /**
     * @brief Routes customer assistance requests to available sales staff.
     * @param customer Pointer to the User requesting sales assistance.
     */
    virtual string getAssistance(User* customer) ;

    /**
     * @brief Coordinates staff assistance for sales operations.
     */
    virtual void assist() ;
};

#endif
