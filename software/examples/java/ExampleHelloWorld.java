import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletLCD16x2;

public class ExampleHelloWorld {
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

		// Turn backlight on
		lcd162.backlightOn();

		// Write "Hello World"
		lcd162.writeLine((short)0, (short)0, "Hello World");

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
