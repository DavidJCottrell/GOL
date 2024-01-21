cmake_minimum_required(VERSION 3.26)
project(GOL)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES
        EventHandler.cpp
        main.cpp
        Renderer.cpp
        GOL.cpp
)

add_executable(GOL ${SOURCES})

target_link_libraries(GOL ${SDL2_MAIN_LIBRARIES} ${SDL2_LIBRARIES})
