#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletLCD16x2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $lcd = Tinkerforge::BrickletLCD16x2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Turn backlight on
$lcd->backlight_on();

# Write "Hello World"
$lcd->write_line(0, 0, "Hello World");

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
