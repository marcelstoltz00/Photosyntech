#ifndef __NurseryFacade_h__
#define __NurseryFacade_h__

class Director;
class Singleton;
class Mediator;
class Command;
class Aggregate;
class PlantComponent;

/**
 * @brief Unified facade interface for the nursery management system.
 *
 * Provides simplified, high-level methods for common operations by
 * coordinating multiple subsystems (plant creation via Builder/Director,
 * inventory management via Singleton, sales via Mediator, operations via Command,
 * and filtering via Iterator). Hides system complexity from GUI and external clients.
 */
class NurseryFacade
{
	private:
		Director* _director;
		Singleton* _inventory;
		Mediator* _salesFloor;
		Mediator* _suggestionFloor;

	public:
		/**
		 * @brief Creates a new plant using the builder pattern.
		 * @param species String identifying the plant species to create.
		 * @return Pointer to the newly created PlantComponent.
		 */
		PlantComponent* createPlant(const char* species);

		/**
		 * @brief Adds a plant to the global inventory.
		 * @param plant Pointer to the PlantComponent to add.
		 */
		void addToInventory(PlantComponent* plant);

		/**
		 * @brief Browses available plants, optionally filtered by criteria.
		 * @param filter Optional filter string (e.g., season name).
		 */
		void browsePlants(const char* filter);

		/**
		 * @brief Initiates a plant purchase transaction.
		 * @param plant Pointer to the PlantComponent being purchased.
		 */
		void purchasePlant(PlantComponent* plant);

		/**
		 * @brief Waters a specific plant.
		 * @param plant Pointer to the PlantComponent to water.
		 */
		void waterPlant(PlantComponent* plant);

		/**
		 * @brief Requests plant care suggestions from staff.
		 */
		void getSuggestions();
};

#endif
