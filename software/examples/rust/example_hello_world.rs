use std::{error::Error, io};

use tinkerforge::{ipconnection::IpConnection, lcd_16x2_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your LCD 16x2 Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let lcd_16x2_bricklet = LCD16x2Bricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    // Turn backlight on
    lcd_16x2_bricklet.backlight_on();

    // Write "Hello World"
    lcd_16x2_bricklet.write_line(0, 0, "Hello World".to_string());

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
