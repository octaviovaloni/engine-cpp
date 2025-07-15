#ifndef RENDER_HPP
#define RENDER_HPP
#include "thread_safe_vector.hpp"
#include "instance.hpp"
#include <raylib.h>
#include <vector>

namespace engine::rendering {
    inline ThreadSafeVector<engine::types::Instance*> render_layers[10];

    inline void RegisterInstance(engine::types::Instance* instance, const int render_layer = 1)
    {
        render_layers[render_layer].Write([instance](std::vector<engine::types::Instance*>& vector) {
            vector.push_back(instance);
        });
    }

    inline void DrawInstance(engine::types::Instance* instance) {
        if (instance->able_to_render) instance->Draw(GetFrameTime());
    }

    inline void DrawLoadedInstances()
    {
        for (auto render_layer : render_layers) {
            render_layer.Write([](const std::vector<engine::types::Instance*>& vector) {
                for (auto* instance : vector) DrawInstance(instance);
            });
        }
    }

    inline void DrawLoadedInstances(const int render_layer)
    {
        render_layers[render_layer].Read([](const std::vector<engine::types::Instance*>& vector) {
            for (auto* instance : vector) DrawInstance(instance);
        });
    }

    inline void LogicUpdateInstance(engine::types::Instance* instance) {
        if (instance->able_to_update) instance->LogicUpdate(GetFrameTime());
    }

    inline void LogicUpdateLoadedInstances(const int render_layer)
    {
        render_layers[render_layer].Read([](const std::vector<engine::types::Instance*>& vector) {
            for (auto* instance : vector) LogicUpdateInstance(instance);
        });
    }

    inline void LogicUpdateLoadedInstances()
    {
        for (auto render_layer : render_layers) {
            render_layer.Write([](const std::vector<engine::types::Instance*>& vector) {
                for (auto* instance : vector) LogicUpdateInstance(instance);
            });
        }
    }

    inline void PhysicsUpdateInstance(engine::types::Instance* instance) {
        if (instance->physics_enabled) instance->PhysicsUpdate(GetFrameTime());
    }

    inline void PhysicsUpdateLoadedInstances()
    {
        for (auto render_layer : render_layers) {
            render_layer.Write([](const std::vector<engine::types::Instance*>& vector) {
                for (auto* instance : vector) PhysicsUpdateInstance(instance);
            });
        }
    }

    inline void PhysicsUpdateLoadedInstances(const int render_layer)
    {
        render_layers[render_layer].Read([](const std::vector<engine::types::Instance*>& vector) {
            for (auto* instance : vector) {
                if (instance->physics_enabled) instance->PhysicsUpdate(GetFrameTime());
            }
        });
    }

    inline void CleanDestroyedInstances()
    {
        for (auto render_layer : render_layers) {
            render_layer.Write([](std::vector<engine::types::Instance*>& vector) {
                std::erase_if(vector, [](const engine::types::Instance* instance) {
                if (instance->destroyed) {
                    delete instance;
                    return true;
                }
                return false;
                });
            });
        }
    }

    inline void CleanDestroyedInstances(const int render_layer)
    {
        render_layers[render_layer].Write([](std::vector<engine::types::Instance*>& vector) {
            std::erase_if(vector, [](const engine::types::Instance* instance) {
                if (instance->destroyed) {
                    delete instance;
                    return true;
                }
                return false;
            });
        });
    }

    inline void CleanAllInstances()
    {
        for (auto render_layer : render_layers) {
            render_layer.Write([](std::vector<engine::types::Instance*>& vector) {
                std::erase_if(vector, [](const engine::types::Instance* instance) {
                    delete instance;
                    return true;
                });
            });
        }
    }

    inline void UpdateLoadedInstances()
    {
        LogicUpdateLoadedInstances();
        PhysicsUpdateLoadedInstances();
    }

    inline void Draw()
    {
        BeginDrawing();

        ClearBackground(SKYBLUE);

        DrawLoadedInstances();

        #ifdef ENGINE_DEBUG_MODE
        DrawFPS(0,0);
        #endif

        EndDrawing();
    }
}

#endif //RENDER_HPP
