#include "rigid_body.hpp"

namespace engine::entity
{
    void RigidBodyRec::PhysicsUpdate(const float delta)
    {
        this->transform.x *= this->velocity.x * delta;
        this->transform.y *= this->velocity.y * delta;
    }

}