#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your LCD 16x2 Bricklet

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_lcd_16x2 import BrickletLCD16x2

# Callback function for button pressed callback
def cb_button_pressed(button):
    print("Button Pressed: " + str(button))

# Callback function for button released callback
def cb_button_released(button):
    print("Button Released: " + str(button))

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    lcd = BrickletLCD16x2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register button pressed callback to function cb_button_pressed
    lcd.register_callback(lcd.CALLBACK_BUTTON_PRESSED, cb_button_pressed)

    # Register button released callback to function cb_button_released
    lcd.register_callback(lcd.CALLBACK_BUTTON_RELEASED, cb_button_released)

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
