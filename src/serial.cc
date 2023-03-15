#include "serial.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <libserialport.h>
namespace godot {
void
Serial::_bind_methods()
{

  godot::ClassDB::bind_method(godot::D_METHOD("get_port_names"),
                              &Serial::get_port_names);
}
PackedStringArray
Serial::get_port_names()
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
