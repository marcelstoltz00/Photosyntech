#ifndef __Plant3Builder_h__
#define __Plant3Builder_h__

#include "Builder.h"

/**
 * @brief Concrete builder for constructing a third plant species.
 *
 * Implements the Builder interface to create plants with specific
 * water strategies, sun strategies, and maturity states.
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
};

#endif
