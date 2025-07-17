#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP
#include <unordered_map>
#include <vector>
#include <functional>
#include <string_view>

namespace engine
{
    class EventBus {
    public:
        using Listener = std::function<void(void*)>; // The lambda accepts any type of argument

        void Emit(const std::string_view eventId, void* data = nullptr) {
            if (const auto it = listeners.find(eventId); it != listeners.end()) {
                for (auto& listener : it->second) {
                    listener(data);
                }
            }
        }

        void Connect(const std::string_view eventId, const Listener& callback) {
            listeners[eventId].push_back(callback);
        }

    private:
        std::unordered_map<std::string_view, std::vector<Listener>> listeners;
    };
}

#endif //EVENT_BUS_HPP
