#include "serial_port.hpp"
#include <libserialport.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <iostream>
namespace godot {

SerialPort::SerialPort() {
}

SerialPort::~SerialPort() {
	if (_port != nullptr) {
		sp_close(_port);
		sp_free_port(_port);
	}
}

void SerialPort::_bind_methods() {
	ClassDB::bind_static_method(
			"SerialPort", D_METHOD("get_port_names"), &SerialPort::get_port_names);

	ClassDB::bind_method(D_METHOD("set_port_name"), &SerialPort::set_port_name);
	ClassDB::bind_method(D_METHOD("get_port_name"), &SerialPort::get_port_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "port_name"), "set_port_name", "get_port_name");

	ClassDB::bind_method(D_METHOD("open"), &SerialPort::open);
	ClassDB::bind_method(D_METHOD("close"), &SerialPort::close);
	ClassDB::bind_method(D_METHOD("write", "data"), &SerialPort::write);
	ClassDB::bind_method(D_METHOD("read"), &SerialPort::read);
	ClassDB::bind_method(D_METHOD("is_open"), &SerialPort::is_open);

	ADD_SIGNAL(MethodInfo("byte_received", PropertyInfo(Variant::INT, "data")));

	BIND_ENUM_CONSTANT(SP_ERR_ARG);
	BIND_ENUM_CONSTANT(SP_ERR_FAIL);
	BIND_ENUM_CONSTANT(SP_ERR_MEM);
	BIND_ENUM_CONSTANT(SP_ERR_SUPP);
	BIND_ENUM_CONSTANT(SP_OK);

	BIND_ENUM_CONSTANT(SP_MODE_READ);
	BIND_ENUM_CONSTANT(SP_MODE_READ_WRITE);
	BIND_ENUM_CONSTANT(SP_MODE_WRITE);

