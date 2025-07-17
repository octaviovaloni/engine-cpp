#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <functional>
#include <vector>
#include "event_bus.hpp"

namespace engine::types
{
    class Instance
    {
    public:
        virtual ~Instance() = default;
        Instance();

        bool destroyed = false;
        bool able_to_render = true;
        bool able_to_update = true;
        bool physics_enabled = false;

        void Destroy()
        {
            this->destroyed = true;
        }

        virtual void PhysicsUpdate(float delta);
        virtual void LogicUpdate(float delta);
        virtual void Draw(float delta);
;    };
}

#endif //INSTANCE_HPP
