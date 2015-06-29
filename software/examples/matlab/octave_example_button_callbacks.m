function octave_example_button_callbacks()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "SCD32"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    lcd = java_new("com.tinkerforge.BrickletLCD16x2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register button status callbacks to cb_pressed and cb_released
    lcd.addButtonPressedCallback(@cb_pressed);
    lcd.addButtonReleasedLCallback(@cb_released);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback functions for button status
function cb_pressed(e)
    fprintf("Pressed: %d\n", short2int(e.button));
end

function cb_released(e)
    fprintf("Released: %d\n", short2int(e.button));
end

function int = short2int(short)
    if compare_versions(version(), "3.8", "<=")
        int = short.intValue();
    else
        int = short;
    end
end
