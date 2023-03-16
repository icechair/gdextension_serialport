#ifndef LIBSERIALPORT_HPP
#define LIBSERIALPORT_HPP
#include <libserialport.h>

class sp_deleter
{
  void operator()(sp_port* ptr) { sp_free_port(ptr); };
  void operator()(sp_port** ptr) { sp_free_port_list(ptr); };
  void operator()(sp_port_config* ptr) { sp_free_config(ptr); };
  void operator()(sp_event_set* ptr) { sp_free_event_set(ptr); };
};

#endif // LIBSERIALPORT_HPP
