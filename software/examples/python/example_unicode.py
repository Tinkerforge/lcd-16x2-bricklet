#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your LCD 16x2 Bricklet

import sys
from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_lcd_16x2 import BrickletLCD16x2

# Maps a Python string to the LCD charset
def unicode_to_ks0066u(string):
    if sys.hexversion < 0x03000000:
        byte = lambda x: chr(x)
        ks0066u = ''

        if not isinstance(string, unicode):
            code_points = unicode(string, 'UTF-8')
        else:
            code_points = string
    else:
        byte = lambda x: bytes([x])
        ks0066u = bytes()
        code_points = string

    for code_point in code_points:
        code_point = ord(code_point)

        # ASCII subset from JIS X 0201
        if code_point >= 0x0020 and code_point <= 0x007e:
            # The LCD charset doesn't include '\' and '~', use similar characters instead
            mapping = {
                0x005c : byte(0xa4), # REVERSE SOLIDUS maps to HALFWIDTH IDEOGRAPHIC COMMA
                0x007e : byte(0x2d)  # TILDE maps to HYPHEN-MINUS
            }

            try:
                c = mapping[code_point]
            except KeyError:
                c = byte(code_point)
        # Katakana subset from JIS X 0201
        elif code_point >= 0xff61 and code_point <= 0xff9f:
            c = byte(code_point - 0xfec0)
        # Special characters
        else:
            mapping = {
                0x00a5 : byte(0x5c), # YEN SIGN
                0x2192 : byte(0x7e), # RIGHTWARDS ARROW
                0x2190 : byte(0x7f), # LEFTWARDS ARROW
                0x00b0 : byte(0xdf), # DEGREE SIGN maps to KATAKANA SEMI-VOICED SOUND MARK
                0x03b1 : byte(0xe0), # GREEK SMALL LETTER ALPHA
                0x00c4 : byte(0xe1), # LATIN CAPITAL LETTER A WITH DIAERESIS
                0x00e4 : byte(0xe1), # LATIN SMALL LETTER A WITH DIAERESIS
                0x00df : byte(0xe2), # LATIN SMALL LETTER SHARP S
                0x03b5 : byte(0xe3), # GREEK SMALL LETTER EPSILON
                0x00b5 : byte(0xe4), # MICRO SIGN
                0x03bc : byte(0xe4), # GREEK SMALL LETTER MU
                0x03c2 : byte(0xe5), # GREEK SMALL LETTER FINAL SIGMA
                0x03c1 : byte(0xe6), # GREEK SMALL LETTER RHO
                0x221a : byte(0xe8), # SQUARE ROOT
                0x00b9 : byte(0xe9), # SUPERSCRIPT ONE maps to SUPERSCRIPT (minus) ONE
                0x00a4 : byte(0xeb), # CURRENCY SIGN
                0x00a2 : byte(0xec), # CENT SIGN
                0x2c60 : byte(0xed), # LATIN CAPITAL LETTER L WITH DOUBLE BAR
                0x00f1 : byte(0xee), # LATIN SMALL LETTER N WITH TILDE
                0x00d6 : byte(0xef), # LATIN CAPITAL LETTER O WITH DIAERESIS
                0x00f6 : byte(0xef), # LATIN SMALL LETTER O WITH DIAERESIS
                0x03f4 : byte(0xf2), # GREEK CAPITAL THETA SYMBOL
                0x221e : byte(0xf3), # INFINITY
                0x03a9 : byte(0xf4), # GREEK CAPITAL LETTER OMEGA
                0x00dc : byte(0xf5), # LATIN CAPITAL LETTER U WITH DIAERESIS
                0x00fc : byte(0xf5), # LATIN SMALL LETTER U WITH DIAERESIS
                0x03a3 : byte(0xf6), # GREEK CAPITAL LETTER SIGMA
                0x03c0 : byte(0xf7), # GREEK SMALL LETTER PI
                0x0304 : byte(0xf8), # COMBINING MACRON
                0x00f7 : byte(0xfd), # DIVISION SIGN
                0x25a0 : byte(0xff)  # BLACK SQUARE
            }

            try:
                c = mapping[code_point]
            except KeyError:
                c = byte(0xff) # BLACK SQUARE

        # Special handling for 'x' followed by COMBINING MACRON
        if c == byte(0xf8):
            if len(ks0066u) == 0 or not ks0066u.endswith(byte(0x78)):
                c = byte(0xff) # BLACK SQUARE

            if len(ks0066u) > 0:
                ks0066u = ks0066u[:-1]

        ks0066u += c

    return ks0066u

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    lcd = BrickletLCD16x2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Turn backlight on
    lcd.backlight_on()

    # Write a string using the unicode_to_ks0066u function to map to the LCD charset
    lcd.write_line(0, 0, unicode_to_ks0066u('Stromstärke: 5µA'))

    # Write a string directly including characters from the LCD charset
    lcd.write_line(1, 0, b'Drehzahl: 1000s\xe9')

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
