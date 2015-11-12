function matlab_example_hello_world()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletLCD16x2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    lcd = handle(BrickletLCD16x2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Turn backlight on
    lcd.backlightOn();

    % Write "Hello World"
    lcd.writeLine(0, 0, 'Hello World');

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
