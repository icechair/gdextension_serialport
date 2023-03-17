#include "serial_port.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <libserialport.h>
namespace godot {
void
SerialPort::_bind_methods()
{
  ClassDB::bind_static_method(
    "SerialPort", D_METHOD("get_port_names"), &SerialPort::get_port_names);
}

PackedStringArray
SerialPort::get_port_names()
{
  sp_port** ports{};
  sp_list_ports(&ports);
  godot::PackedStringArray names{};
  for (int i = 0; ports[i] != nullptr; i++) {
    String name{ sp_get_port_name(ports[i]) };
    names.append(name);
  }
  sp_free_port_list(ports);
  return names;
}

};
