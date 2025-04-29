-- 'system' code
local sensor = {}
function sensor:add_senders(...)
	self.senders = self.senders or {}
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
		if #arg < 2 then
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
		return nil, table.concat(errors, "\n")
	end

	-- Фаза применения изменений (только если все проверки пройдены)
	for name, sender in pairs(new_subscriptions) do
		self.senders[name] = sender
	end

	return true
end

function sensor:remove_senders(...)
	self.senders = self.senders or {}
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
	self.senders = self.senders or {}
	local result = {}

	for name, sender in pairs(self.senders) do
		result[name] = sender
	end

	return result
end

function sensor:add_receivers(...)
	self.receivers = self.receivers or {}
	local args = { ... }
	local errors = {}

	for i, arg in ipairs(args) do
		-- Проверка типа элемента подписки
		if type(arg) ~= "table" then
			table.insert(errors, ("Bad argument #%d: expected table, got %s"):format(i, type(arg)))
		end
		-- Проверка уникальности имени во временном наборе
		if self.receivers[arg] then
			table.insert(errors, ("Receiver #%d is already in self.receivers"):format(i))
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
	self.receivers = self.receivers or {}
	local args = { ... }
	local errors = {}

	for i, arg in ipairs(args) do
		-- Проверка типа элемента подписки
		if type(arg) ~= "table" then
			table.insert(errors,("Bad argument #%d: expected table, got %s"):format(i, type(arg)))
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
	self.receivers = self.receivers or {}
	local result = {}

	for receiver, _ in pairs(self.senders) do
		table.insert(result, receiver)
	end

	return result
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
