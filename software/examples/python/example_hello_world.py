#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your LCD 16x2 Bricklet

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_lcd_16x2 import BrickletLCD16x2

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    lcd = BrickletLCD16x2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Turn backlight on
    lcd.backlight_on()

    # Write "Hello World"
    lcd.write_line(0, 0, "Hello World")

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
