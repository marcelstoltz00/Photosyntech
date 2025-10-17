#ifndef __FlyweightFactory_h__
#define __FlyweightFactory_h__

#include <map>
#include "Flyweight.h"

/**
 * @brief Template factory for creating and caching flyweight objects.
 *
 * Creates and manages flyweight objects using a cache keyed by ID.
 * Returns existing instances when available or creates new ones as needed,
 * ensuring shared immutable data is reused efficiently across the system.
 *
 * @tparam T The type of data being shared (e.g., string, WaterStrategy, SunStrategy).
 * @tparam ID The type of identifier used to key the cache (e.g., string, int).
 */
template <class T, class ID>
class FlyweightFactory
{
	private:
		std::map<ID, Flyweight<T>*> _cache;

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
			for (auto& pair : _cache) {
				delete pair.second;
			}
		}
};

#endif
