local function create_enum(tbl)
	local enum = {}
	local mt = {
		__index = function (_, k)
			error("Field '" .. k .. "' doesn't exist in enum")
		end,
		__newindex = function ()
			error("You can't change enum")
		end
	}
	for k, v in pairs(tbl) do
		enum[k] = v
	end
	return setmetatable(enum, mt)
end

sensor = {}

sensor.WORKING_STATE = create_enum({
	ON = "ON",
	OFF = "OFF",
	SUSPENDED = "SUSPENDED",
	BROKEN = "BROKEN"
})

function sensor.new(name, data, ui)
	local self = {
		name = name,
		data = data,
		ui = ui,
		senders = {},
		receivers = {},
		state = sensor.WORKING_STATE.OFF
	}

	setmetatable(self, { __index = sensor })

	return self
end

function sensor:add_senders(...) --
	local args = { ... }
	local new_subscriptions = {}
	local errors = {}

	-- Фаза валидации и подготовки новых данных
	for i, arg in ipairs(args) do
		-- Проверка типа элемента подписки
		if type(arg) ~= "table" then
			table.insert(errors, ("Bad argument #%d: expected table, got %s"):format(i, type(arg)))
		end
		-- Проверка структуры пары подписки
		if #arg ~= 2 then
			table.insert(errors, ("Bad subscription pair #%d: expected {name, sender}"):format(i))
		end

		local name = arg[1]
		local sender = arg[2]
		-- Проверка имени подписки
		if type(name) ~= "string" or name == "" then
			table.insert(errors, ("Bad name in pair #%d: non-empty string expected"):format(i))
		end
		-- Проверка отправителя
		if type(sender) ~= "table" then
			table.insert(errors, ("Bad sender in pair #%d: table expected"):format(i))
		end
		-- Проверка уникальности имени
		if self.senders[name] then
			table.insert(errors,
				("Subscription '%s' already exists in self.senders"):format(name))
		end

		if new_subscriptions[name] then
			table.insert(errors,
				("Subscriptions with same name '%s' occurs twice (or more) in args"):format(name))
		end
		new_subscriptions[name] = sender
	end

	if #errors > 0 then
		return false, table.concat(errors, "\n")
	end
	-- Фаза применения изменений (только если все проверки пройдены)
	for name, sender in pairs(new_subscriptions) do
		self.senders[name] = sender
	end

	return true
end

function sensor:remove_senders(...)
	local args = { ... }
	local errors = {}

	for i, arg in ipairs(args) do
		-- Проверка типа элемента подписки
		if type(arg) == "table" then
			local found = false
			for _, sender in pairs(self.senders) do
				if arg == sender then
					found = true
				end
			end
			if not found then
				table.insert(errors, ("Bad sender table in args #%d: not found to remove"):format(i))
			end
		elseif type(arg) == "string" then
			if arg == "" then
				table.insert(errors, ("Bad sender name '%s' in args: non-empty string expected"):format(arg))
			end
			local found = false
			for name, _ in pairs(self.senders) do
				if arg == name then
					found = true
				end
			end
			if not found then
				table.insert(errors, ("Bad sender name '%s' in args: not found to remove"):format(arg))
			end
		else
			table.insert(errors, ("Bad argument #%d: expected table or string, got %s"):format(i, type(arg)))
		end
	end

	if #errors > 0 then
		return nil, table.concat(errors, "\n")
	end

	for _, sender in ipairs(args) do
		if type(sender) == "table" then
			for n, s in pairs(self.senders) do
				if sender == s then
					self.senders[n] = nil
					break
				end
			end
		elseif type(sender) == "string" then
			self.senders[sender] = nil
		end
	end

	return true
end

