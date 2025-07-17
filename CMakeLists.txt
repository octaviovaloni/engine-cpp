cmake_minimum_required(VERSION 3.31)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_CXX_STANDARD 20)
project(Step1_RaylibUnderstanding)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif()
endif()

add_executable(${PROJECT_NAME} main.cpp
        engine/rendering.hpp
        engine/instance.hpp
        engine/entity/static_body.cpp
        engine/entity/static_body.hpp
        engine/instance.cpp
        engine/thread_safe_vector.hpp
        engine/entity/rigid_body.cpp
        engine/entity/rigid_body.hpp
        engine/event_bus.hpp
)
target_link_libraries(${PROJECT_NAME} raylib)