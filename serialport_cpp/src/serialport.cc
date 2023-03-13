#include "serialport.hpp"
#include <libserialport.h>

#include <iterator>

class Port
{
public:
  Port(sp_port* port)
    : _port(port){};
  ~Port(){};

  sp_return close() { return sp_close(_port); }
  sp_return open(sp_mode flags) { return sp_open(_port, flags); }

private:
  sp_port* _port;
};

class Ports
{
public:
  Ports() { sp_list_ports(&_list); }
  ~Ports() { sp_free_port_list(_list); }

private:
  sp_port** _list;
};

void
foo()
{
  sp_port** ports{};
  sp_list_ports(&ports);
}
