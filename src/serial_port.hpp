#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <libserialport.hpp>

namespace godot {

class SerialPort : public Object {
	GDCLASS(SerialPort, Object)
private:
protected:
	static void _bind_methods();

public:
	static PackedStringArray get_port_names();
};
}; //namespace godot
/*
VARIANT_ENUM_CAST(sp_return);
VARIANT_ENUM_CAST(sp_mode);
VARIANT_ENUM_CAST(sp_event);
VARIANT_ENUM_CAST(sp_buffer);
VARIANT_ENUM_CAST(sp_signal);
VARIANT_ENUM_CAST(sp_transport);
*/
#endif // SERIAL_HPP
