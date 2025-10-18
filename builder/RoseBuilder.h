#ifndef RoseBuilder_h
#define RoseBuilder_h

#include "Builder.h"

/**
 * @brief Concrete builder for constructing Rose plants.
 *
 * Implements the Builder interface to create Rose plants with specific
 * water strategies, sun strategies, and maturity states appropriate for roses.
 *
 * **System Role:**
 * Concrete implementation of Builder pattern for Rose plant species.
 * Encapsulates rose-specific construction including mid-range water needs,
 * mid-range sun requirements, and rose lifecycle characteristics.
 * Enables Director to create roses uniformly while isolating species-specific logic.
 *
 * **Pattern Role:** Concrete Builder (implements construction steps for Rose species)
 *
 * **Related Patterns:**
 * - Builder: Implements interface defined by abstract Builder
 * - Director: Orchestrates rose construction via builder methods
 * - Strategy: Assigns rose-appropriate water and sun strategies
 * - Prototype: Created roses become prototypes for inventory cloning
 * - Singleton: Obtains rose strategies from singleton's flyweight factories
 *
 * **System Interactions:**
 * - Director calls methods in sequence to build rose with characteristics
 * - Rose strategies obtained from singleton-managed strategy factories
 * - Rose initialized in Seed state with species-specific parameters
 * - getResult() returns fully constructed Rose instance ready for inventory
 *
 * @see Builder (abstract interface)
 * @see Director (orchestrates rose creation)
 * @see Strategy (rose-specific water/sun strategies)
 */
class RoseBuilder : public Builder
{
	public:
		/**
		 * @brief Creates a new Rose plant object.
		 */
		void createObject();

		/**
		 * @brief Assigns the water strategy suitable for roses.
		 */
		void assignWaterStrategy();

		/**
		 * @brief Assigns the sun strategy suitable for roses.
		 */
		void assignSunStrategy();

		/**
		 * @brief Assigns the initial maturity state for the rose.
		 */
		void assignMaturityState();

		/**
		 * @brief Returns the fully constructed plant object.
		 * @return Pointer to the constructed Plant object.
		 */
		Plant* getResult();
};

#endif
