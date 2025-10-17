#ifndef __Flyweight_h__
#define __Flyweight_h__

/**
 * @brief Template class for sharing immutable data objects.
 *
 * Stores shared immutable data (seasons, strategies) and provides access
 * through getState(). Used by FlyweightFactory to minimize memory consumption
 * by sharing instances across multiple plants instead of duplicating data.
 *
 * @tparam T The type of data being shared (e.g., string, WaterStrategy, SunStrategy).
 */
template <class T>
class Flyweight
{
	private:
		T* _data;

	public:
		/**
		 * @brief Constructs a Flyweight with the given data.
		 * @param data Pointer to the shared data object.
		 */
		Flyweight(T* data) : _data(data) {}

		/**
		 * @brief Gets the shared state data.
		 * @return Pointer to the shared data object.
		 */
		T* getState() {
			return _data;
		}

		/**
		 * @brief Destructor for cleanup.
		 */
		~Flyweight() {
			// Note: Consider whether _data ownership should be here or in factory
		}
};

#endif
