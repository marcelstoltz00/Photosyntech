#ifndef BasketMemento_h
#define BasketMemento_h

#include <list>

class Customer;
class PlantComponent;

/**
 * @brief Memento class capturing immutable snapshot of customer basket contents.
 *
 * Stores a snapshot of a customer's shopping basket at a specific point in time
 * for later restoration. Used by PurchasePlantsCommand to enable undo functionality.
 * Maintains references to plants (not ownership) and records whether basket existed
 * before the purchase.
 *
 * **System Role:**
 * Enables undo functionality for purchase transactions by capturing the basket's
 * plant list and existence status in an immutable snapshot. Commands use mementos
 * to implement reversible purchase operations.
 *
 * **Pattern Role:** Memento (encapsulates state snapshot)
 *
 * **Related Patterns:**
 * - Customer: Originator that owns the basket
 * - PurchasePlantsCommand: Caretaker that stores memento for undo
 * - Command: Uses memento to implement undo operations
 * - Composite: Basket is a PlantGroup containing plants
 *
 * **System Interactions:**
 * - PurchasePlantsCommand creates BasketMemento before executing purchase
 * - BasketMemento stores snapshot of basket plant pointers and existence flag
 * - PurchasePlantsCommand calls restoreBasket() during undo
 * - Memento is immutable after creation (no state modifications)
 * - Does NOT own plants (avoids double-deletion issues)
 *
 * @see Customer (originator)
 * @see PurchasePlantsCommand (caretaker)
 */
class BasketMemento
{
	friend class PurchasePlantsCommand;

private:
	/**
	 * @brief Captured basket plant pointers.
	 * Stores references only, not ownership of the plants.
	 */
	std::list<PlantComponent *> plants;

	/**
	 * @brief Flag indicating if basket existed before snapshot.
	 * Used to distinguish between "empty basket" and "no basket".
	 */
	bool basketExisted;

	/**
	 * @brief Private constructor for friend-only creation.
	 * @param customer Pointer to the Customer whose basket to capture.
	 */
	BasketMemento(Customer *customer);

public:
	/**
	 * @brief Virtual destructor for proper cleanup.
	 * Does NOT delete contained plants (memento maintains references only).
	 */
	virtual ~BasketMemento();

	/**
	 * @brief Restores captured basket state to a customer.
	 * @param customer Pointer to the Customer to restore basket to.
	 */
	void restoreBasket(Customer *customer);

	/**
	 * @brief Gets the captured plant list.
	 * @return Const reference to the list of plant pointers.
	 */
	const std::list<PlantComponent *> &getPlants() const;

	/**
	 * @brief Checks if the basket existed before snapshot.
	 * @return True if basket existed, false if it was null.
	 */
	bool didBasketExist() const;
};

#endif
