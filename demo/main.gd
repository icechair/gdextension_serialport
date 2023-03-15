extends Node2D

@onready var serial: Serial = Serial.new()
# Called when the node enters the scene tree for the first time.
func _ready():
	print(serial.get_port_names())
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
