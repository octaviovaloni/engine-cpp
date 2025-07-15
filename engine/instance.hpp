#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <functional>
#include <vector>

namespace engine::types
{
    class Instance
    {
    public:
        virtual ~Instance() = default;
        Instance();

        std::vector<std::function<void()>> logic_update_connections;
        std::vector<std::function<void()>> physics_update_connections;
        bool destroyed = false;
        bool able_to_render = true;
        bool able_to_update = true;
        bool physics_enabled = false;

        void Destroy()
        {
            this->destroyed = true;
        }

        void ConnectToPhysicsUpdate(const std::function<void()>& func);
        void ConnectToLogicUpdate(const std::function<void()>& func);
        void FireLogicUpdateConnections();
        void FirePhysicsUpdateConnections();


        virtual void PhysicsUpdate(float delta);
        virtual void LogicUpdate(float delta);
        virtual void Draw(float delta);
;    };
}

#endif //INSTANCE_HPP
