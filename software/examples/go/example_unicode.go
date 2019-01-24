package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/lcd_16x2_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your LCD 16x2 Bricklet.

func UTF8ToKS0066U(utf8 string) string {
	var result []rune
	for _, r := range utf8 {
		var replacement rune
		switch {
		// ASCII subset from JIS X 0201
		// The LCD charset doesn't include '\' and '~', use similar characters instead
		case r == 0x005c:
			replacement = 0xa4 // REVERSE SOLIDUS maps to IDEOGRAPHIC COMMA
		case r == 0x007e:
			replacement = 0x2d // TILDE maps to HYPHEN-MINUS
		case r >= 0x0020 && r <= 0x007e:
			replacement = r

		// Katakana subset from JIS X 0201
		case r >= 0xff61 && r <= 0xff9f:
			replacement = r - 0xfec0

		// Special characters
		case r == 0x00a5:
			replacement = 0x5c // YEN SIGN
		case r == 0x2192:
			replacement = 0x7e // RIGHTWARDS ARROW
		case r == 0x2190:
			replacement = 0x7f // LEFTWARDS ARROW
		case r == 0x00b0:
			replacement = 0xdf // DEGREE SIGN maps to KATAKANA SEMI-VOICED SOUND MARK
		case r == 0x03b1:
			replacement = 0xe0 // GREEK SMALL LETTER ALPHA
		case r == 0x00c4:
			replacement = 0xe1 // LATIN CAPITAL LETTER A WITH DIAERESIS
		case r == 0x00e4:
			replacement = 0xe1 // LATIN SMALL LETTER A WITH DIAERESIS
		case r == 0x00df:
			replacement = 0xe2 // LATIN SMALL LETTER SHARP S
		case r == 0x03b5:
			replacement = 0xe3 // GREEK SMALL LETTER EPSILON
		case r == 0x00b5:
			replacement = 0xe4 // MICRO SIGN
		case r == 0x03bc:
			replacement = 0xe4 // GREEK SMALL LETTER MU
		case r == 0x03c2:
			replacement = 0xe5 // GREEK SMALL LETTER FINAL SIGMA
		case r == 0x03c1:
			replacement = 0xe6 // GREEK SMALL LETTER RHO
		case r == 0x221a:
			replacement = 0xe8 // SQUARE ROOT
		case r == 0x00b9:
			replacement = 0xe9 // SUPERSCRIPT ONE maps to SUPERSCRIPT (minus) ONE
		case r == 0x00a4:
			replacement = 0xeb // CURRENCY SIGN
		case r == 0x00a2:
			replacement = 0xec // CENT SIGN
		case r == 0x2c60:
			replacement = 0xed // LATIN CAPITAL LETTER L WITH DOUBLE BAR
		case r == 0x00f1:
			replacement = 0xee // LATIN SMALL LETTER N WITH TILDE
		case r == 0x00d6:
			replacement = 0xef // LATIN CAPITAL LETTER O WITH DIAERESIS
		case r == 0x00f6:
			replacement = 0xef // LATIN SMALL LETTER O WITH DIAERESIS
		case r == 0x03f4:
			replacement = 0xf2 // GREEK CAPITAL THETA SYMBOL
		case r == 0x221e:
			replacement = 0xf3 // INFINITY
		case r == 0x03a9:
			replacement = 0xf4 // GREEK CAPITAL LETTER OMEGA
		case r == 0x00dc:
			replacement = 0xf5 // LATIN CAPITAL LETTER U WITH DIAERESIS
		case r == 0x00fc:
			replacement = 0xf5 // LATIN SMALL LETTER U WITH DIAERESIS
		case r == 0x03a3:
			replacement = 0xf6 // GREEK CAPITAL LETTER SIGMA
		case r == 0x03c0:
			replacement = 0xf7 // GREEK SMALL LETTER PI
		case r == 0x0304:
			replacement = 0xf8 // COMBINING MACRON
		case r == 0x00f7:
			replacement = 0xfd // DIVISION SIGN

		default:
			replacement = 0xff // BLACK SQUARE
		}

		// Special handling for 'x' followed by COMBINING MACRON
		if replacement == 0xf8 {
			if result[len(result)-1] != 'x' {
				replacement = 0xff // BLACK SQUARE
			}

			if len(result) > 0 {
				result = result[:len(result)-1]
			}
		}
		result = append(result, replacement)
	}
	return string(result)
}

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	lcd, _ := lcd_16x2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Turn backlight on
	lcd.BacklightOn()

	// Write a string using the UTF8ToKS0066U function to map to the LCD charset
	lcd.WriteLine(0, 0, UTF8ToKS0066U("Stromstärke: 5µA"))

	// Write a string directly including characters from the LCD charset
	lcd.WriteLine(1, 0, "Drehzahl: 1000s\u00e9")

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
