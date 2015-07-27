#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_lcd_16x2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
lcd162 = BrickletLCD16x2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Turn backlight on
lcd162.backlight_on

# Write "Hello World"
lcd162.write_line 0, 0, 'Hello World'

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
