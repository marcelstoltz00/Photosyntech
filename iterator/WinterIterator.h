#ifndef WinterIterator_h
#define WinterIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"
#include "../composite/PlantComponent.h"
#include "../composite/PlantGroup.h"

/**
 * @brief Concrete iterator for filtering winter-season plants.
 *
 * Iterates through a plant collection returning only plants whose getSeason()
 * method matches the target season string. Handles nested hierarchies by
 * recursively descending into PlantGroups to find matching LivingPlants.
 *
 * **System Role:**
 * Specialized iterator for winter-season inventory browsing. Enables customers to
 * view plants suitable for winter growing. Skips non-winter plants during traversal
 * for focused seasonal shopping.
 *
 * **Pattern Role:** Concrete Iterator (winter-specific filtering with composite support)
 *
 * **Related Patterns:**
 * - Iterator: Implements filtering traversal interface
 * - Aggregate: Created by AggWinter aggregate factory
 * - Decorator: Filters plants based on their seasonal decorator chain (via getSeason())
 * - Composite: Handles nested PlantGroup hierarchies
 *
 * **System Interactions:**
 * - first() finds first plant matching target season
 * - next() advances to next matching plant
 * - isDone() checks iteration completion
 * - currentItem() returns current matching plant
 * - Filters by comparing plant->getSeason() to aggregate->targetSeason
 *
 * @see Iterator (abstract interface)
 * @see AggWinter (creates this iterator)
 * @see LivingPlant::getSeason() (method used for filtering)
 */
class AggWinter;

class WinterIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggWinter aggregate managing the collection and target season.
		 */
		WinterIterator(AggWinter* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~WinterIterator() {}

		/**
		 * @brief Positions the iterator at the first winter plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next winter plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more winter plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current winter plant.
		 * @return Pointer to the current winter LivingPlant.
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
