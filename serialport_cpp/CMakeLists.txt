cmake_minimum_required(VERSION 3.11)

include(cmake/serialport.cmake)

project(serialport_cpp)
add_library(${PROJECT_NAME} OBJECT src/serialport.cc)
target_link_libraries(${PROJECT_NAME} serialport)

target_include_directories(${PROJECT_NAME} PUBLIC
  include
  PRIVATE
  ${serialport_SOURCE_DIR}
)
