use std::{error::Error, io};

use tinkerforge::{ip_connection::IpConnection, lcd_16x2_bricklet::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your LCD 16x2 Bricklet.

/// Maps a normal UTF-8 encoded string to the LCD charset.
fn utf8_to_ks0066u(utf8: &str) -> String {
    let mut result = Vec::<char>::with_capacity(utf8.len());
    for code_point in utf8.chars() {
        // Technically these are not code points, but scalar values.
        let mut replacement = match code_point as u32 {
            // ASCII subset from JIS X 0201
            // The LCD charset doesn't include '\' and '~', use similar characters instead
            0x005c => 0xa4, // REVERSE SOLIDUS maps to IDEOGRAPHIC COMMA
            0x007e => 0x2d, // TILDE maps to HYPHEN-MINUS
            0x0020...0x007e => code_point as u32,

            // Katakana subset from JIS X 0201
            0xff61...0xff9f => code_point as u32 - 0xfec0,

            // Special characters
            0x00a5 => 0x5c, // YEN SIGN
            0x2192 => 0x7e, // RIGHTWARDS ARROW
            0x2190 => 0x7f, // LEFTWARDS ARROW
            0x00b0 => 0xdf, // DEGREE SIGN maps to KATAKANA SEMI-VOICED SOUND MARK
            0x03b1 => 0xe0, // GREEK SMALL LETTER ALPHA
            0x00c4 => 0xe1, // LATIN CAPITAL LETTER A WITH DIAERESIS
            0x00e4 => 0xe1, // LATIN SMALL LETTER A WITH DIAERESIS
            0x00df => 0xe2, // LATIN SMALL LETTER SHARP S
            0x03b5 => 0xe3, // GREEK SMALL LETTER EPSILON
            0x00b5 => 0xe4, // MICRO SIGN
            0x03bc => 0xe4, // GREEK SMALL LETTER MU
            0x03c2 => 0xe5, // GREEK SMALL LETTER FINAL SIGMA
            0x03c1 => 0xe6, // GREEK SMALL LETTER RHO
            0x221a => 0xe8, // SQUARE ROOT
            0x00b9 => 0xe9, // SUPERSCRIPT ONE maps to SUPERSCRIPT (minus) ONE
            0x00a4 => 0xeb, // CURRENCY SIGN
            0x00a2 => 0xec, // CENT SIGN
            0x2c60 => 0xed, // LATIN CAPITAL LETTER L WITH DOUBLE BAR
            0x00f1 => 0xee, // LATIN SMALL LETTER N WITH TILDE
            0x00d6 => 0xef, // LATIN CAPITAL LETTER O WITH DIAERESIS
            0x00f6 => 0xef, // LATIN SMALL LETTER O WITH DIAERESIS
            0x03f4 => 0xf2, // GREEK CAPITAL THETA SYMBOL
            0x221e => 0xf3, // INFINITY
            0x03a9 => 0xf4, // GREEK CAPITAL LETTER OMEGA
            0x00dc => 0xf5, // LATIN CAPITAL LETTER U WITH DIAERESIS
            0x00fc => 0xf5, // LATIN SMALL LETTER U WITH DIAERESIS
            0x03a3 => 0xf6, // GREEK CAPITAL LETTER SIGMA
            0x03c0 => 0xf7, // GREEK SMALL LETTER PI
            0x0304 => 0xf8, // COMBINING MACRON
            0x00f7 => 0xfd, // DIVISION SIGN

            // Default
            _ => 0xff, // BLACK SQUARE
        };

        // Special handling for 'x' followed by COMBINING MACRON
        if replacement == 0xf8 {
            if result[result.len() - 1] != 'x' {
                replacement = 0xff; // BLACK SQUARE
            }

            if result.len() > 0 {
                result.truncate(result.len() - 1);
            }
        }
        result.push(std::char::from_u32(replacement).unwrap());
    }

    result.into_iter().collect()
}

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let lcd = Lcd16x2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Turn backlight on
    lcd.backlight_on();

    // Write a string using the utf8_to_ks0066u function to map to the LCD charset
    lcd.write_line(0, 0, utf8_to_ks0066u("Stromstärke: 5µA"));

    // Write a string directly including characters from the LCD charset. \u{00e9} is the ⁻¹ character.
    lcd.write_line(1, 0, "Drehzahl: 1000s\u{00e9}".to_string());

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
