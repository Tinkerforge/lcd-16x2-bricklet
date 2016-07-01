#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletLCD16x2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your LCD 16x2 Bricklet

# Callback subroutine for button pressed callback
sub cb_button_pressed
{
    my ($button) = @_;

    print "Button Pressed: $button\n";
}

# Callback subroutine for button released callback
sub cb_button_released
{
    my ($button) = @_;

    print "Button Released: $button\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $lcd = Tinkerforge::BrickletLCD16x2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register button pressed callback to subroutine cb_button_pressed
$lcd->register_callback($lcd->CALLBACK_BUTTON_PRESSED, 'cb_button_pressed');

# Register button released callback to subroutine cb_button_released
$lcd->register_callback($lcd->CALLBACK_BUTTON_RELEASED, 'cb_button_released');

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
