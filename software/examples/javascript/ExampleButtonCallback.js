var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your LCD 16x2 Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var lcd = new Tinkerforge.BrickletLCD16x2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

// Register button pressed callback
lcd.on(Tinkerforge.BrickletLCD16x2.CALLBACK_BUTTON_PRESSED,
    // Callback function for button pressed callback
    function (button) {
        console.log('Button Pressed: ' + button);
    }
);

// Register button released callback
lcd.on(Tinkerforge.BrickletLCD16x2.CALLBACK_BUTTON_RELEASED,
    // Callback function for button released callback
    function (button) {
        console.log('Button Released: ' + button);
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
