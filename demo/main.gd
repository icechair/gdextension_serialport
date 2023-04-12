extends Node2D


@onready var buttonConnect: Button = $"HFlowContainer/ButtonConnect"
@onready var buttonRefresh: Button = $"HFlowContainer/ButtonRefresh"
@onready var optionComPort: OptionButton = $"HFlowContainer/OptionComPort"
@onready var serial: SerialPort = SerialPort.new()
@onready var serialConfig: PortConfig = PortConfig.new()
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
	serialConfig.baudrate = 115200
	pass # Replace with function body.

func _on_connect_pressed():
	serial.open(serial.SP_MODE_READ_WRITE, serialConfig)
	serial.connect("byte_received", _on_byte_received)
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
	pass
