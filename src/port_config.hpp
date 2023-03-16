#ifndef PORT_CONFIG_HPP
#define PORT_CONFIG_HPP

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <libserialport.hpp>
#include <memory>

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
};
}

#endif // PORT_CONFIG_HPP
