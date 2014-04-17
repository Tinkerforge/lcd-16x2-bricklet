function matlab_example_button_callbacks
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletLCD16x2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'SCD32'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    lcd = BrickletLCD16x2(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register button status callbacks to cb_pressed and cb_released
    set(lcd, 'ButtonPressedCallback', @(h, e) cb_pressed(e));
    set(lcd, 'ButtonReleasedCallback', @(h, e) cb_released(e));

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback functions for button status
function cb_pressed(e)
    fprintf('Pressed: %i\n', e.button);
end
function cb_released(e)
    fprintf('Released: %i\n', e.button);
end
