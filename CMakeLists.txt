cmake_minimum_required(VERSION 3.26)
project(GOL)

set(CMAKE_CXX_STANDARD 23)

# Find libraries
find_package(SDL2 REQUIRED)

# Add include directories
include_directories(${SDL2_INCLUDE_DIRS})

# Source files
set(SOURCES
        EventHandler.cpp
        main.cpp
        Renderer.cpp
        GOL.cpp
)

# Add executable
add_executable(GOL ${SOURCES})

# Link against libraries
target_link_libraries(GOL ${SDL2_MAIN_LIBRARIES} ${SDL2_LIBRARIES})
