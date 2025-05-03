local templates = {
	{
		name = "BLANK",
		modifiable = false,
		script = [[
btn_down = ui.QPushButton.new('↓');
btn_down:setSizePolicy('Expanding', 'Expanding')
txt = ui.QLabel.new('init text');
txt:setSizePolicy('Expanding', 'Expanding')
btn_up = ui.QPushButton.new('↑');
btn_up:setSizePolicy('Expanding', 'Expanding')
lyt = ui.QHBoxLayout.new();
lyt:addWidget(btn_down);
lyt:addWidget(txt);
lyt:addWidget(btn_up);
ui = ui.QWidget.new();
ui:setLayout(lyt);
btn_up:_aux_connect_to_clicked('con1', function () print('hello') end)
]],
	},
	{
		name = "Standard",
		children = {
			{
				name = "CO2",
				modifiable = false,
				children = {
					{
						name = "default",
						modifiable = false,
						script = "if print then print('hello from CO2 default) end"
					}
				}
			},
			{
				name = "Temperature",
				children = {
					{
						name = "default",
						modifiable = false,
						script = "if print then print('hello from default temperature') end"
					}
				}
			}
		}
	},
	{
		name = "User-Defined",
		children = {
			{
				name = "my_temp_sensor",
				modifiable = true,
				script = "if print then print('hello from my_temp_sensor') end"
			}
		}
	}
}

return templates
