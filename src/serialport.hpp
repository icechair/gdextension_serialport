#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/string.hpp>
#include <libserialport.h>

class SerialPort : public godot::Node
{
  GDCLASS(SerialPort, godot::Node)

private:
  godot::String _port_name = "";

protected:
  static void _bind_methods();
  void _get_property_list(godot::List<godot::PropertyInfo>* r_props) const;
  bool _get(const godot::StringName& p_property, godot::Variant& r_value) const;
  bool _set(const godot::StringName& p_property, const godot::Variant& p_value);

public:
  SerialPort();
  ~SerialPort();

  void _ready() override;
  void _process(float delta);
};

#endif
