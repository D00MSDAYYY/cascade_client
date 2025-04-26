function make_err_handler(context)
    return function(msg)
        error(string.format("[%s][%s] %s\nCall stack:\n%s",
            cascade_client.clock:now(),
            context,
            msg or "value not available",
            debug.traceback("", 2)
        ), 2)
    end
end