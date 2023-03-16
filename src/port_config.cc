#include "port_config.hpp"
#include <godot_cpp/core/class_db.hpp>

namespace godot {

PortConfig::PortConfig()
{
  sp_new_config(&_ptr);
}

PortConfig::~PortConfig()
{
  sp_free_config(_ptr);
}

void
PortConfig::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("set_baudrate"), &PortConfig::set_baudrate);
  ClassDB::bind_method(D_METHOD("get_baudrate"), &PortConfig::get_baudrate);
  ClassDB::add_property("PortConfig",
                        PropertyInfo(Variant::INT, "baudrate"),
                        "set_baudrate",
                        "get_baudrate");
}

void
PortConfig::set_baudrate(int bd)
{
  sp_set_config_baudrate(_ptr, bd);
}

int
PortConfig::get_baudrate() const
{
  int baudrate = 0;
  sp_get_config_baudrate(_ptr, &baudrate);
  return baudrate;
}
};
