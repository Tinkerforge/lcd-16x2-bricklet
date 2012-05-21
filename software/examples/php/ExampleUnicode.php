<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletLCD16x2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletLCD16x2;

$host = 'localhost';
$port = 4223;
$uid = '6mJ'; // Change to your UID

// Maps a string to the LCD charset
function auto_to_ks0066u($string)
{
	$ks0066u = '';
	$utf32le = mb_convert_encoding($string, 'UTF-32LE', 'auto');
	$c = '';

	for ($i = 0; $i < strlen($utf32le); $i += 4) {
		// Combine 4 bytes into 1 code point
		$codePoint = ord($utf32le[$i]) + ord($utf32le[$i + 1]) * 256 + 
		             ord($utf32le[$i + 2]) * 65536 + ord($utf32le[$i + 3]) * 16777216;

		// ASCII subset from JIS X 0201
		if ($codePoint >= 0x0020 && $codePoint <= 0x007e) {
			// The LCD charset doesn't include '\' and '~', use similar characters instead
			switch ($codePoint) {
			case 0x005c: $c = chr(0xa4); break; // REVERSE SOLIDUS is similar to IDEOGRAPHIC COMMA
			case 0x007e: $c = chr(0x2d); break; // TILDE is similar to HYPHEN-MINUS
			default: $c = chr($codePoint); break;
			}
		}
		// Katakana subset from JIS X 0201
		else if ($codePoint >= 0xff61 && $codePoint <= 0xff9f) {
			$c = chr($codePoint - 0xfec0);
		}
		// Special characters
		else {
			switch ($codePoint) {
			case 0x00a5: $c = chr(0x5c); break; // YEN SIGN
			case 0x2192: $c = chr(0x7e); break; // RIGHTWARDS ARROW
			case 0x2190: $c = chr(0x7f); break; // LEFTWARDS ARROW
			case 0x00b0: $c = chr(0xdf); break; // DEGREE SIGN is similar to KATAKANA SEMI-VOICED SOUND MARK
			case 0x03b1: $c = chr(0xe0); break; // GREEK SMALL LETTER ALPHA
			case 0x00e4: $c = chr(0xe1); break; // LATIN SMALL LETTER A WITH DIAERESIS
			case 0x00df: $c = chr(0xe2); break; // LATIN SMALL LETTER SHARP S
			case 0x03b5: $c = chr(0xe3); break; // GREEK SMALL LETTER EPSILON
			case 0x00b5: $c = chr(0xe4); break; // MICRO SIGN
			case 0x03bc: $c = chr(0xe4); break; // GREEK SMALL LETTER MU
			case 0x03c2: $c = chr(0xe5); break; // GREEK SMALL LETTER FINAL SIGMA
			case 0x03c1: $c = chr(0xe6); break; // GREEK SMALL LETTER RHO
			case 0x221a: $c = chr(0xe8); break; // SQUARE ROOT
			case 0x00b9: $c = chr(0xe9); break; // SUPERSCRIPT ONE is similar to SUPERSCRIPT (minus) ONE
			case 0x00a4: $c = chr(0xeb); break; // CURRENCY SIGN
			case 0x00a2: $c = chr(0xec); break; // CENT SIGN
			case 0x2c60: $c = chr(0xed); break; // LATIN CAPITAL LETTER L WITH DOUBLE BAR
			case 0x00f1: $c = chr(0xee); break; // LATIN SMALL LETTER N WITH TILDE
			case 0x00f6: $c = chr(0xef); break; // LATIN SMALL LETTER O WITH DIAERESIS
			case 0x03f4: $c = chr(0xf2); break; // GREEK CAPITAL THETA SYMBOL
			case 0x221e: $c = chr(0xf3); break; // INFINITY
			case 0x03a9: $c = chr(0xf4); break; // GREEK CAPITAL LETTER OMEGA
			case 0x00fc: $c = chr(0xf5); break; // LATIN SMALL LETTER U WITH DIAERESIS
			case 0x03a3: $c = chr(0xf6); break; // GREEK CAPITAL LETTER SIGMA
			case 0x03c0: $c = chr(0xf7); break; // GREEK SMALL LETTER PI
			case 0x0304: $c = chr(0xf8); break; // COMBINING MACRON
			case 0x00f7: $c = chr(0xfd); break; // DIVISION SIGN

			default:
			case 0x25a0: $c = chr(0xff); break; // BLACK SQUARE
			}
		}

		// Special handling for 'x' followed by COMBINING MACRON
		if ($c == chr(0xf8)) {
			if (strlen($ks0066u) == 0 || substr($ks0066u, strlen($ks0066u) - 1, 1) != 'x') {
				$c = chr(0xff); // BLACK SQUARE
			}

			if (strlen($ks0066u) > 0) {
				$ks0066u = substr($ks0066u, 0, strlen($ks0066u) - 1);
			}
		}

		$ks0066u .= $c;
	}

	return $ks0066u;
}

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$lcd = new BrickletLCD16x2($uid); // Create device object

$ipcon->addDevice($lcd); // Add device to IP connection
// Don't use device before it is added to a connection

// Turn backlight on
$lcd->backlightOn();

// Write a string using the Utf16ToKS0066U function to map to the LCD charset
$lcd->writeLine(0, 0, auto_to_ks0066u("Stromstärke: 5µA"));

// Write a string directly including characters from the LCD charset
$lcd->writeLine(1, 0, "Drehzahl: 1000s\xe9");

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->destroy();

?>
