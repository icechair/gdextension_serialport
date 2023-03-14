
include(ExternalProject)

set(SERIALPORT_BIN ${CMAKE_BINARY_DIR}/libserialport)
set(SERIALPORT_STATIC_LIB ${CMAKE_BINARY_DIR}/libserialport/lib/libserialport.a)
ExternalProject_Add(libserialport
  PREFIX ${SERIALPORT_BIN}
  BUILD_IN_SOURCE ON
  GIT_REPOSITORY https://github.com/sigrokproject/libserialport.git
  GIT_TAG libserialport-0.1.1
  UPDATE_DISCONNECTED ON
  CONFIGURE_COMMAND "./autogen.sh" COMMAND "./configure" ARGS "--prefix=${SERIALPORT_BIN}"
  BUILD_COMMAND "make"
  INSTALL_COMMAND make DEST=${SERIALPORT_BIN} install
  BUILD_BYPRODUCTS ${SERIALPORT_STATIC_LIB}
)

ExternalProject_Get_property(libserialport SOURCE_DIR)
ExternalProject_Get_property(libserialport INSTALL_DIR)
message(INFO " libserialport SOURCE_DIR: '${SOURCE_DIR}'")
message(INFO " libserialport SOURCE_DIR: '${INSTALL_DIR}'")
add_library(serialport STATIC IMPORTED GLOBAL)
add_dependencies(serialport libserialport)
set_target_properties(serialport PROPERTIES IMPORTED_LOCATION ${SERIALPORT_STATIC_LIB})
set_target_properties(serialport PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${SOURCE_DIR})
