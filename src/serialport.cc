#include "serialport.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

SerialPort::SerialPort() {}

SerialPort::~SerialPort() {}

void
SerialPort::_bind_methods()
{
}

void
SerialPort::_get_property_list(godot::List<godot::PropertyInfo>* r_props) const
{
  sp_port** port_list;
  sp_list_ports(&port_list);
  godot::PackedStringArray port_names{};
  for (int i = 0; port_list[i] != nullptr; i++) {
    char* name = sp_get_port_name(port_list[i]);
    godot::UtilityFunctions::print("_get_property_list: port_name: ", name);
    godot::String gname{ name };
    godot::UtilityFunctions::print("_get_property_list: gName: ", gname);
    port_names.append(gname);
  }
  sp_free_port_list(port_list);
  godot::String hint{ "," };
  hint = hint.join(port_names);
  godot::UtilityFunctions::print("_get_property_list: hint: ", hint);
  r_props->push_back(godot::PropertyInfo(
    godot::Variant::STRING, "port_name", godot::PROPERTY_HINT_ENUM, hint));
}

bool
SerialPort::_get(const godot::StringName& p_property,
                 godot::Variant& r_value) const
{
  if (p_property != godot::StringName("port_name"))
    return false;
  if (_port_name.is_empty()) {
    return false;
  }
  r_value = _port_name;
  return true;
}

bool
SerialPort::_set(const godot::StringName& p_property,
                 const godot::Variant& p_value)
{
  godot::UtilityFunctions::print("SerialPort::_set");
  if (p_property != godot::StringName("port_name"))
    return false;

  const char* port_name = ((godot::String)p_value).utf8().get_data();
  godot::UtilityFunctions::print("SerialPort::_set: port_name: ", port_name);

  sp_port* port;
  auto status = sp_get_port_by_name(port_name, &port);
  sp_free_port(port);
  godot::UtilityFunctions::print("SerialPort::_set: status: ", status);
  if (status != sp_return::SP_OK)
    return false;

  _port_name = (godot::String)p_value;
  godot::UtilityFunctions::print("SerialPort::_set: _port_name: ", _port_name);
  return true;
}

void
SerialPort::_process(float delta)
{
}

void
SerialPort::_ready()
{
  godot::UtilityFunctions::print("SerialPort::_ready");
}
