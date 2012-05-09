<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletLCD16x2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletLCD16x2;

$host = 'localhost';
$port = 4223;
$uid = '6mJ'; // Change to your UID

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$lcd = new BrickletLCD16x2($uid); // Create device object

$ipcon->addDevice($lcd); // Add device to IP connection
// Don't use device before it is added to a connection

// Turn backlight on
$lcd->backlightOn();

// Write "Hello World"
$lcd->writeLine(0, 0, 'Hello World');

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->destroy();

?>
