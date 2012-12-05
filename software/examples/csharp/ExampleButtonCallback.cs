using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "ABC"; // Change to your UID

	// Callback functions for button status
	static void PressedCB(object sender, byte button)
	{
		System.Console.WriteLine("Pressed: " + button);
	}

	static void ReleasedCB(object sender, byte button)
	{
		System.Console.WriteLine("Released: " + button);
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletLCD16x2 lcd = new BrickletLCD16x2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register callbacks for pressed and released events
		lcd.ButtonPressed += PressedCB;
		lcd.ButtonReleased += ReleasedCB;

		System.Console.WriteLine("Press key to exit");
		System.Console.ReadKey();
	}
}
