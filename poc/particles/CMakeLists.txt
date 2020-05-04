cmake_minimum_required(VERSION 3.10)
project(ParticleSystem)

set(CMAKE_CXX_STANDARD 17)

set(TARGET ParticleSystem)

set(SRC
        src/main.cpp
        include/ParticleSystem/BaseParticle.hpp
        include/ParticleSystem/Particle.hpp
        include/ParticleSystem/ParticleEmitter.hpp
        include/ParticleSystem/Policies/BaseInitializationPolicy.hpp
        include/ParticleSystem/Policies/BaseUpdatePolicy.hpp
        include/ParticleSystem/Policies/InitializationPolicy.hpp
        include/ParticleSystem/Policies/UpdatePolicy.hpp
        # TODO: ENTRES TEMPORAIRES, A SUPPRIMER QUAND LE MODULE ENGINE DEVIENT
        # UNE BIBLIOTHEQUE COMPILE SEPAREMENT
        ${CMAKE_SOURCE_DIR}/include/Engine/Types/Color.hpp
        ${CMAKE_SOURCE_DIR}/src/Engine/Types/Color.cpp
        ${CMAKE_SOURCE_DIR}/include/Engine/Types/Vec2.hpp)

add_executable(${TARGET} ${SRC})
target_compile_options(${TARGET} PRIVATE -DSDL_MAIN_HANDLED)
target_include_directories(${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/include)

if(MSVC)
    string(REGEX REPLACE "/W[3|4]" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    if(MINGW)
        target_link_libraries(${TARGET} PRIVATE mingw32)
    endif()
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra)
endif()

target_link_libraries(${TARGET} PRIVATE SDL2main SDL2-static)
