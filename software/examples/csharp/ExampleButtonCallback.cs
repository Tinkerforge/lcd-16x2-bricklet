using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback function for button pressed callback
	static void ButtonPressedCB(BrickletLCD16x2 sender, byte button)
	{
		Console.WriteLine("Button Pressed: " + button);
	}

	// Callback function for button released callback
	static void ButtonReleasedCB(BrickletLCD16x2 sender, byte button)
	{
		Console.WriteLine("Button Released: " + button);
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletLCD16x2 lcd = new BrickletLCD16x2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register button pressed callback to function ButtonPressedCB
		lcd.ButtonPressed += ButtonPressedCB;

		// Register button released callback to function ButtonReleasedCB
		lcd.ButtonReleased += ButtonReleasedCB;

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
