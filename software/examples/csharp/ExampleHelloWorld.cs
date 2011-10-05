using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "ABC"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		BrickletLCD16x2 lcd = new BrickletLCD16x2(UID); // Create device object
		ipcon.AddDevice(lcd); // Add device to ip connection
		// Don't use device before it is added to a connection


		// Turn backlight on
		lcd.BacklightOn();

		// Write "Hello World"
		lcd.WriteLine(0, 0, "Hello World");

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
    }
}
