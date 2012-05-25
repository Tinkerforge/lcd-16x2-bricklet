#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_lcd_16x2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = '6mJ' # Change to your UID

def unicode_to_ks0066u(string)
  ks0066u = ''

  string.each_codepoint do |codepoint|
    # ASCII subset from JIS X 0201
    if codepoint >= 0x0020 and codepoint <= 0x007e
      # The LCD charset doesn't include '\' and '~', use similar characters instead
      mapping = {
        0x005c => 0xa4.chr, # REVERSE SOLIDUS maps to IDEOGRAPHIC COMMA
        0x007e => 0x2d.chr  # TILDE maps to HYPHEN-MINUS
      }

      if mapping.has_key? codepoint
        c = mapping[codepoint]
      else
        c = codepoint.chr
      end
    # Katakana subset from JIS X 0201
    elsif codepoint >= 0xff61 and codepoint <= 0xff9f
      c = (codepoint - 0xfec0).chr
    # Special characters
    else
      mapping = {
        0x00a5 => 0x5c.chr, # YEN SIGN
        0x2192 => 0x7e.chr, # RIGHTWARDS ARROW
        0x2190 => 0x7f.chr, # LEFTWARDS ARROW
        0x00b0 => 0xdf.chr, # DEGREE SIGN maps to KATAKANA SEMI-VOICED SOUND MARK
        0x03b1 => 0xe0.chr, # GREEK SMALL LETTER ALPHA
        0x00e4 => 0xe1.chr, # LATIN SMALL LETTER A WITH DIAERESIS
        0x00df => 0xe2.chr, # LATIN SMALL LETTER SHARP S
        0x03b5 => 0xe3.chr, # GREEK SMALL LETTER EPSILON
        0x00b5 => 0xe4.chr, # MICRO SIGN
        0x03bc => 0xe4.chr, # GREEK SMALL LETTER MU
        0x03c2 => 0xe5.chr, # GREEK SMALL LETTER FINAL SIGMA
        0x03c1 => 0xe6.chr, # GREEK SMALL LETTER RHO
        0x221a => 0xe8.chr, # SQUARE ROOT
        0x00b9 => 0xe9.chr, # SUPERSCRIPT ONE maps to SUPERSCRIPT (minus) ONE
        0x00a4 => 0xeb.chr, # CURRENCY SIGN
        0x00a2 => 0xec.chr, # CENT SIGN
        0x2c60 => 0xed.chr, # LATIN CAPITAL LETTER L WITH DOUBLE BAR
        0x00f1 => 0xee.chr, # LATIN SMALL LETTER N WITH TILDE
        0x00f6 => 0xef.chr, # LATIN SMALL LETTER O WITH DIAERESIS
        0x03f4 => 0xf2.chr, # GREEK CAPITAL THETA SYMBOL
        0x221e => 0xf3.chr, # INFINITY
        0x03a9 => 0xf4.chr, # GREEK CAPITAL LETTER OMEGA
        0x00fc => 0xf5.chr, # LATIN SMALL LETTER U WITH DIAERESIS
        0x03a3 => 0xf6.chr, # GREEK CAPITAL LETTER SIGMA
        0x03c0 => 0xf7.chr, # GREEK SMALL LETTER PI
        0x0304 => 0xf8.chr, # COMBINING MACRON
        0x00f7 => 0xfd.chr, # DIVISION SIGN
        0x25a0 => 0xff.chr  # BLACK SQUARE
      }

      if mapping.has_key? codepoint
        c = mapping[codepoint]
      else
        c = 0xff.chr # BLACK SQUARE
      end
    end

    # Special handling for 'x' followed by COMBINING MACRON
    if c == 0xf8.chr
      if ks0066u.length == 0 or not ks0066u[-1, 1] == 0x78.chr
        c = 0xff.chr # BLACK SQUARE
      end

      if ks0066u.length > 0
        ks0066u = ks0066u[0..-2]
      end
    end

    ks0066u += c
  end

  ks0066u
end

ipcon = IPConnection.new HOST, PORT # Create IP connection to brickd
lcd = BrickletLCD16x2.new UID # Create device object
ipcon.add_device lcd # Add device to IP connection
# Don't use device before it is added to a connection

# Turn backlight on
lcd.backlight_on

# Write a string using the unicode_to_ks0066u function to map to the LCD charset
lcd.write_line 0, 0, unicode_to_ks0066u('Stromstärke: 5µA')

# Write a string directly including characters from the LCD charset
lcd.write_line 1, 0, "Drehzahl: 1000s\xe9"

puts 'Press key to exit'
$stdin.gets
ipcon.destroy
