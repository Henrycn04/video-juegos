#ifndef POOL_HPP
#define POOL_HPP
#include <vector>

/**
 * @class IPool
 * @brief Interface for component pools in the ECS framework.
 *
 * Provides a base interface for all component pool implementations.
 */
class IPool {
    public:
        virtual ~IPool() = default;
};

/**
 * @class Pool
 * @brief Templated component pool implementation.
 * @tparam TComponent The type of component to be stored in the pool.
 *
 * Implements a resizable container for storing components of a specific type.
 * Provides basic operations for component management in an ECS architecture.
 */
template <typename TComponent>
class Pool : public IPool {
    private:
        std::vector<TComponent> data; ///< Internal storage for components

    public:
        /**
         * @brief Constructs a Pool with initial size.
         * @param size Initial capacity of the pool (default: 1000).
         */
        Pool(int size = 1000) {
            data.resize(size);
        }

        virtual ~Pool() = default;

        /**
         * @brief Checks if the pool is empty.
         * @return True if the pool contains no elements, false otherwise.
         */
        bool IsEmpty() const {
            return data.empty();
        }

        /**
         * @brief Gets the current size of the pool.
         * @return Number of elements in the pool.
         */
        int GetSize() const {
            return static_cast<int>(data.size());
        }

        /**
         * @brief Resizes the pool.
         * @param n New size of the pool.
         */
        void Resize(int n) {
            data.resize(n);
        }

        /**
         * @brief Clears all elements from the pool.
         */
        void Clear() {
            data.clear();
        }

        /**
         * @brief Adds a component to the end of the pool.
         * @param object Component to be added.
         */
        void Add(TComponent object) {
            data.push_back(object);
        }

        /**
         * @brief Sets a component at a specific index.
         * @param index Position to set the component.
         * @param object Component to be stored.
         */
        void Set(unsigned int index, TComponent object) {
            data[index] = object;
        }

        /**
         * @brief Gets a reference to the component at specified index.
         * @param index Position of the component to retrieve.
         * @return Reference to the requested component.
         */
        TComponent& Get(unsigned int index) {
            return static_cast<TComponent&>(data[index]);
        }

        /**
         * @brief Array access operator.
         * @param index Position of the component to access.
         * @return Reference to the component at specified index.
         */
        TComponent& operator[](unsigned int index) {
            return static_cast<TComponent&>(data[index]);
        }
};

#endif