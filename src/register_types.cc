#include "register_types.h"
#include "serial_port.hpp"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

namespace godot {
void init_gdserialport(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<SerialPort>();
}

void uninit_gdserialport(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
		// Initialization.
		GDExtensionBool GDE_EXPORT
		gdext_init_gdserialport(const GDExtensionInterface* p_interface,
				GDExtensionClassLibraryPtr p_library,
				GDExtensionInitialization* r_initialization) {
	GDExtensionBinding::InitObject init_obj(
			p_interface, p_library, r_initialization);

	init_obj.register_initializer(init_gdserialport);
	init_obj.register_terminator(uninit_gdserialport);
	init_obj.set_minimum_library_initialization_level(
			MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}; //namespace godot
