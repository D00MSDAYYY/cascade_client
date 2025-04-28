local templates = {
	{
		name = "BLANK",
		modifiable = false,
		script = "if print then print('hello') end"
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
						script = "if print then print('hello') end"
					}
				}
			},
			{
				name = "Temperature",
				children = {
					{
						name = "default",
						modifiable = false,
						script = "if print then print('hello') end"
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
				script = "if print then print('hello') end"
			}
		}
	}
}

return templates