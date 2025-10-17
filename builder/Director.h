#ifndef __Director_h__
#define __Director_h__

class Builder;
class Plant;

/**
 * @brief Orchestrates the plant construction process using a Builder.
 *
 * The Director controls the order of construction steps and ensures that all
 * necessary components are properly initialized. It uses the Builder interface
 * to construct plants without knowing the specific type being created.
 */
class Director
{
	private:
		Builder* _builder;

	public:
		/**
		 * @brief Executes the construction sequence using the assigned builder.
		 *
		 * Calls the builder methods in the correct order to create a complete
		 * plant with all required strategies and states.
		 */
		void construct();

		/**
		 * @brief Retrieves the constructed plant from the builder.
		 * @return Pointer to the fully constructed Plant object.
		 */
		Plant* getPlant();
};

#endif
