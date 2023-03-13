#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "example.hpp"

void
init_serialport_cpp(godot::ModuleInitializationLevel p_level)
{
  if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  godot::ClassDB::register_class<Example>();
}

void
uninit_serialport_cpp(godot::ModuleInitializationLevel p_level)
{
  if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
}

extern "C"
  // Initialization.
  GDExtensionBool GDE_EXPORT
  serialport_cpp_init(const GDExtensionInterface* p_interface,
                      GDExtensionClassLibraryPtr p_library,
                      GDExtensionInitialization* r_initialization)
{
  godot::GDExtensionBinding::InitObject init_obj(
    p_interface, p_library, r_initialization);

  init_obj.register_initializer(init_serialport_cpp);
  init_obj.register_terminator(uninit_serialport_cpp);
  init_obj.set_minimum_library_initialization_level(
    godot::MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
