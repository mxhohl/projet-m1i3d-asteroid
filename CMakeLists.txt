cmake_minimum_required(VERSION 3.10)
project(ProjetProgAvancee)
set(CMAKE_CXX_STANDARD 17)

option(ASTEROID_VISUAL_DEBUG "Enable Visual Debug mode" off)

add_subdirectory(external/SDL2-2.0.12)

set(TARGET asteroids)
set(SRC
        src/Game/main.cpp
        include/Game/Game.hpp
        src/Game/Game.cpp
        include/Engine/Rendering/Renderer.hpp
        src/Engine/Rendering/Renderer.cpp
        include/Engine/Observer/Observer.hpp
        include/Engine/Observer/Subject.hpp
        include/Engine/Types/Vec2.hpp
        include/Engine/Types/Color.hpp
        src/Engine/Types/Color.cpp
        include/Game/Entities/Player.hpp
        src/Game/Entities/Player.cpp
        include/Engine/Types/Polygon.hpp
        src/Engine/Types/Polygon.cpp
        include/Engine/Observer/KeyboardEventData.hpp
        include/Engine/Transformable.hpp
        src/Engine/Transformable.cpp
        include/Engine/Types/Mat3.hpp
        include/Game/Entities/Asteroids.hpp
        src/Game/Entities/Asteroids.cpp
        include/Game/Entities/Asteroid.hpp
        src/Game/Entities/Asteroid.cpp
        include/Engine/Settings.hpp
        include/Engine/Types/Rect.hpp
        include/Engine/Physic/PhysicEngine.hpp
        include/Engine/Physic/PhysicEntity.hpp
        src/Engine/Physic/PhysicEntity.cpp
        src/Engine/Physic/PhysicEngine.cpp
        include/Game/Entities/Shot.hpp
        include/Engine/Utils.hpp
        include/Engine/gui/Entities/Text.hpp
        src/Engine/gui/Entities/Text.cpp
        include/Engine/gui/Entities/Panel.hpp
        include/Engine/gui/Entity.hpp
        include/Engine/gui/Anchor.hpp
        src/Engine/gui/Entities/Panel.cpp
        include/Engine/gui/Gui.hpp
        src/Engine/gui/Gui.cpp src/Engine/gui/Entity.cpp
        include/Engine/gui/Renderer.hpp
        src/Engine/gui/GUIRenderer.cpp
        include/Engine/Logger.hpp
        src/Engine/Logger.cpp)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE include)

if(ASTEROID_VISUAL_DEBUG)
    target_compile_definitions(${TARGET} PRIVATE -DDEBUG_MOD)
endif()

if(MSVC)
    string(REGEX REPLACE "/W[3|4]" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    if(MINGW)
        target_link_libraries(${TARGET} PRIVATE mingw32)
    endif()
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra)
endif()

target_link_libraries(${TARGET} PRIVATE SDL2main SDL2-static)
