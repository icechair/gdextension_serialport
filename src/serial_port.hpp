#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <array>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <libserialport.hpp>

VARIANT_ENUM_CAST(sp_return);
VARIANT_ENUM_CAST(sp_mode);

//portconfig
VARIANT_ENUM_CAST(sp_parity);
VARIANT_ENUM_CAST(sp_rts);
VARIANT_ENUM_CAST(sp_cts);
VARIANT_ENUM_CAST(sp_dtr);
VARIANT_ENUM_CAST(sp_dsr);
VARIANT_ENUM_CAST(sp_xonxoff);
VARIANT_ENUM_CAST(sp_flowcontrol);
namespace godot {

class SerialPort : public RefCounted {
	GDCLASS(SerialPort, RefCounted)
private:
	sp_port* _port = nullptr;
	sp_port_config* _cfg = nullptr;
	String _name = "";
	std::array<uint8_t, 256> _buffer = {};

protected:
	static void _bind_methods();

public:
	SerialPort();
	~SerialPort();
	static PackedStringArray get_port_names();
	sp_return open(sp_mode flags);
	sp_return close();
	void set_port_name(String name) { _name = name; }
	String get_port_name() { return _name; }
	sp_return write(PackedByteArray data);
	void _process(float delta);

	void set_baudrate(const int baudrate);
	int get_baudrate() const;
	void set_bits(const int bits);
	int get_bits() const;
	void set_parity(const sp_parity parity);
	sp_parity get_parity() const;
	void set_stopbits(const int stopbits);
	int get_stopbits() const;
	void set_rts(const sp_rts rts);
	sp_rts get_rts() const;
	void set_cts(const sp_cts cts);
	sp_cts get_cts() const;
	void set_dtr(const sp_dtr dtr);
	sp_dtr get_dtr() const;
	void set_dsr(const sp_dsr dsr);
	sp_dsr get_dsr() const;
	void set_xonxoff(const sp_xonxoff xonxoff);
	sp_xonxoff get_xonxoff() const;
	void set_flowcontrol(const sp_flowcontrol);
	sp_flowcontrol get_flowcontrol() const;
};
}; //namespace godot

#endif // SERIAL_HPP
