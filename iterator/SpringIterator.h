#ifndef SpringIterator_h
#define SpringIterator_h

#include "Iterator.h"
#include "../prototype/LivingPlant.h"
#include "../composite/PlantComponent.h"
#include "../composite/PlantGroup.h"

/**
 * @brief Concrete iterator for filtering spring-season plants.
 *
 * Iterates through a plant collection returning only plants whose getSeason()
 * method matches the target season string. Handles nested hierarchies by
 * recursively descending into PlantGroups to find matching LivingPlants.
 *
 * **System Role:**
 * Specialized iterator for browsing spring-season plants. Enables customers to
 * view and select plants appropriate for spring growing. Skips non-spring plants
 * during traversal, providing focused seasonal inventory access.
 *
 * **Pattern Role:** Concrete Iterator (spring-specific filtering with composite support)
 *
 * **Related Patterns:**
 * - Iterator: Implements filtering traversal interface
 * - Aggregate: Created by AggSpring aggregate factory
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
 * @see AggSpring (creates this iterator)
 * @see LivingPlant::getSeason() (method used for filtering)
 */
class AggSpring;

class SpringIterator : public Iterator
{
	public:
		/**
		 * @brief Constructor that initializes the iterator with an aggregate.
		 * @param aggregate Pointer to the AggSpring aggregate managing the collection and target season.
		 */
		SpringIterator(AggSpring* aggregate);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~SpringIterator() {}

		/**
		 * @brief Positions the iterator at the first spring plant.
		 */
		void first();

		/**
		 * @brief Advances the iterator to the next spring plant.
		 */
		void next();

		/**
		 * @brief Checks if iteration is complete.
		 * @return True if no more spring plants to iterate, false otherwise.
		 */
		bool isDone();

		/**
		 * @brief Returns the current spring plant.
		 * @return Pointer to the current spring LivingPlant.
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
