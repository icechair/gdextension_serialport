#include "serial_port.hpp"
#include "port_config.hpp"
#include <libserialport.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <vector>
namespace godot {
void SerialPort::_bind_methods() {
	ClassDB::bind_static_method(
			"SerialPort", D_METHOD("get_port_names"), &SerialPort::get_port_names);

	ClassDB::bind_method(D_METHOD("set_port_name"), &SerialPort::set_port_name);
	ClassDB::bind_method(D_METHOD("get_port_name"), &SerialPort::get_port_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "port_name"), "set_port_name", "get_port_name");

	ClassDB::bind_method(D_METHOD("open"), &SerialPort::open);
	ClassDB::bind_method(D_METHOD("close"), &SerialPort::close);
	ClassDB::bind_method(D_METHOD("write"), &SerialPort::write);

	ADD_SIGNAL(MethodInfo("byte_received", PropertyInfo(Variant::INT, "data")));

	BIND_ENUM_CONSTANT(SP_ERR_ARG);
	BIND_ENUM_CONSTANT(SP_ERR_FAIL);
	BIND_ENUM_CONSTANT(SP_ERR_MEM);
	BIND_ENUM_CONSTANT(SP_ERR_SUPP);
	BIND_ENUM_CONSTANT(SP_OK);

	BIND_ENUM_CONSTANT(SP_MODE_READ);
	BIND_ENUM_CONSTANT(SP_MODE_READ_WRITE);
	BIND_ENUM_CONSTANT(SP_MODE_WRITE);
}

PackedStringArray
SerialPort::get_port_names() {
	sp_port** ports{};
	sp_list_ports(&ports);
	PackedStringArray names{};
	for (int i = 0; ports[i] != nullptr; i++) {
		String name{ sp_get_port_name(ports[i]) };
		names.append(name);
	}
	sp_free_port_list(ports);
	return names;
}

sp_return SerialPort::open(sp_mode flags, Ref<PortConfig> cfg) {
	if (_port != nullptr) {
		UtilityFunctions::printerr("SerialPort::open(): failed: port already open");
		return sp_return::SP_ERR_FAIL;
	}
	sp_return status = sp_get_port_by_name(_name.utf8().get_data(), &_port);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::open(): get_port_by_name failed: ", status);
		_port = nullptr;
		return status;
	}
	UtilityFunctions::print("SerialPort::open(): cfg: ", cfg);
	cfg.instantiate();
	status = sp_set_config(_port, cfg->ptr());
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::open(): set_config failed: ", status);
		sp_free_port(_port);
		_port = nullptr;
		return status;
	}

	status = sp_open(_port, flags);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::open(): open failed: ", status);
		sp_free_port(_port);
		_port = nullptr;
		return status;
	}

	return sp_return::SP_OK;
}

sp_return SerialPort::close() {
	if (_port == nullptr) {
		UtilityFunctions::printerr("SerialPort::close(): failed: was not open");
		return sp_return::SP_ERR_ARG;
	}
	sp_return status = sp_close(_port);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::close(): close failed: ", status);
		return status;
	}
	return sp_return::SP_OK;
}

sp_return SerialPort::write(PackedByteArray data) {
	if (_port == nullptr) {
		UtilityFunctions::printerr("SerialPort::write() failed: port is not open");
		return sp_return::SP_ERR_FAIL;
	}
	sp_return status = sp_nonblocking_write(_port, data.ptr(), data.size());
	if (status < sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::write() failed: ", status);
	}
	return status;
}

void SerialPort::_process(float delta) {
	if (_port == nullptr) {
		return;
	}

	sp_return status = sp_nonblocking_read(_port, _buffer.data(), _buffer.size());
	if (status > 0) {
		UtilityFunctions::print("SerialPort::_process(): nonblocking_read: ", status);
		for (int i = 0; i < status; i++) {
			emit_signal("byte_received", _buffer[i]);
		}
	}
}

}; //namespace godot
