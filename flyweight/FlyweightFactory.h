#ifndef FlyweightFactory_h
#define FlyweightFactory_h

#include <map>
#include "Flyweight.h"

/**
 * @brief Template factory for creating and caching flyweight objects.
 *
 * Creates and manages flyweight objects using a cache keyed by ID.
 * Returns existing instances when available or creates new ones as needed,
 * ensuring shared immutable data is reused efficiently across the system.
 *
 * **System Role:**
 * This template factory class is the creator and manager of flyweight instances.
 * Three instances (managed by Singleton) handle caching of water strategies,
 * sun strategies, and season names. Cache lookups are O(log n), enabling efficient
 * access to shared data across thousands of plant instances.
 *
 * **Pattern Role:** Factory (creates and manages Flyweight instances)
 *
 * **Related Patterns:**
 * - Flyweight: Creates instances of this template
 * - Singleton: Three FlyweightFactory instances managed by singleton
 * - Builder: Requests strategy instances during plant construction
 * - Strategy: Factories cache WaterStrategy and SunStrategy instances
 * - Iterator: Season name factories used for filtering
 *
 * **System Interactions:**
 * - getFlyweight(ID id) checks cache, returns existing or creates new
 * - Cache prevents duplicate object creation
 * - Singleton manages factory lifetime and global access
 * - Immutability allows safe sharing across all plants
 * - Memory savings: 5000 plants with 2 strategies = 9998 fewer objects
 *
 * @see Flyweight (instances created by factory)
 * @see Singleton (owns factory instances)
 * @see Strategy (flyweight-managed strategies)
 *
 * @tparam T The type of data being shared (e.g., string, WaterStrategy, SunStrategy).
 * @tparam ID The type of identifier used to key the cache (e.g., string, int).
 */
template <class T, class ID>
class FlyweightFactory
{
	private:
		std::map<ID, Flyweight<T>*> cache;

	public:
		/**
		 * @brief Gets or creates a flyweight for the given identifier.
		 * @param id The identifier for the requested flyweight.
		 * @return Pointer to the Flyweight instance (either cached or newly created).
		 */
		Flyweight<T>* getFlyweight(ID id);

		/**
		 * @brief Destructor that cleans up cached flyweights.
		 */
		~FlyweightFactory() {
			for (auto& pair : cache) {
				delete pair.second;
			}
		}
};

#endif
