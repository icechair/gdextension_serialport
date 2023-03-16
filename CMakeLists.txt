cmake_minimum_required(VERSION 3.19)

project(gdextension-serialport)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/gdextension.cmake)
include(cmake/serialport.cmake)

add_library(${PROJECT_NAME} SHARED
  src/port_config.cc
  src/serial.cc
  src/register_types.cc
  include/register_types.h
)
message(INFO " GDExtension_BINARY_DIR: ${gdextension_BINARY_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE
  "include"
  "src"
  ${gdextension_BINARY_DIR}/gen/include

  ${serialport_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PUBLIC serialport godot::cpp)

set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS ${GODOT_COMPILE_FLAGS})
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS ${GODOT_LINKER_FLAGS})

set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "gdserialport")
