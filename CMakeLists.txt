cmake_minimum_required(VERSION 3.22.1)
project(GOL)

if(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
    include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
else()
    message(FATAL_ERROR "Conan toolchain file not found: ${CMAKE_BINARY_DIR}/conan_toolchain.cmake. Please run 'conan install .' first.")
endif()

if (APPLE)
    execute_process(COMMAND xcrun --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)

set(SOURCES
        src/EventHandler.cpp
        src/main.cpp
        src/Renderer.cpp
        src/GOL.cpp
)

add_executable(GOL ${SOURCES})

target_link_libraries(GOL SDL2::SDL2 SDL2::SDL2main)
