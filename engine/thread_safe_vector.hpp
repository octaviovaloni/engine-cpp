#ifndef THREAD_SAFE_VECTOR_HPP
#define THREAD_SAFE_VECTOR_HPP

#include <vector>
#include <shared_mutex>
#include <functional>
#include <mutex>

template<typename T>
class ThreadSafeVector {
    std::vector<T> data;
    mutable std::shared_mutex mutex;
public:
    void Read(std::function<void(const std::vector<T>&)> reader) const {
        std::shared_lock lock(mutex);
        reader(data);
    }

    void Write(std::function<void(std::vector<T>&)> writer) {
        std::unique_lock lock(mutex);
        writer(data);
    }
};
#endif THREAD_SAFE_VECTOR_HPP
