import com.tinkerforge.BrickletLCD16x2;
import com.tinkerforge.IPConnection;

public class ExampleButtonCallback {
	private static final String host = new String("localhost");
	private static final int port = 4223;
	private static final String UID = new String("ABC"); // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(host, port); // Create connection to brickd (Can throw IOException)

		BrickletLCD16x2 lcd = new BrickletLCD16x2(UID); // Create device object
		ipcon.addDevice(lcd); // Add device to ip connection (Can throw IPConnection.TimeoutException)
		// Don't use device before it is added to a connection
		

		// Add and implement listener for pressed and released events
		lcd.addListener(new BrickletLCD16x2.ButtonPressedListener() {
			public void buttonPressed(short button) {
				System.out.println("Pressed: " + button);
			}
		});
		lcd.addListener(new BrickletLCD16x2.ButtonReleasedListener() {
			public void buttonReleased(short button) {
				System.out.println("Released: " + button);
			}
		});
		
		System.out.println("Press ctrl+c to exit");
		ipcon.joinThread();
	}
}
