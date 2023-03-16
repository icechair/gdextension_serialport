#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <libserialport.h>
namespace godot {

class Serial : public Object
{
  GDCLASS(Serial, Object)
private:
protected:
  static void _bind_methods();

public:
  PackedStringArray get_port_names();
};
};

#endif // SERIAL_HPP