	//portconfig
	ClassDB::bind_method(D_METHOD("set_baudrate"), &SerialPort::set_baudrate);
	ClassDB::bind_method(D_METHOD("get_baudrate"), &SerialPort::get_baudrate);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "baudrate"), "set_baudrate", "get_baudrate");

	ClassDB::bind_method(D_METHOD("set_bits"), &SerialPort::set_bits);
	ClassDB::bind_method(D_METHOD("get_bits"), &SerialPort::get_bits);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "bits"), "set_bits", "get_bits");

	ClassDB::bind_method(D_METHOD("set_parity"), &SerialPort::set_parity);
	ClassDB::bind_method(D_METHOD("get_parity"), &SerialPort::get_parity);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "parity"), "set_parity", "get_parity");

	ClassDB::bind_method(D_METHOD("set_stopbits"), &SerialPort::set_stopbits);
	ClassDB::bind_method(D_METHOD("get_stopbits"), &SerialPort::get_stopbits);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stopbits"), "set_stopbits", "get_stopbits");

	ClassDB::bind_method(D_METHOD("set_rts"), &SerialPort::set_rts);
	ClassDB::bind_method(D_METHOD("get_rts"), &SerialPort::get_rts);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rts"), "set_rts", "get_rts");

	ClassDB::bind_method(D_METHOD("set_cts"), &SerialPort::set_cts);
	ClassDB::bind_method(D_METHOD("get_cts"), &SerialPort::get_cts);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cts"), "set_cts", "get_cts");

	ClassDB::bind_method(D_METHOD("set_dtr"), &SerialPort::set_dtr);
	ClassDB::bind_method(D_METHOD("get_dtr"), &SerialPort::get_dtr);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dtr"), "set_dtr", "get_dtr");

	ClassDB::bind_method(D_METHOD("set_dsr"), &SerialPort::set_dsr);
	ClassDB::bind_method(D_METHOD("get_dsr"), &SerialPort::get_dsr);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dsr"), "set_dsr", "get_dsr");

	ClassDB::bind_method(D_METHOD("set_xonxoff"), &SerialPort::set_xonxoff);
	ClassDB::bind_method(D_METHOD("get_xonxoff"), &SerialPort::get_xonxoff);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "xonxoff"), "set_xonxoff", "get_xonxoff");

	ClassDB::bind_method(D_METHOD("set_flowcontrol"), &SerialPort::set_flowcontrol);
	ClassDB::bind_method(D_METHOD("get_flowcontrol"), &SerialPort::get_flowcontrol);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "flowcontrol"), "set_flowcontrol", "get_flowcontrol");

	BIND_ENUM_CONSTANT(SP_PARITY_INVALID);
	BIND_ENUM_CONSTANT(SP_PARITY_NONE);
	BIND_ENUM_CONSTANT(SP_PARITY_ODD);
	BIND_ENUM_CONSTANT(SP_PARITY_EVEN);
	BIND_ENUM_CONSTANT(SP_PARITY_MARK);
	BIND_ENUM_CONSTANT(SP_PARITY_SPACE);

	BIND_ENUM_CONSTANT(SP_RTS_INVALID);
	BIND_ENUM_CONSTANT(SP_RTS_OFF);
	BIND_ENUM_CONSTANT(SP_RTS_ON);
	BIND_ENUM_CONSTANT(SP_RTS_FLOW_CONTROL);

	BIND_ENUM_CONSTANT(SP_CTS_INVALID);
	BIND_ENUM_CONSTANT(SP_CTS_IGNORE);
	BIND_ENUM_CONSTANT(SP_CTS_FLOW_CONTROL);

	BIND_ENUM_CONSTANT(SP_DTR_INVALID);
	BIND_ENUM_CONSTANT(SP_DTR_OFF);
	BIND_ENUM_CONSTANT(SP_DTR_ON);
	BIND_ENUM_CONSTANT(SP_DTR_FLOW_CONTROL);

	BIND_ENUM_CONSTANT(SP_DSR_INVALID);
	BIND_ENUM_CONSTANT(SP_DSR_IGNORE);
	BIND_ENUM_CONSTANT(SP_DSR_FLOW_CONTROL);

	BIND_ENUM_CONSTANT(SP_XONXOFF_INVALID);
	BIND_ENUM_CONSTANT(SP_XONXOFF_DISABLED);
	BIND_ENUM_CONSTANT(SP_XONXOFF_IN);
	BIND_ENUM_CONSTANT(SP_XONXOFF_OUT);
	BIND_ENUM_CONSTANT(SP_XONXOFF_INOUT);

	BIND_ENUM_CONSTANT(SP_FLOWCONTROL_NONE);
	BIND_ENUM_CONSTANT(SP_FLOWCONTROL_XONXOFF);
	BIND_ENUM_CONSTANT(SP_FLOWCONTROL_RTSCTS);
	BIND_ENUM_CONSTANT(SP_FLOWCONTROL_DTRDSR);
}

bool SerialPort::is_open() const {
	return _is_open;
}

void SerialPort::set_port_name(String name) {
	_name = name;
}
String SerialPort::get_port_name() const {
	return _name;
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

sp_return SerialPort::_set_config() {
	sp_return status = sp_set_baudrate(_port, _baudrate);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_baudrate failed: ", status, _baudrate);
		return status;
	}

	status = sp_set_bits(_port, _bits);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_bits failed: ", status, _bits);
		return status;
	}

	status = sp_set_parity(_port, _parity);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_parity failed: ", status, _parity);
		return status;
	}

	status = sp_set_stopbits(_port, _stopbits);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_stopbits failed: ", status, _stopbits);
		return status;
	}

	status = sp_set_rts(_port, _rts);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_rts failed: ", status, _rts);
		return status;
	}

	status = sp_set_cts(_port, _cts);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_cts failed: ", status, _cts);
		return status;
	}

	status = sp_set_dtr(_port, _dtr);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_dtr failed: ", status, _dtr);
		return status;
	}

	status = sp_set_dsr(_port, _dsr);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_dsr failed: ", status, _dsr);
		return status;
	}

	status = sp_set_xon_xoff(_port, _xonxoff);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_xonxoff failed: ", status, _xonxoff);
		return status;
	}

	status = sp_set_flowcontrol(_port, _flowcontrol);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::_set_config(): set_flowcontrol failed: ", status, _flowcontrol);
		return status;
	}
	return sp_return::SP_OK;
}

