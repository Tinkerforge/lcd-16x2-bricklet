function octave_example_button_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your LCD 16x2 Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    lcd = javaObject("com.tinkerforge.BrickletLCD16x2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register button pressed callback to function cb_button_pressed
    lcd.addButtonPressedCallback(@cb_button_pressed);

    % Register button released callback to function cb_button_released
    lcd.addButtonReleasedCallback(@cb_button_released);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for button pressed callback
function cb_button_pressed(e)
    fprintf("Button Pressed: %d\n", java2int(e.button));
end

% Callback function for button released callback
function cb_button_released(e)
    fprintf("Button Released: %d\n", java2int(e.button));
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
