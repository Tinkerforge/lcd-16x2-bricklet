<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletLCD16x2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletLCD16x2;

$host = 'localhost';
$port = 4223;
$uid = '6mJ'; // Change to your UID

// Callback functions for button status
function cb_pressed($i)
{
    echo "Pressed: $i\n";
}

function cb_released($i)
{
    echo "Released: $i\n";
}

$ipcon = new IPConnection(); // Create IP connection
$lcd = new BrickletLCD16x2($uid, $ipcon); // Create device object

$ipcon->connect($host, $port); // Connect to brickd
// Don't use device before ipcon is connected

// Register button status callbacks to cb_pressed and cb_released
$lcd->registerCallback(BrickletLCD16x2::CALLBACK_BUTTON_PRESSED, 'cb_pressed');
$lcd->registerCallback(BrickletLCD16x2::CALLBACK_BUTTON_RELEASED, 'cb_released');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
