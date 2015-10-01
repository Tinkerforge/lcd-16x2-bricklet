function octave_example_hello_world()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    lcd = java_new("com.tinkerforge.BrickletLCD16x2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Turn backlight on
    lcd.backlightOn();

    % Write "Hello World"
    lcd.writeLine(0, 0, "Hello World");

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
