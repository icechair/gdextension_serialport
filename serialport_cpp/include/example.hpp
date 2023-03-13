#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>

class Example : public godot::Sprite2D
{
  GDCLASS(Example, godot::Sprite2D)

private:
  float time_passed;

protected:
  static void _bind_methods();

public:
  Example();
  ~Example();

  void _process(float delta);
};

#endif
