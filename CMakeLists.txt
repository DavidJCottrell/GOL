cmake_minimum_required(VERSION 3.26)
project(GOL)

set(CMAKE_CXX_STANDARD 23)

# Add directories libraries
set(CMAKE_PREFIX_PATH "C:/SDK/sdl2;C:/SDK/SDL2_image")

# Find libraries
find_package(SDL2_image REQUIRED)
find_package(SDL2 REQUIRED)

# Add include directories
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

# Source files
set(SOURCES
        EventHandler.cpp
        main.cpp
        Renderer.cpp
        GOL.cpp
)

# Add executable
add_executable(gol ${SOURCES})

# Link against libraries
target_link_libraries(gol ${SDL2_IMAGE_LIBRARIES} ${SDL2_LIBRARIES})
