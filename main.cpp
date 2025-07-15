#define ENGINE_DEBUG_MODE
#define ENGINE_GRAVITY 980.0f // pixels/second²

#include <raylib.h>
#include "engine/entity/static_body.hpp"
#include "engine/rendering.hpp"
#include <thread>
#include <chrono>
#include <iostream>

auto ENGINE_WINDOW_DEFAULT_TITLE = "Step 1: Raylib Understanding";
constexpr int ENGINE_WINDOW_SIZE_X = 1280;
constexpr int ENGINE_WINDOW_SIZE_Y = 720;
constexpr int ENGINE_GARBAGE_COLLECTION_TIME = 35;

void EditorControls() {
    if (IsKeyPressed(KEY_A)) {
        auto* CreatedBlock = new engine::entity::StaticBodyRect();
        CreatedBlock->transform = {
            0,0,
            100,100
        };
        CreatedBlock->color = RED;

        engine::rendering::RegisterInstance(CreatedBlock);
    }
}

int main()
{
    #ifdef ENGINE_DEBUG_MODE
    std::cout << "Starting engine..." << std::endl;
    #endif

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    SetExitKey(KEY_ESCAPE);
    SetTargetFPS(120);
    InitWindow(
        ENGINE_WINDOW_SIZE_X,
        ENGINE_WINDOW_SIZE_Y,
        ENGINE_WINDOW_DEFAULT_TITLE
    );

    // Garbage collector thread
    std::thread GarbageCollectorThread([]()
    {
        while (!WindowShouldClose())
        {
            #ifdef ENGINE_DEBUG_MODE
            std::cout << "Collecting garbage..." << std::endl;
            #endif
            engine::rendering::CleanDestroyedInstances();
            std::this_thread::sleep_for(std::chrono::seconds(ENGINE_GARBAGE_COLLECTION_TIME));
        }
        engine::rendering::CleanAllInstances();
    });

    // Engine loop
    while (!WindowShouldClose())
    {
        EditorControls();
        engine::rendering::Update();
        engine::rendering::Draw();
    }

    GarbageCollectorThread.join();
    CloseWindow();
    return 0;
}
