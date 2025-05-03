function ui.QAbstractButton:connect_to_clicked(...)
	local args = { ... }
	local new_slots = {}
	local errors = {}

	for i, arg in ipairs(args) do
		if type(arg) ~= "table" then
			table.insert(errors, ("Bad argument #%d: expected table, got %s"):format(i, type(arg)))
		end

		if #arg ~= 2 then
			table.insert(errors, ("Bad slot pair #%d: expected {name, slot}"):format(i))
		end

		local name = arg[1]
		local slot = arg[2]

		if type(name) ~= "string" or name == "" then
			table.insert(errors, ("Bad name in pair #%d: non-empty string expected"):format(i))
		end

		if type(slot) ~= "function" then
			table.insert(errors, ("Bad slot in pair #%d: function expected"):format(i))
		end

		if self.connected_slots[name] then
			table.insert(errors, ("Slot '%s' already exists in self.connected_slots"):format(name))
		end

		if new_slots[name] then
			table.insert(errors, ("Slot with same name '%s' occurs twice (or more) in args"):format(name))
		end
		new_slots[name] = slot
	end

	if #errors > 0 then
		return false, table.concat(errors, "\n")
	end

	for name, slot in pairs(new_slots) do
		ui.QAbstractButton._aux_connect_to_clicked(self, name, slot)
		self.connected_slots[name] = slot
	end

	return true
end
