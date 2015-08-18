Imports Tinkerforge

Module ExampleButtonCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    ' Callback function for button pressed callback
    Sub ButtonPressedCB(ByVal sender As BrickletLCD16x2, ByVal buttonPressed As Byte)
        System.Console.WriteLine("Button Pressed: " + buttonPressed.ToString())
    End Sub

    ' Callback function for button released callback
    Sub ButtonReleasedCB(ByVal sender As BrickletLCD16x2, ByVal buttonReleased As Byte)
        System.Console.WriteLine("Button Released: " + buttonReleased.ToString())
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim lcd As New BrickletLCD16x2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register button pressed callback to function ButtonPressedCB
        AddHandler lcd.ButtonPressed, AddressOf ButtonPressedCB

        ' Register button released callback to function ButtonReleasedCB
        AddHandler lcd.ButtonReleased, AddressOf ButtonReleasedCB

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
