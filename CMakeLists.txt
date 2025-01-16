cmake_minimum_required(VERSION 3.30)
project(Pong)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pong src/main.cpp
                    src/sdlapp.cpp
                    src/ltexture.cpp
                    src/ball.cpp
                    src/paddle.cpp)

# Find SDL from vcpkg
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# Error checking
if (SDL2_FOUND)
    message(STATUS "SDL2 found: ${SDL2_DIR}")
else()
    message(FATAL_ERROR "SDL2 not found!")
endif()
if (SDL2_image_FOUND)
    message(STATUS "SDL2_image found: ${SDL2_image_DIR}")
else()
    message(FATAL_ERROR "SDL2_image not found!")
endif()
if (SDL2_ttf_FOUND)
    message(STATUS "SDL2_ttf found: ${SDL2_ttf_DIR}")
else()
    message(FATAL_ERROR "SDL2_ttf not found!")
endif()
if (SDL2_mixer_FOUND)
    message(STATUS "SDL2_mixer found: ${SDL2_mixer_DIR}")
else()
    message(FATAL_ERROR "SDL2_mixer not found!")
endif()

# Get the static libraries
target_link_libraries(Pong PRIVATE SDL2::SDL2)
target_link_libraries(Pong PRIVATE SDL2_image::SDL2_image-static)
target_link_libraries(Pong PRIVATE SDL2_ttf::SDL2_ttf-static)
target_link_libraries(Pong PRIVATE SDL2_mixer::SDL2_mixer-static)
