cmake_minimum_required(VERSION 3.19)

project(gdextension-serialport)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
    GDExtension
    GIT_REPOSITORY https://github.com/godotengine/godot-cpp.git
    GIT_TAG godot-4.0-stable
)

FetchContent_MakeAvailable(GDExtension)

#FetchContent_GetProperties(GDExtension)
#if(NOT GDExtension_POPULATED)
#    FetchContent_Populate(GDExtension)
#endif()
#
#ExternalProject_add(GDExtension
#    SOURCE_DIR ${GDExtension_SOURCE_DIR}
#)

add_subdirectory(serialport_cpp)
add_subdirectory(src)
