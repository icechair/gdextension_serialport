#ifndef PORT_CONFIG_HPP
#define PORT_CONFIG_HPP

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <libserialport.hpp>

VARIANT_ENUM_CAST(sp_parity);
VARIANT_ENUM_CAST(sp_rts);
VARIANT_ENUM_CAST(sp_cts);
VARIANT_ENUM_CAST(sp_dtr);
VARIANT_ENUM_CAST(sp_dsr);
VARIANT_ENUM_CAST(sp_xonxoff);
VARIANT_ENUM_CAST(sp_flowcontrol);

namespace godot {
class PortConfig : public Object
{
  GDCLASS(PortConfig, Object)
private:
  sp_port_config* _ptr;

protected:
  static void _bind_methods();

public:
  PortConfig();
  ~PortConfig();
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
}

#endif // PORT_CONFIG_HPP
