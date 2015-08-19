#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletLCD16x2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $lcd = Tinkerforge::BrickletLCD16x2->new(&UID, $ipcon); # Create device object

# Callback subroutine for button pressed callback
sub cb_button_pressed
{
    my ($button_pressed) = @_;

    print "Button Pressed: " . $button_pressed . "\n";
}

# Callback subroutine for button released callback
sub cb_button_released
{
    my ($button_released) = @_;

    print "Button Released: " . $button_released . "\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register button pressed callback to subroutine cb_button_pressed
$lcd->register_callback($lcd->CALLBACK_BUTTON_PRESSED, 'cb_button_pressed');

# Register button released callback to subroutine cb_button_released
$lcd->register_callback($lcd->CALLBACK_BUTTON_RELEASED, 'cb_button_released');

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