function sensor:get_senders()
	print("in get_senders")
	print(#self.senders)
	local result = {}

	for name, sender in pairs(self.senders) do
		result[name] = sender
	end

	return result
end

function sensor:add_receivers(...)
	local args = { ... }
	local errors = {}

	for i, arg in ipairs(args) do
		-- Проверка типа элемента подписки
		if type(arg) ~= "table" then
			table.insert(errors, ("Bad argument #%d: expected table, got %s"):format(i, type(arg)))
		elseif self.receivers[arg] then
			table.insert(errors, ("Receiver #%d is already exists"):format(i))
		end
	end

	if #errors > 0 then
		return nil, table.concat(errors, "\n")
	end

	for _, receiver in ipairs(args) do
		self.receivers[receiver] = true
	end

	return true
end

function sensor:remove_receivers(...)
	local args = { ... }
	local errors = {}

	for i, arg in ipairs(args) do
		-- Проверка типа элемента подписки
		if type(arg) ~= "table" then
			table.insert(errors, ("Bad argument #%d: expected table, got %s"):format(i, type(arg)))
		end
		-- Проверка уникальности имени в наборе
		if not self.receivers[arg] then
			table.insert(errors, ("Receiver #%d is not present in receivers"):format(i))
		end
	end

	if #errors > 0 then
		return nil, table.concat(errors, "\n")
	end

	for _, receiver in ipairs(args) do
		self.receivers[receiver] = nil
	end

	return true
end

function sensor:get_receivers()
	local result = {}

	for receiver, _ in pairs(self.receivers) do
		table.insert(result, receiver)
	end

	return result
end

function sensor:on()
	if self.state == sensor.WORKING_STATE.OFF then
		local is_ok, err_msg = self.on_on()

		if is_ok then
			self.state = sensor.WORKING_STATE.ON
		end

		return is_ok, err_msg
	else
		return nil, "Sensor is not in 'OFF' state to turn in 'ON'. Sensor working state is '" .. self.state .. "'"
	end
end

function sensor:off()
	if self.state ~= sensor.WORKING_STATE.OFF then
		local is_ok, err_msg = self.on_off()

		if is_ok then
			self.state = sensor.WORKING_STATE.OFF
		end

		return is_ok, err_msg
	else
		return nil, "Sensor is already in 'OFF' state"
	end
end

function sensor:suspend()
	if self.state == sensor.WORKING_STATE.ON or self.state == sensor.WORKING_STATE.BROKEN then
		local is_ok, err_msg = self.on_suspend()

		if is_ok then
			self.state = sensor.WORKING_STATE.SUSPENDED
		end

		return is_ok, err_msg
	else
		return nil, "Sensor is not in 'ON' state to suspend"
	end
end

function sensor:resume()
	if self.state ~= sensor.WORKING_STATE.SUSPENDED then
		local is_ok, err_msg = self.on_resume()

		if is_ok then
			self.state = sensor.WORKING_STATE.ON
		end

		return is_ok, err_msg
	else
		return nil, "Sensor is not in 'SUSPENDED' state to resume"
	end
end

function sensor:update()
	if self.state == sensor.WORKING_STATE.ON or self.state == sensor.WORKING_STATE.BROKEN then
		local is_ok, err_msg = self.on_update()

		if not is_ok then
			self.state = sensor.WORKING_STATE.BROKEN
		end

		return is_ok, err_msg
	else
		return nil, "Sensor is not in 'ON' state to update"
	end
end

-- 'custom' code
-- s:add_senders({ 'room_temp1', drivers.room_temp1 }, { 'outside_temp', drivers.outside_temp })

-- sensor:on_update()
-- local room_temp1_value = self.senders['room_temp1']:get_value()
-- local outside_temp_value = self.senders['outside_temp']:get_value()






-- s = sensor.new("temperature_in_room")
-- s:subscribe_to(drivers.driver1, sensors.sensor2)

-- value_set = {}

-- text_set = label.new("")
-- text_set:set_measure_unit("°C")
-- s:add_widget("text_set", text_set)

-- button_up = button.new("↑")
-- button_up.on_clicked = function ()
-- 	value_set = value_set - 1
-- 	text_set:set_value(value_set)
-- end
-- s:add_widget("button_up", button_up)

-- button_down = button.new("↓")
-- button_down.on_clicked = function ()
-- 	value_set = value_set + 1
-- 	text_set:set_value(value_set)
-- end
-- s:add_widget("button_down", button_down)

-- s:add_widget("separator", separator.new())

-- text_actual = label.new("")
-- text_actual:set_measure_unit("°C")
-- s:add_widget("text_actual", text_actual)

-- s.on_update = function ()
-- 	value_actual = drivers.driver1:get_temperature();
-- end
