using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "6mJ"; // Change to your UID

	// Maps a normal UTF-16 encoded string to the LCD charset
	static string Utf16ToKS0066U(string utf16)
	{
		string ks0066u = "";
		char c;

		for (int i = 0; i < utf16.Length; i++) {
			int codePoint = Char.ConvertToUtf32(utf16, i);

			if (Char.IsSurrogate(utf16, i)) {
				// Skip low surrogate
				i++;
			}

			// ASCII subset from JIS X 0201
			if (codePoint >= 0x0020 && codePoint <= 0x007e) {
				// The LCD charset doesn't include '\' and '~', use similar characters instead
				switch (codePoint) {
				case 0x005c: c = (char)0xa4; break; // REVERSE SOLIDUS is similar to IDEOGRAPHIC COMMA
				case 0x007e: c = (char)0x2d; break; // TILDE is similar to HYPHEN-MINUS
				default: c = (char)codePoint; break;
				}
			}
			// Katakana subset from JIS X 0201
			else if (codePoint >= 0xff61 && codePoint <= 0xff9f) {
				c = (char)(codePoint - 0xfec0);
			}
			// Special characters
			else {
				switch (codePoint) {
				case 0x00a5: c = (char)0x5c; break; // YEN SIGN
				case 0x2192: c = (char)0x7e; break; // RIGHTWARDS ARROW
				case 0x2190: c = (char)0x7f; break; // LEFTWARDS ARROW
				case 0x00b0: c = (char)0xdf; break; // DEGREE SIGN is similar to KATAKANA SEMI-VOICED SOUND MARK
				case 0x03b1: c = (char)0xe0; break; // GREEK SMALL LETTER ALPHA
				case 0x00e4: c = (char)0xe1; break; // LATIN SMALL LETTER A WITH DIAERESIS
				case 0x00df: c = (char)0xe2; break; // LATIN SMALL LETTER SHARP S
				case 0x03b5: c = (char)0xe3; break; // GREEK SMALL LETTER EPSILON
				case 0x00b5: c = (char)0xe4; break; // MICRO SIGN
				case 0x03bc: c = (char)0xe4; break; // GREEK SMALL LETTER MU
				case 0x03c2: c = (char)0xe5; break; // GREEK SMALL LETTER FINAL SIGMA
				case 0x03c1: c = (char)0xe6; break; // GREEK SMALL LETTER RHO
				case 0x221a: c = (char)0xe8; break; // SQUARE ROOT
				case 0x00b9: c = (char)0xe9; break; // SUPERSCRIPT ONE is similar to SUPERSCRIPT (minus) ONE
				case 0x00a4: c = (char)0xeb; break; // CURRENCY SIGN
				case 0x00a2: c = (char)0xec; break; // CENT SIGN
				case 0x2c60: c = (char)0xed; break; // LATIN CAPITAL LETTER L WITH DOUBLE BAR
				case 0x00f1: c = (char)0xee; break; // LATIN SMALL LETTER N WITH TILDE
				case 0x00f6: c = (char)0xef; break; // LATIN SMALL LETTER O WITH DIAERESIS
				case 0x03f4: c = (char)0xf2; break; // GREEK CAPITAL THETA SYMBOL
				case 0x221e: c = (char)0xf3; break; // INFINITY
				case 0x03a9: c = (char)0xf4; break; // GREEK CAPITAL LETTER OMEGA
				case 0x00fc: c = (char)0xf5; break; // LATIN SMALL LETTER U WITH DIAERESIS
				case 0x03a3: c = (char)0xf6; break; // GREEK CAPITAL LETTER SIGMA
				case 0x03c0: c = (char)0xf7; break; // GREEK SMALL LETTER PI
				case 0x0304: c = (char)0xf8; break; // COMBINING MACRON
				case 0x00f7: c = (char)0xfd; break; // DIVISION SIGN

				default:
				case 0x25a0: c = (char)0xff; break; // BLACK SQUARE
				}
			}

			// Special handling for 'x' followed by COMBINING MACRON
			if (c == (char)0xf8) {
				if (!ks0066u.EndsWith("x")) {
					c = (char)0xff; // BLACK SQUARE
				}

				if (ks0066u.Length > 0) {
					ks0066u = ks0066u.Remove(ks0066u.Length - 1, 1);
				}
			}

			ks0066u += c;
		}

		return ks0066u;
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		BrickletLCD16x2 lcd = new BrickletLCD16x2(UID); // Create device object
		ipcon.AddDevice(lcd); // Add device to IP connection
		// Don't use device before it is added to a connection

		// Turn backlight on
		lcd.BacklightOn();

		// Write a string using the Utf16ToKS0066U function to map to the LCD charset
		lcd.WriteLine(0, 0, Utf16ToKS0066U("Stromstärke: 5µA"));

		// Write a string directly including characters from the LCD charset
		lcd.WriteLine(1, 0, "Drehzahl: 1000s\xe9");

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
	}
}