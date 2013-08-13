#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# turn backlight on
tinkerforge call lcd-16x2-bricklet $uid backlight-on

# write "Hello World"
tinkerforge call lcd-16x2-bricklet $uid write-line 0 0 "Hello World"
