#include "port_config.hpp"
#include <godot_cpp/core/class_db.hpp>

namespace godot {

PortConfig::PortConfig() {
	sp_new_config(&_ptr);
}

PortConfig::~PortConfig() {
	sp_free_config(_ptr);
}

void PortConfig::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_baudrate"), &PortConfig::set_baudrate);
	ClassDB::bind_method(D_METHOD("get_baudrate"), &PortConfig::get_baudrate);
	ClassDB::add_property("PortConfig",
			PropertyInfo(Variant::INT, "baudrate"),
			"set_baudrate",
			"get_baudrate");

	ClassDB::bind_method(D_METHOD("set_bits"), &PortConfig::set_bits);
	ClassDB::bind_method(D_METHOD("get_bits"), &PortConfig::get_bits);
	ClassDB::add_property(
			"PortConfig", PropertyInfo(Variant::INT, "bits"), "set_bits", "get_bits");

	ClassDB::bind_method(D_METHOD("set_parity"), &PortConfig::set_parity);
	ClassDB::bind_method(D_METHOD("get_parity"), &PortConfig::get_parity);
	ClassDB::add_property("PortConfig",
			PropertyInfo(Variant::INT, "parity"),
			"set_parity",
			"get_parity");

	ClassDB::bind_method(D_METHOD("set_stopbits"), &PortConfig::set_stopbits);
	ClassDB::bind_method(D_METHOD("get_stopbits"), &PortConfig::get_stopbits);
	ClassDB::add_property("PortConfig",
			PropertyInfo(Variant::INT, "stopbits"),
			"set_stopbits",
			"get_stopbits");

	ClassDB::bind_method(D_METHOD("set_rts"), &PortConfig::set_rts);
	ClassDB::bind_method(D_METHOD("get_rts"), &PortConfig::get_rts);
	ClassDB::add_property(
			"PortConfig", PropertyInfo(Variant::INT, "rts"), "set_rts", "get_rts");

	ClassDB::bind_method(D_METHOD("set_cts"), &PortConfig::set_cts);
	ClassDB::bind_method(D_METHOD("get_cts"), &PortConfig::get_cts);
	ClassDB::add_property(
			"PortConfig", PropertyInfo(Variant::INT, "cts"), "set_cts", "get_cts");

	ClassDB::bind_method(D_METHOD("set_dtr"), &PortConfig::set_dtr);
	ClassDB::bind_method(D_METHOD("get_dtr"), &PortConfig::get_dtr);
	ClassDB::add_property(
			"PortConfig", PropertyInfo(Variant::INT, "dtr"), "set_dtr", "get_dtr");

	ClassDB::bind_method(D_METHOD("set_dsr"), &PortConfig::set_dsr);
	ClassDB::bind_method(D_METHOD("get_dsr"), &PortConfig::get_dsr);
	ClassDB::add_property(
			"PortConfig", PropertyInfo(Variant::INT, "dsr"), "set_dsr", "get_dsr");

	ClassDB::bind_method(D_METHOD("set_xonxoff"), &PortConfig::set_xonxoff);
	ClassDB::bind_method(D_METHOD("get_xonxoff"), &PortConfig::get_xonxoff);
	ClassDB::add_property("PortConfig",
			PropertyInfo(Variant::INT, "xonxoff"),
			"set_xonxoff",
			"get_xonxoff");

	ClassDB::bind_method(D_METHOD("set_flowcontrol"),
			&PortConfig::set_flowcontrol);
	ClassDB::bind_method(D_METHOD("get_flowcontrol"),
			&PortConfig::get_flowcontrol);
	ClassDB::add_property("PortConfig",
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

void PortConfig::set_baudrate(int bd) {
	sp_set_config_baudrate(_ptr, bd);
}

int PortConfig::get_baudrate() const {
	int baudrate = 0;
	sp_get_config_baudrate(_ptr, &baudrate);
	return baudrate;
}

int PortConfig::get_bits() const {
	int bits = 0;
	sp_get_config_bits(_ptr, &bits);
	return bits;
}

void PortConfig::set_bits(const int bits) {
	sp_set_config_bits(_ptr, bits);
}

void PortConfig::set_parity(const sp_parity parity) {
	sp_set_config_parity(_ptr, parity);
}

sp_parity
PortConfig::get_parity() const {
	sp_parity parity;
	sp_get_config_parity(_ptr, &parity);
	return parity;
}

void PortConfig::set_stopbits(const int stopbits) {
	sp_set_config_stopbits(_ptr, stopbits);
}

int PortConfig::get_stopbits() const {
	int stopbits;
	sp_get_config_stopbits(_ptr, &stopbits);
	return stopbits;
}

void PortConfig::set_rts(const sp_rts rts) {
	sp_set_config_rts(_ptr, rts);
}

sp_rts
PortConfig::get_rts() const {
	sp_rts rts;
	sp_get_config_rts(_ptr, &rts);
	return rts;
}

void PortConfig::set_cts(const sp_cts cts) {
	sp_set_config_cts(_ptr, cts);
}

sp_cts
PortConfig::get_cts() const {
	sp_cts cts;
	sp_get_config_cts(_ptr, &cts);
	return cts;
}

void PortConfig::set_dtr(const sp_dtr dtr) {
	sp_set_config_dtr(_ptr, dtr);
}

sp_dtr
PortConfig::get_dtr() const {
	sp_dtr dtr;
	sp_get_config_dtr(_ptr, &dtr);
	return dtr;
}

void PortConfig::set_dsr(const sp_dsr dsr) {
	sp_set_config_dsr(_ptr, dsr);
}

sp_dsr
PortConfig::get_dsr() const {
	sp_dsr dsr;
	sp_get_config_dsr(_ptr, &dsr);
	return dsr;
}

void PortConfig::set_xonxoff(const sp_xonxoff xonxoff) {
	sp_set_config_xon_xoff(_ptr, xonxoff);
}

sp_xonxoff
PortConfig::get_xonxoff() const {
	sp_xonxoff xonxoff;
	sp_get_config_xon_xoff(_ptr, &xonxoff);
	return xonxoff;
}

void PortConfig::set_flowcontrol(const sp_flowcontrol flowcontrol) {
	sp_set_config_flowcontrol(_ptr, flowcontrol);
}

sp_flowcontrol
PortConfig::get_flowcontrol() const {
	return sp_flowcontrol::SP_FLOWCONTROL_NONE;
}

}; // namespace godot
