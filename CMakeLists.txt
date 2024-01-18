cmake_minimum_required(VERSION 3.26)
project(GOL)

set(CMAKE_CXX_STANDARD 23)

# Find SDL2 and SDL2_image libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add include directories for SDL2 and SDL2_image
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Add your source files
set(SOURCES
        EventHandler.cpp
        GOL.cpp
        main.cpp
        Renderer.cpp
)

# Add executable
add_executable(YourExecutable ${SOURCES})

# Link against SDL2 and SDL2_image libraries
target_link_libraries(YourExecutable ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
