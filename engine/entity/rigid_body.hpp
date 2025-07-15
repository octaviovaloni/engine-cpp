#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP
#include "static_body.hpp"

namespace engine::entity
{
    class RigidBodyRec : public StaticBodyRect
    {
        ~RigidBodyRec() override = default;
        RigidBodyRec() = default;

        Vector2 velocity = {0,0};
        bool physics_enabled = true;

        void PhysicsUpdate(float delta) override;
    };
}

#endif //RIGID_BODY_HPP
