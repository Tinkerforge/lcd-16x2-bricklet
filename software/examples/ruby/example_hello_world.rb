#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_lcd_16x2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = '6mJ' # Change to your UID

ipcon = IPConnection.new HOST, PORT # Create IP connection to brickd
lcd = BrickletLCD16x2.new UID # Create device object
ipcon.add_device lcd # Add device to IP connection
# Don't use device before it is added to a connection

# Turn backlight on
lcd.backlight_on

# Write "Hello World"
lcd.write_line 0, 0, 'Hello World'

puts 'Press key to exit'
$stdin.gets
ipcon.destroy
