#ifndef AutumnIterator_h
#define AutumnIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"
#include "../composite/PlantComponent.h"
#include "../composite/PlantGroup.h"

/**
 * @brief Concrete iterator for filtering autumn-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Autumn seasonal decorator. Handles nested hierarchies by
 * recursively descending into PlantGroups to find matching LivingPlants.
 *
 * **System Role:**
 * Specialized iterator for autumn-season inventory browsing. Enables customers to
 * view plants suitable for autumn growing. Skips non-autumn plants during traversal
 * and recursively searches through composite groups for focused seasonal shopping.
 *
 * **Pattern Role:** Concrete Iterator (autumn-specific filtering with composite support)
 *
 * **Related Patterns:**
 * - Iterator: Implements filtering traversal
 * - Aggregate: Created by AggAutumn factory
 * - Decorator: Identifies via Autumn decorator
 * - Composite: Handles nested PlantGroup hierarchies
 *
 * @see Iterator (abstract interface)
 * @see AggAutumn (creates this iterator)
 * @see Autumn (decorator identifying autumn plants)
 */
class AggAutumn;

class AutumnIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggAutumn aggregate managing the collection and target season.
		 */
		AutumnIterator(AggAutumn* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AutumnIterator() {}

		/**
		 * @brief Positions the iterator at the first autumn plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next autumn plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more autumn plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current autumn plant.
		 * @return Pointer to the current autumn LivingPlant.
		 */
		LivingPlant* currentItem();

	private:
		/**
		 * @brief Cached pointer to the current matching plant, or nullptr if not found.
		 */
		LivingPlant* currentPlant;

		/**
		 * @brief Recursively searches for the next matching plant in the hierarchy.
		 * @param plants Pointer to the plant collection to search.
		 * @param findFirst If true, returns the first matching plant; if false, returns the plant after currentPlant.
		 * @return Pointer to matching LivingPlant, or nullptr if none found.
		 */
		LivingPlant* findNextMatch(std::list<PlantComponent*>* plants, bool findFirst);
};

#endif
