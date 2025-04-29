local templates = {
	{
		name = "BLANK",
		modifiable = false,
		script = "if print then print('hello from BLANK') end"
	},
	{
		name = "Standard",
		children = {
			{
				name = "CO2",
				modifiable = false,
				script = "",
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
