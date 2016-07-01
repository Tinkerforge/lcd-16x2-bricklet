import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletLCD16x2;

public class ExampleButtonCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your LCD 16x2 Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletLCD16x2 lcd = new BrickletLCD16x2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add button pressed listener
		lcd.addButtonPressedListener(new BrickletLCD16x2.ButtonPressedListener() {
			public void buttonPressed(short button) {
				System.out.println("Button Pressed: " + button);
			}
		});

		// Add button released listener
		lcd.addButtonReleasedListener(new BrickletLCD16x2.ButtonReleasedListener() {
			public void buttonReleased(short button) {
				System.out.println("Button Released: " + button);
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
