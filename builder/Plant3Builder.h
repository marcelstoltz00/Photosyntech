#ifndef Plant3Builder_h
#define Plant3Builder_h

#include "Builder.h"

/**
 * @brief Concrete builder for constructing a third plant species.
 *
 * Implements the Builder interface to create plants with specific
 * water strategies, sun strategies, and maturity states appropriate for this species.
 *
 * **System Role:**
 * Concrete implementation of Builder pattern for a specific plant species (Plant3).
 * Encapsulates all species-specific construction logic, enabling Director to treat
 * all plant types uniformly while each builder handles its unique configuration.
 * This separation allows new plant species to be added by creating only a new builder.
 *
 * **Pattern Role:** Concrete Builder (implements construction steps for Plant3)
 *
 * **Related Patterns:**
 * - Builder: Implements interface defined by abstract Builder
 * - Director: Orchestrates construction by calling methods on this builder
 * - Strategy: Assigns Plant3-specific water and sun strategies
 * - Prototype: Created plant becomes prototype for cloning operations
 * - Singleton: Obtains strategies from singleton's flyweight factories
 *
 * **System Interactions:**
 * - Director calls createObject(), assignWaterStrategy(), assignSunStrategy(), assignMaturityState() in sequence
 * - Plant3-specific strategies obtained from singleton factories
 * - Plant initialized in Seed state and stored internally
 * - getResult() returns fully constructed Plant3 instance
 *
 * @see Builder (abstract interface)
 * @see Director (orchestrates plant creation)
 * @see Strategy (water/sun strategies assigned)
 */
class Plant3Builder : public Builder
{
	public:
		/**
		 * @brief Creates a new plant object of the third species.
		 */
		void createObject();

		/**
		 * @brief Assigns the appropriate water strategy for this plant species.
		 */
		void assignWaterStrategy();

		/**
		 * @brief Assigns the appropriate sun strategy for this plant species.
		 */
		void assignSunStrategy();

		/**
		 * @brief Assigns the initial maturity state for this plant.
		 */
		void assignMaturityState();

		/**
		 * @brief Returns the fully constructed plant object.
		 * @return Pointer to the constructed Plant object.
		 */
		Plant* getResult();
};

#endif
