#include "example.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void
Example::_bind_methods()
{
}

Example::Example()
{
  // initialize any variables here
  time_passed = 0.0;
}

Example::~Example()
{
  // add your cleanup here
}

void
Example::_process(float delta)
{
  time_passed += delta;

  Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)),
                                 10.0 + (10.0 * cos(time_passed * 1.5)));

  set_position(new_position);
}
