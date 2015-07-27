import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletLCD16x2;

public class ExampleButtonCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletLCD16x2 lcd162 = new BrickletLCD16x2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add button pressed listener
		lcd162.addButtonPressedListener(new BrickletLCD16x2.ButtonPressedListener() {
			public void buttonPressed(short buttonPressed) {
				System.out.println("Button Pressed: " + buttonPressed);
			}
		});

		// Add button released listener
		lcd162.addButtonReleasedListener(new BrickletLCD16x2.ButtonReleasedListener() {
			public void buttonReleased(short buttonReleased) {
				System.out.println("Button Released: " + buttonReleased);
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
