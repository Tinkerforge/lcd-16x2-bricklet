Imports System
Imports Tinkerforge

Module ExampleButtonCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    ' Callback subroutine for button pressed callback
    Sub ButtonPressedCB(ByVal sender As BrickletLCD16x2, ByVal button As Byte)
        Console.WriteLine("Button Pressed: " + button.ToString())
    End Sub

    ' Callback subroutine for button released callback
    Sub ButtonReleasedCB(ByVal sender As BrickletLCD16x2, ByVal button As Byte)
        Console.WriteLine("Button Released: " + button.ToString())
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim lcd As New BrickletLCD16x2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register button pressed callback to subroutine ButtonPressedCB
        AddHandler lcd.ButtonPressed, AddressOf ButtonPressedCB

        ' Register button released callback to subroutine ButtonReleasedCB
        AddHandler lcd.ButtonReleased, AddressOf ButtonReleasedCB

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
