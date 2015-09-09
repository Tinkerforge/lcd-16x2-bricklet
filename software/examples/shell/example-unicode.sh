#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# turn backlight on
tinkerforge call lcd-16x2-bricklet $uid backlight-on

# write some strings using sed to map to the LCD charset
# note: this assumes that the shell supports UTF-8
tinkerforge call lcd-16x2-bricklet $uid write-line 0 0\
 "`echo 'Stromstärke: 5µA' | sed 'y/\o134~¥→←°αÄäßεµςρ√¹¤¢ⱠñÖöϴ∞ΩÜüΣπ÷■/\o244\o55\o134\o176\o177\o337\o340\o341\o341\o342\o343\o344\o345\o346\o350\o351\o353\o354\o355\o356\o357\o357\o362\o363\o364\o365\o365\o366\o367\o375\o377/'`"

# write a string directly including characters from the LCD charset
tinkerforge call lcd-16x2-bricklet $uid write-line 1 0\
 "`printf 'Drehzahl: 1000s\xe9'`"
