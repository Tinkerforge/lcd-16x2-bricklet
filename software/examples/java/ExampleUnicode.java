import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletLCD16x2;

public class ExampleUnicode {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your LCD 16x2 Bricklet
	private static final String UID = "XYZ";

	// Maps a normal UTF-16 encoded string to the LCD charset
	static String utf16ToKS0066U(String utf16)
	{
		String ks0066u = "";
		char c;

		for (int i = 0; i < utf16.length(); i++) {
			int codePoint = utf16.codePointAt(i);

			if (Character.isHighSurrogate(utf16.charAt(i))) {
				// Skip low surrogate
				i++;
			}

			// ASCII subset from JIS X 0201
			if (codePoint >= 0x0020 && codePoint <= 0x007e) {
				// The LCD charset doesn't include '\' and '~', use similar characters instead
				switch (codePoint) {
				case 0x005c: c = (char)0xa4; break; // REVERSE SOLIDUS maps to IDEOGRAPHIC COMMA
				case 0x007e: c = (char)0x2d; break; // TILDE maps to HYPHEN-MINUS
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
				case 0x00b0: c = (char)0xdf; break; // DEGREE SIGN maps to KATAKANA SEMI-VOICED SOUND MARK
				case 0x03b1: c = (char)0xe0; break; // GREEK SMALL LETTER ALPHA
				case 0x00c4: c = (char)0xe1; break; // LATIN CAPITAL LETTER A WITH DIAERESIS
				case 0x00e4: c = (char)0xe1; break; // LATIN SMALL LETTER A WITH DIAERESIS
				case 0x00df: c = (char)0xe2; break; // LATIN SMALL LETTER SHARP S
				case 0x03b5: c = (char)0xe3; break; // GREEK SMALL LETTER EPSILON
				case 0x00b5: c = (char)0xe4; break; // MICRO SIGN
				case 0x03bc: c = (char)0xe4; break; // GREEK SMALL LETTER MU
				case 0x03c2: c = (char)0xe5; break; // GREEK SMALL LETTER FINAL SIGMA
				case 0x03c1: c = (char)0xe6; break; // GREEK SMALL LETTER RHO
				case 0x221a: c = (char)0xe8; break; // SQUARE ROOT
				case 0x00b9: c = (char)0xe9; break; // SUPERSCRIPT ONE maps to SUPERSCRIPT (minus) ONE
				case 0x00a4: c = (char)0xeb; break; // CURRENCY SIGN
				case 0x00a2: c = (char)0xec; break; // CENT SIGN
				case 0x2c60: c = (char)0xed; break; // LATIN CAPITAL LETTER L WITH DOUBLE BAR
				case 0x00f1: c = (char)0xee; break; // LATIN SMALL LETTER N WITH TILDE
				case 0x00d6: c = (char)0xef; break; // LATIN CAPITAL LETTER O WITH DIAERESIS
				case 0x00f6: c = (char)0xef; break; // LATIN SMALL LETTER O WITH DIAERESIS
				case 0x03f4: c = (char)0xf2; break; // GREEK CAPITAL THETA SYMBOL
				case 0x221e: c = (char)0xf3; break; // INFINITY
				case 0x03a9: c = (char)0xf4; break; // GREEK CAPITAL LETTER OMEGA
				case 0x00dc: c = (char)0xf5; break; // LATIN CAPITAL LETTER U WITH DIAERESIS
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
				if (!ks0066u.endsWith("x")) {
					c = (char)0xff; // BLACK SQUARE
				}

				if (ks0066u.length() > 0) {
					ks0066u = ks0066u.substring(0, ks0066u.length() - 1);
				}
			}

			ks0066u += c;
		}

		return ks0066u;
	}

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletLCD16x2 lcd = new BrickletLCD16x2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Turn backlight on
		lcd.backlightOn();

		// Write a string using the utf16ToKS0066U function to map to the LCD charset
		lcd.writeLine((short)0, (short)0, utf16ToKS0066U("Stromstärke: 5µA"));

		// Write a string directly including characters from the LCD charset
		lcd.writeLine((short)1, (short)0, "Drehzahl: 1000s\u00e9");

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
