var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'SCD32'; // Change to your UID

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var lcd = new Tinkerforge.BrickletLCD16x2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

// Register button status callbacks
lcd.on(Tinkerforge.BrickletLCD16x2.CALLBACK_BUTTON_PRESSED,
    function(buttonNumber) {
        console.log('Pressed: '+buttonNumber);
    }
);
lcd.on(Tinkerforge.BrickletLCD16x2.CALLBACK_BUTTON_RELEASED,
    function(buttonNumber) {
        console.log('Released: '+buttonNumber);
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
