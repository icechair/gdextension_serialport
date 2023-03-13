
include(ExternalProject)

set(SERIALPORT_BIN ${CMAKE_CURRENT_BINARY_DIR}/libserialport)

ExternalProject_Add(libserialport
  PREFIX ${SERIALPORT_BIN}
  BUILD_IN_SOURCE ON
  GIT_REPOSITORY https://github.com/sigrokproject/libserialport.git
  GIT_TAG libserialport-0.1.1
  CONFIGURE_COMMAND "./autogen.sh" COMMAND "./configure" ARGS "--prefix=${SERIALPORT_BIN}"
  BUILD_COMMAND ${MAKE}
  INSTALL_COMMAND
)
ExternalProject_Get_property(libserialport SOURCE_DIR)
ExternalProject_Get_property(libserialport INSTALL_DIR)
message(INFO " libserialport SOURCE_DIR: '${SOURCE_DIR}'")
message(INFO " libserialport SOURCE_DIR: '${INSTALL_DIR}'")
add_library(serialport STATIC IMPORTED GLOBAL)
add_dependencies(serialport libserialport)
set_target_properties(serialport PROPERTIES IMPORTED_LOCATION ${SOURCE_DIR}/.libs/libserialport.a)
set_target_properties(serialport PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${SOURCE_DIR})
