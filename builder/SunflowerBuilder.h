#ifndef SunflowerBuilder_h
#define SunflowerBuilder_h

#include "Builder.h"

/**
 * @brief Concrete builder for constructing Sunflower plants.
 *
 * Implements the Builder interface to create Sunflower plants with specific
 * water strategies, sun strategies, and maturity states appropriate for sunflowers.
 *
 * **System Role:**
 * Concrete implementation of Builder pattern for Sunflower plant species.
 * Encapsulates sunflower-specific construction including high sun requirements,
 * moderate water needs, and sunflower lifecycle characteristics.
 * Enables Director to create sunflowers with consistent configuration.
 *
 * **Pattern Role:** Concrete Builder (implements construction steps for Sunflower species)
 *
 * **Related Patterns:**
 * - Builder: Implements interface defined by abstract Builder
 * - Director: Orchestrates sunflower construction via builder methods
 * - Strategy: Assigns sunflower-appropriate high-sun and moderate-water strategies
 * - Prototype: Created sunflowers become prototypes for inventory cloning
 * - Singleton: Obtains sunflower strategies from singleton's flyweight factories
 *
 * **System Interactions:**
 * - Director calls methods in sequence to build sunflower with characteristics
 * - Sunflower strategies obtained from singleton-managed strategy factories
 * - Sunflower initialized in Seed state with high-sun requirements
 * - getResult() returns fully constructed Sunflower instance ready for inventory
 *
 * @see Builder (abstract interface)
 * @see Director (orchestrates sunflower creation)
 * @see Strategy (sunflower-specific water/sun strategies)
 */
class SunflowerBuilder : public Builder
{
	public:
		/**
		 * @brief Creates a new Sunflower plant object.
		 */
		void createObject();

		/**
		 * @brief Assigns the water strategy suitable for sunflowers.
		 */
		void assignWaterStrategy();

		/**
		 * @brief Assigns the sun strategy suitable for sunflowers.
		 */
		void assignSunStrategy();

		/**
		 * @brief Assigns the initial maturity state for the sunflower.
		 */
		void assignMaturityState();

		/**
		 * @brief Returns the fully constructed plant object.
		 * @return Pointer to the constructed Plant object.
		 */
		Plant* getResult();
};

#endif
