extends Node2D


@onready var buttonConnect: Button = $"HFlowContainer/ButtonConnect"
@onready var buttonRefresh: Button = $"HFlowContainer/ButtonRefresh"
@onready var optionComPort: OptionButton = $"HFlowContainer/OptionComPort"
@onready var serial: SerialPort = SerialPort.new()

var time_start = 0
var time_now = 0

func updateComPorts():
	optionComPort.clear()
	optionComPort.add_separator("choose")
	for name in SerialPort.get_port_names():
		optionComPort.add_item(name)
	pass
	optionComPort.select(-1)


# Called when the node enters the scene tree for the first time.
func _ready():
	updateComPorts()
	optionComPort.connect("item_selected", _on_comport_selected)
	buttonRefresh.connect("pressed", updateComPorts)
	buttonConnect.connect("pressed", _on_connect_pressed)
	serial.connect("byte_received", _on_byte_received)
	print("baudrate: ", serial.baudrate)
	serial.baudrate = 115200
	serial.bits = 8
	print("baudrate: ", serial.baudrate)
	time_start = Time.get_ticks_msec()
	pass # Replace with function body.

func _on_connect_pressed():
	serial.open(serial.SP_MODE_READ_WRITE)
	pass

func _on_byte_received(byte:int):
	print("%x received" % byte)
	pass

func _on_comport_selected(id):
	var name = optionComPort.get_item_text(id)
	print(name)
	buttonConnect.disabled = false
	serial.port_name = name
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
#	menuComPort.get_
	time_now = Time.get_ticks_msec()
	var elapsed = time_now - time_start
	if serial.is_open():
		var data = serial.read()
		if data.is_empty() and elapsed > 2000:
			var msg = "hello world!\r\n".to_utf8_buffer()
			serial.write(msg)
			time_start = time_now
		elif not data.is_empty():
			print(data.hex_encode())
			print(data.get_string_from_utf8())
		pass
	pass
