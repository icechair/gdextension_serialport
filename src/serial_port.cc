#include "serial_port.hpp"
#include <libserialport.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <iostream>
#include <vector>
namespace godot {

SerialPort::SerialPort() {
	sp_new_config(&_cfg);
}
SerialPort::~SerialPort() {
	sp_free_config(_cfg);
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

	//portconfig
	ClassDB::bind_method(D_METHOD("set_baudrate"), &SerialPort::set_baudrate);
	ClassDB::bind_method(D_METHOD("get_baudrate"), &SerialPort::get_baudrate);
	ClassDB::add_property("SerialPort",
			PropertyInfo(Variant::INT, "baudrate"),
			"set_baudrate",
			"get_baudrate");

	ClassDB::bind_method(D_METHOD("set_bits"), &SerialPort::set_bits);
	ClassDB::bind_method(D_METHOD("get_bits"), &SerialPort::get_bits);
	ClassDB::add_property(
			"SerialPort", PropertyInfo(Variant::INT, "bits"), "set_bits", "get_bits");

	ClassDB::bind_method(D_METHOD("set_parity"), &SerialPort::set_parity);
	ClassDB::bind_method(D_METHOD("get_parity"), &SerialPort::get_parity);
	ClassDB::add_property("SerialPort",
			PropertyInfo(Variant::INT, "parity"),
			"set_parity",
			"get_parity");

	ClassDB::bind_method(D_METHOD("set_stopbits"), &SerialPort::set_stopbits);
	ClassDB::bind_method(D_METHOD("get_stopbits"), &SerialPort::get_stopbits);
	ClassDB::add_property("SerialPort",
			PropertyInfo(Variant::INT, "stopbits"),
			"set_stopbits",
			"get_stopbits");

	ClassDB::bind_method(D_METHOD("set_rts"), &SerialPort::set_rts);
	ClassDB::bind_method(D_METHOD("get_rts"), &SerialPort::get_rts);
	ClassDB::add_property(
			"SerialPort", PropertyInfo(Variant::INT, "rts"), "set_rts", "get_rts");

	ClassDB::bind_method(D_METHOD("set_cts"), &SerialPort::set_cts);
	ClassDB::bind_method(D_METHOD("get_cts"), &SerialPort::get_cts);
	ClassDB::add_property(
			"SerialPort", PropertyInfo(Variant::INT, "cts"), "set_cts", "get_cts");

	ClassDB::bind_method(D_METHOD("set_dtr"), &SerialPort::set_dtr);
	ClassDB::bind_method(D_METHOD("get_dtr"), &SerialPort::get_dtr);
	ClassDB::add_property(
			"SerialPort", PropertyInfo(Variant::INT, "dtr"), "set_dtr", "get_dtr");

	ClassDB::bind_method(D_METHOD("set_dsr"), &SerialPort::set_dsr);
	ClassDB::bind_method(D_METHOD("get_dsr"), &SerialPort::get_dsr);
	ClassDB::add_property(
			"SerialPort", PropertyInfo(Variant::INT, "dsr"), "set_dsr", "get_dsr");

	ClassDB::bind_method(D_METHOD("set_xonxoff"), &SerialPort::set_xonxoff);
	ClassDB::bind_method(D_METHOD("get_xonxoff"), &SerialPort::get_xonxoff);
	ClassDB::add_property("SerialPort",
			PropertyInfo(Variant::INT, "xonxoff"),
			"set_xonxoff",
			"get_xonxoff");

	ClassDB::bind_method(D_METHOD("set_flowcontrol"),
			&SerialPort::set_flowcontrol);
	ClassDB::bind_method(D_METHOD("get_flowcontrol"),
			&SerialPort::get_flowcontrol);
	ClassDB::add_property("SerialPort",
			PropertyInfo(Variant::INT, "flowcontrol"),
			"set_flowcontrol",
			"get_flowcontrol");

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

PackedStringArray
SerialPort::get_port_names() {
	UtilityFunctions::print("SerialPort::get_port_names()");
	std::cout << "get_port_names" << std::endl;
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

sp_return SerialPort::open(sp_mode flags) {
	UtilityFunctions::print("SerialPort::open()");
	std::cout << "open" << std::endl;
	if (_port != nullptr) {
		UtilityFunctions::printerr("SerialPort::open(): failed: port already open");
		return sp_return::SP_ERR_FAIL;
	} /*
	 sp_return status = sp_get_port_by_name(_name.utf8().get_data(), &_port);
	 if (status != sp_return::SP_OK) {
		 UtilityFunctions::printerr("SerialPort::open(): get_port_by_name failed: ", status);
		 _port = nullptr;
		 return status;
	 }
	 UtilityFunctions::print("SerialPort::open(): cfg: ", cfg);
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
 */
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

void SerialPort::set_baudrate(int bd) {
	sp_set_config_baudrate(_cfg, bd);
}

int SerialPort::get_baudrate() const {
	int baudrate = 0;
	sp_get_config_baudrate(_cfg, &baudrate);
	return baudrate;
}

int SerialPort::get_bits() const {
	int bits = 0;
	sp_get_config_bits(_cfg, &bits);
	return bits;
}

void SerialPort::set_bits(const int bits) {
	sp_set_config_bits(_cfg, bits);
}

void SerialPort::set_parity(const sp_parity parity) {
	sp_set_config_parity(_cfg, parity);
}

sp_parity
SerialPort::get_parity() const {
	sp_parity parity;
	sp_get_config_parity(_cfg, &parity);
	return parity;
}

void SerialPort::set_stopbits(const int stopbits) {
	sp_set_config_stopbits(_cfg, stopbits);
}

int SerialPort::get_stopbits() const {
	int stopbits;
	sp_get_config_stopbits(_cfg, &stopbits);
	return stopbits;
}

void SerialPort::set_rts(const sp_rts rts) {
	sp_set_config_rts(_cfg, rts);
}

sp_rts
SerialPort::get_rts() const {
	sp_rts rts;
	sp_get_config_rts(_cfg, &rts);
	return rts;
}

void SerialPort::set_cts(const sp_cts cts) {
	sp_set_config_cts(_cfg, cts);
}

sp_cts
SerialPort::get_cts() const {
	sp_cts cts;
	sp_get_config_cts(_cfg, &cts);
	return cts;
}

void SerialPort::set_dtr(const sp_dtr dtr) {
	sp_set_config_dtr(_cfg, dtr);
}

sp_dtr
SerialPort::get_dtr() const {
	sp_dtr dtr;
	sp_get_config_dtr(_cfg, &dtr);
	return dtr;
}

void SerialPort::set_dsr(const sp_dsr dsr) {
	sp_set_config_dsr(_cfg, dsr);
}

sp_dsr
SerialPort::get_dsr() const {
	sp_dsr dsr;
	sp_get_config_dsr(_cfg, &dsr);
	return dsr;
}

void SerialPort::set_xonxoff(const sp_xonxoff xonxoff) {
	sp_set_config_xon_xoff(_cfg, xonxoff);
}

sp_xonxoff
SerialPort::get_xonxoff() const {
	sp_xonxoff xonxoff;
	sp_get_config_xon_xoff(_cfg, &xonxoff);
	return xonxoff;
}

void SerialPort::set_flowcontrol(const sp_flowcontrol flowcontrol) {
	sp_set_config_flowcontrol(_cfg, flowcontrol);
}

sp_flowcontrol
SerialPort::get_flowcontrol() const {
	return sp_flowcontrol::SP_FLOWCONTROL_NONE;
}

}; //namespace godot
