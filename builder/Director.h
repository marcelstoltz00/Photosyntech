#ifndef Director_h
#define Director_h

#include "Builder.h"
#include "prototype/LivingPlant.h"

/**
 * @brief Orchestrates the LivingPlant construction process using a Builder.
 *
 * The Director controls the order of construction steps and ensures that all
 * necessary components are properly initialized. It uses the Builder interface
 * to construct plants without knowing the specific type being created.
 */
class Director
{
	private:
		Builder* builder;

	public:
		/**
		 * @brief Constructor for Director with a specific Builder.
		 * @param builder Pointer to the Builder instance to use.
		 */
		Director(Builder* builder);
		/**
		 * @brief Executes the construction sequence using the assigned builder.
		 *
		 * Calls the builder methods in the correct order to create a complete
		 * plant with all required strategies and states.
		 */
		void construct();

		/**
		 * @brief Retrieves the constructed plant from the builder.
		 * @return Pointer to the fully constructed LivingPlant object.
		 */
		PlantComponent* getPlant();
};

#endif
