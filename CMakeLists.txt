cmake_minimum_required(VERSION 3.10)
project(ProjetProgAvancee)
set(CMAKE_CXX_STANDARD 17)

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
        include/Settings.hpp)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE include)

if(CMAKE_BUILD_TYPE MATCHES Debug)
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
