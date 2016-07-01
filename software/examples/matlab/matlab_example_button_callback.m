function matlab_example_button_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletLCD16x2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your LCD 16x2 Bricklet

    ipcon = IPConnection(); % Create IP connection
    lcd = handle(BrickletLCD16x2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register button pressed callback to function cb_button_pressed
    set(lcd, 'ButtonPressedCallback', @(h, e) cb_button_pressed(e));

    % Register button released callback to function cb_button_released
    set(lcd, 'ButtonReleasedCallback', @(h, e) cb_button_released(e));

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for button pressed callback
function cb_button_pressed(e)
    fprintf('Button Pressed: %i\n', e.button);
end

% Callback function for button released callback
function cb_button_released(e)
    fprintf('Button Released: %i\n', e.button);
end
