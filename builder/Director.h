#ifndef Director_h
#define Director_h

#include "../builder/Builder.h"
#include "../prototype/LivingPlant.h"

/**
 * @brief Orchestrates the PlantComponent construction process using a Builder.
 *
 * The Director controls the order of construction steps and ensures that all
 * necessary components are properly initialized. It uses the Builder interface
 * to construct plants without knowing the specific type being created.
 * 
 * The construction sequence is:
 * 1. Create base plant object (Tree, Shrub, Herb, etc.)
 * 2. Assign water strategy
 * 3. Assign sun strategy
 * 4. Assign maturity state
 * 5. Add decorators (season and plant attributes)
 * 6. Set up initial health, water, and sun levels
 * 
 * @see Builder The abstract builder interface that defines construction steps
 * @see LivingPlant The product being constructed
 * @see PlantComponent The composite interface for plant objects
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
		 * plant with all required strategies and states. The sequence is:
		 * 1. createObject() - Creates the base plant object
		 * 2. assignWaterStrategy() - Sets water requirements
		 * 3. assignSunStrategy() - Sets sun exposure needs
		 * 4. assignMaturityState() - Sets initial growth state
		 * 5. addDecorators() - Adds season and plant attributes
		 * 6. setUp() - Sets up initial health, water, and sun levels
		 * 
		 * If no builder is assigned (null), the method returns without constructing.
		 */
		void construct();

		/**
		 * @brief Retrieves the constructed plant from the builder.
		 * @return Pointer to the fully constructed PlantComponent object, or nullptr if no builder is assigned.
		 * 
		 * The builder's getResult() method is called to get the constructed plant.
		 * The builder implementation determines whether a new instance or a pointer to the same instance is returned.
		 */
		PlantComponent* getPlant();
};

#endif
