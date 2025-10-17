#ifndef __SunflowerBuilder_h__
#define __SunflowerBuilder_h__

#include "Builder.h"

/**
 * @brief Concrete builder for constructing Sunflower plants.
 *
 * Implements the Builder interface to create Sunflower plants with specific
 * water strategies, sun strategies, and maturity states appropriate for sunflowers.
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
};

#endif
