#ifndef SummerIterator_h
#define SummerIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"
#include "../composite/PlantComponent.h"
#include "../composite/PlantGroup.h"

/**
 * @brief Concrete iterator for filtering summer-season plants.
 *
 * Iterates through a plant collection returning only plants decorated
 * with the Summer seasonal decorator. Handles nested hierarchies by
 * recursively descending into PlantGroups to find matching LivingPlants.
 *
 * **System Role:**
 * Specialized iterator for summer-season inventory browsing. Enables customers to
 * view plants suitable for summer growing. Skips non-summer plants during traversal
 * for focused seasonal shopping.
 *
 * **Pattern Role:** Concrete Iterator (summer-specific filtering with composite support)
 *
 * **Related Patterns:**
 * - Iterator: Implements filtering traversal
 * - Aggregate: Created by AggSummer factory
 * - Decorator: Identifies via Summer decorator
 * - Composite: Handles nested PlantGroup hierarchies
 *
 * @see Iterator (abstract interface)
 * @see AggSummer (creates this iterator)
 * @see Summer (decorator identifying summer plants)
 */
class AggSummer;

class SummerIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggSummer aggregate managing the collection and target season.
		 */
		SummerIterator(AggSummer* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~SummerIterator() {}

		/**
		 * @brief Positions the iterator at the first summer plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next summer plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more summer plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current summer plant.
		 * @return Pointer to the current summer LivingPlant.
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
