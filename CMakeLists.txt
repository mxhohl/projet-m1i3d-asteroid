cmake_minimum_required(VERSION 3.10)
project(ProjetProgAvancee)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external/SDL2-2.0.10)

set(TARGET asteroids)
set(SRC 
    src/main.cpp
    include/Game.hpp
    src/Game.cpp
    include/Renderer.hpp
    src/Renderer.cpp
    include/Observer/Observer.hpp
    include/Observer/Subject.hpp
    include/Types/Vec2.hpp
)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE include)
target_compile_options(${TARGET} PRIVATE -Wall -Wextra)
target_link_libraries(${TARGET} PRIVATE SDL2main SDL2-static)
