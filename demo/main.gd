extends Node2D

@onready var serial: Serial = Serial.new()
# Called when the node enters the scene tree for the first time.
func _ready():
	print(serial.get_port_names())
	var cfg: PortConfig = PortConfig.new()
	print(cfg.baudrate);
	cfg.baudrate = 115200;
	print(cfg.baudrate);
	print("flow: ", cfg.flowcontrol);
	cfg.flowcontrol = PortConfig.SP_FLOWCONTROL_RTSCTS
	print("flow: ", cfg.flowcontrol);
	print("parity: ",cfg.parity)
	cfg.parity = PortConfig.SP_PARITY_SPACE
	print("parity: ", cfg.parity)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
