cmake_minimum_required(VERSION 3.10)
project(ProjetProgAvancee)
set(CMAKE_CXX_STANDARD 17)

option(ASTEROID_VISUAL_DEBUG "Enable Visual Debug mode" off)

add_subdirectory(external/SDL2-2.0.10)

set(TARGET asteroids)
set(SRC
        src/main.cpp
        include/Game.hpp
        src/Game.cpp
        include/Rendering/Renderer.hpp
        src/Rendering/Renderer.cpp
        include/Observer/Observer.hpp
        include/Observer/Subject.hpp
        include/Types/Vec2.hpp
        include/Types/Color.hpp
        src/Types/Color.cpp
        include/Entities/Player.hpp
        src/Entities/Player.cpp
        include/Rendering/Polygon.hpp
        src/Rendering/Polygon.cpp
        include/Observer/KeyboardEventData.hpp
        include/Transformable.hpp
        src/Transformable.cpp
        include/Types/Mat3.hpp
        include/Entities/Asteroids.hpp
        src/Entities/Asteroids.cpp
        include/Entities/Asteroid.hpp
        src/Entities/Asteroid.cpp
        include/Settings.hpp
        include/Types/Rect.hpp
        include/Physic/PhysicEngine.hpp
        include/Physic/PhysicEntity.hpp
        src/Physic/PhysicEntity.cpp
        src/Physic/PhysicEngine.cpp
        include/Entities/Shot.hpp
        include/Utils.hpp
        include/gui/Text.hpp
        src/gui/Text.cpp
        include/gui/Panel.hpp
        include/gui/Entity.hpp
        include/gui/Anchor.hpp
        src/gui/Panel.cpp
        include/gui/Gui.hpp
        src/gui/Gui.cpp)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE include)

if(ASTEROID_VISUAL_DEBUG)
    target_compile_definitions(${TARGET} PRIVATE -DDEBUG)
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
