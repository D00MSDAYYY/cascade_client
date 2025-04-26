s = sensor.new("temperature_in_room")
s:subscribe_to(drivers.driver1, sensors.sensor2)

value_set = {}

text_set = label.new("")
text_set:set_measure_unit("°C")
s:add_widget("text_set", text_set)

button_up = button.new("↑")
button_up.on_clicked = function()
	value_set = value_set - 1
	text_set:set_value(value_set)
end
s:add_widget("button_up", button_up)

button_down = button.new("↓")
button_down.on_clicked = function()
	value_set = value_set + 1
	text_set:set_value(value_set)
end
s:add_widget("button_down", button_down)

s:add_widget("separator", separator.new())

text_actual = label.new("")
text_actual:set_measure_unit("°C")
s:add_widget("text_actual", text_actual)

s.on_update = function()
	value_actual = drivers.driver1:get_temperature();
end