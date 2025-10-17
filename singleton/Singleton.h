#ifndef __Singleton_h__
#define __Singleton_h__

#include <string>
#include "../flyweight/FlyweightFactory.h"
#include "../flyweight/Flyweight.h"
#include "../strategy/WaterStrategy.h"
#include "../strategy/SunStrategy.h"

class PlantGroup;

/**
 * @brief Singleton class managing global inventory and flyweight factories.
 *
 * Ensures only one instance exists and provides global access point through
 * getInstance(). Manages the shared inventory and flyweight factories for
 * efficient memory usage of shared immutable data (seasons, strategies).
 */
class Singleton
{
	private:
		static Singleton* _instance;
		PlantGroup* _inventory;
		FlyweightFactory<std::string, std::string>* _string;
		FlyweightFactory<int, WaterStrategy>* _waterStrategies;
		FlyweightFactory<int, SunStrategy>* _sunStrategies;

		/**
		 * @brief Private constructor to prevent direct instantiation.
		 */
		Singleton();

	public:
		/**
		 * @brief Gets the singleton instance.
		 * @return Pointer to the single Singleton instance.
		 */
		static Singleton* getInstance();

		/**
		 * @brief Gets a flyweight for a season name.
		 * @param aSeason Season name string.
		 * @return Const pointer to the Flyweight wrapping the season string.
		 */
		const Flyweight<std::string>* getSeason(std::string aSeason);

		/**
		 * @brief Gets a flyweight for a water strategy.
		 * @param aLevel Integer identifier for the water strategy level.
		 * @return Const pointer to the Flyweight wrapping the WaterStrategy.
		 */
		const Flyweight<WaterStrategy>* getWaterFly(int aLevel);

		/**
		 * @brief Gets a flyweight for a sun strategy.
		 * @param aLevel Integer identifier for the sun strategy level.
		 * @return Const pointer to the Flyweight wrapping the SunStrategy.
		 */
		const Flyweight<SunStrategy>* getSunFly(int aLevel);

		/**
		 * @brief Gets the global plant inventory.
		 * @return Const pointer to the PlantGroup representing the inventory.
		 */
		const PlantGroup* getInventory();

		/**
		 * @brief Deleted copy constructor to prevent copying.
		 */
		Singleton(const Singleton&) = delete;

		/**
		 * @brief Deleted assignment operator to prevent assignment.
		 */
		Singleton& operator=(const Singleton&) = delete;
};

#endif