sp_return SerialPort::open(sp_mode flags) {
	if (_is_open) {
		UtilityFunctions::printerr("SerialPort::open(): already open");
		return sp_return::SP_ERR_FAIL;
	}

	sp_return status = sp_get_port_by_name(_name.utf8().get_data(), &_port);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::open(): get_port_by_name failed: ", status);
		return status;
	}

	status = sp_open(_port, flags);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::open(): open failed: ", status);
		return status;
	}

	status = _set_config();
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::open(): _set_config failed: ", status);
		return status;
	}

	_is_open = true;
	return sp_return::SP_OK;
}

sp_return SerialPort::close() {
	_is_open = false;
	sp_return status = sp_close(_port);
	if (status != sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::close(): close failed: ", status);
		return status;
	}
	return sp_return::SP_OK;
}

sp_return SerialPort::write(const PackedByteArray& data) {
	sp_return status = sp_nonblocking_write(_port, data.ptr(), data.size());
	if (status < sp_return::SP_OK) {
		UtilityFunctions::printerr("SerialPort::write() failed: ", status);
	}
	return status;
}

PackedByteArray SerialPort::read() {
	PackedByteArray data{};
	sp_return status = sp_nonblocking_read(_port, _buffer.data(), _buffer.size());
	if (status > 0) {
		for (int i = 0; i < status; i++) {
			data.push_back(_buffer[i]);
		}
	}
	if (status < 0) {
		UtilityFunctions::print("SerialPort::_process(): read failed: ", status);
	}
	return data;
}

void SerialPort::_process(float delta) {
}

void SerialPort::set_baudrate(int baudrate) {
	_baudrate = baudrate;
}

int SerialPort::get_baudrate() const {
	return _baudrate;
}

void SerialPort::set_bits(const int bits) {
	_bits = bits;
}

int SerialPort::get_bits() const {
	return _bits;
}

void SerialPort::set_parity(const sp_parity parity) {
	_parity = parity;
}

sp_parity
SerialPort::get_parity() const {
	return _parity;
}

void SerialPort::set_stopbits(const int stopbits) {
	_stopbits = stopbits;
}

int SerialPort::get_stopbits() const {
	return _stopbits;
}

void SerialPort::set_rts(const sp_rts rts) {
	_rts = rts;
}

sp_rts
SerialPort::get_rts() const {
	return _rts;
}

void SerialPort::set_cts(const sp_cts cts) {
	_cts = cts;
}

sp_cts
SerialPort::get_cts() const {
	return _cts;
}

void SerialPort::set_dtr(const sp_dtr dtr) {
	_dtr = dtr;
}

sp_dtr
SerialPort::get_dtr() const {
	return _dtr;
}

void SerialPort::set_dsr(const sp_dsr dsr) {
	_dsr = dsr;
}

sp_dsr
SerialPort::get_dsr() const {
	return _dsr;
}

void SerialPort::set_xonxoff(const sp_xonxoff xonxoff) {
	_xonxoff = xonxoff;
}

sp_xonxoff
SerialPort::get_xonxoff() const {
	return _xonxoff;
}

void SerialPort::set_flowcontrol(const sp_flowcontrol flowcontrol) {
	_flowcontrol = flowcontrol;
}

sp_flowcontrol
SerialPort::get_flowcontrol() const {
	return _flowcontrol;
}

}; //namespace godot
