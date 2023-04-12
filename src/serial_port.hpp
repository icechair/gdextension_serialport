#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include "port_config.hpp"
#include <array>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <libserialport.hpp>

VARIANT_ENUM_CAST(sp_return);
VARIANT_ENUM_CAST(sp_mode);
namespace godot {

class SerialPort : public RefCounted {
	GDCLASS(SerialPort, RefCounted)
private:
	sp_port* _port = nullptr;
	String _name = "";
	std::array<uint8_t, 256> _buffer = {};

protected:
	static void _bind_methods();

public:
	static PackedStringArray get_port_names();
	sp_return open(sp_mode flags, Ref<PortConfig> cfg);
	sp_return close();
	void set_port_name(String name) { _name = name; }
	String get_port_name() { return _name; }
	sp_return write(PackedByteArray data);
	void _process(float delta);
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
