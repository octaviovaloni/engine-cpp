#include "static_body.hpp"

namespace engine::entity
{
    void StaticBodyRect::Draw(float delta)
    {
        DrawRectanglePro(this->transform, this->origin, this->rotation, this->color);
    }
}
