#ifndef __RoseBuilder_h__
#define __RoseBuilder_h__

#include "Builder.h"

/**
 * @brief Concrete builder for constructing Rose plants.
 *
 * Implements the Builder interface to create Rose plants with specific
 * water strategies, sun strategies, and maturity states appropriate for roses.
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
};

#endif
