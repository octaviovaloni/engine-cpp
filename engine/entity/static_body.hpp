//
// Created by octaviovaloni on 13/7/2025.
//

#ifndef STATIC_BODY_HPP
#define STATIC_BODY_HPP
#include <raylib.h>
#include "../instance.hpp"

namespace engine::entity
{
    class StaticBodyRect : public engine::types::Instance
    {
    public:
        Rectangle transform = {0,0,0,0};
        Vector2 origin = {0,0};
        float rotation = 0.0f;
        Color color = BLACK;

        void Draw(float delta) override;
    };
}

#endif //STATIC_BODY_HPP
