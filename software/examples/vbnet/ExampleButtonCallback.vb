Imports Tinkerforge

Module ExampleButtonCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "6ko" ' Change to your UID

    ' Callback functions for button status
    Sub PressedCB(ByVal sender As BrickletLCD16x2, ByVal button As Byte)
        System.Console.WriteLine("Pressed: " + button.ToString())
    End Sub

    Sub ReleasedCB(ByVal sender As BrickletLCD16x2, ByVal button As Byte)
        System.Console.WriteLine("Released: " + button.ToString())
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim lcd As New BrickletLCD16x2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register callbacks for pressed and released events
        AddHandler lcd.ButtonPressed, AddressOf PressedCB
        AddHandler lcd.ButtonReleased, AddressOf ReleasedCB

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        ipcon.Disconnect()
    End Sub
End Module
