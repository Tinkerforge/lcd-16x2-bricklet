use std::{error::Error, io, thread};
use tinkerforge::{ip_connection::IpConnection, lcd_16x2_bricklet::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your LCD 16x2 Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let lcd = Lcd16x2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Create receiver for button pressed events.
    let button_pressed_receiver = lcd.get_button_pressed_receiver();

    // Spawn thread to handle received events. This thread ends when the `lcd` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for button_pressed in button_pressed_receiver {
            println!("Button Pressed: {}", button_pressed);
        }
    });

    // Create receiver for button released events.
    let button_released_receiver = lcd.get_button_released_receiver();

    // Spawn thread to handle received events. This thread ends when the `lcd` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for button_released in button_released_receiver {
            println!("Button Released: {}", button_released);
        }
    });

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
