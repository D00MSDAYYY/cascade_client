page = cascade_client.main_window.system_pages["sensors"];
cascade_client.main_window:set_current_page(page);
-----
page = cascade_client.main_window:get_pages()["alerts"];
a = alert.new(alert.TYPE.INFO, "hello", "12-12-12", "test text str", "wowo");
page:add_alert(a);
-----
tmp = cascade_client.clock:now()
tmp:get_minutes()
-----
for k, v in pairs(_G) do print(k, v) end
-----
tmp = sensor.new("hell");
is_ok, err_msg = tmp:add_senders({ "s1", {} })
-----
btn_down = ui.QPushButton.new("↓");
btn_down:setSizePolicy("Expanding", "Expanding")
txt = ui.QLabel.new("init text");
txt:setSizePolicy("Expanding", "Expanding")
btn_up = ui.QPushButton.new("↑");
btn_up:setSizePolicy("Expanding", "Expanding")
lyt = ui.QHBoxLayout.new();
lyt:addWidget(btn_down);
lyt:addWidget(txt);
lyt:addWidget(btn_up);
ui = ui.QWidget.new();
ui:setLayout(lyt);
ui:show();


