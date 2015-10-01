#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Turn backlight on
tinkerforge call lcd-16x2-bricklet $uid backlight-on

# Write "Hello World"
tinkerforge call lcd-16x2-bricklet $uid write-line 0 0 "Hello World"
